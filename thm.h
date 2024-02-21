#ifndef THM_H
#define THM_H

class theorem
{
private:
    struct Node
    {
        char c;
        Node *ls, *rs;
        Node(char _c, Node *_ls, Node *_rs) : c(_c), ls(_ls), rs(_rs) {}
    }; // operator or variable
    std::list<Node*> pre, suf;
    std::set<char> OP, ROP; // all valid operators and right associative operators
    std::unordered_map<char, int> opp; // priority
    std::string ori_expression, inf_expression, suf_expression;
    bool isOp(char c) {if(OP.find(c) != OP.end()) return 1; else return 0;}
    bool isRightOp(char c) {if(ROP.find(c) != ROP.end()) return 1; else return 0;}
    void toInf()
    {
        for(auto it : ori_expression) if(it != ' ') inf_expression.push_back(it);
    }
    void toSuf()
    {
        std::list<int> op; // operator stack
        for(auto it : inf_expression)
        {
            if(it >= 'A' && it <= 'Z') suf_expression.push_back(it);
            if(it == '(') op.push_back(it);
            else if(it == ')')
            {
                while(op.back() != '(')
                {
                    suf_expression.push_back(op.back());
                    op.pop_back();
                }
                op.pop_back(); // pop '('
            }
            else if(isOp(it))
            {
                while(!op.empty() && 
                    ((!isRightOp(it) && opp[op.back()] >= opp[it]) ||
			        (isRightOp(it) && opp[op.back()] > opp[it])))
                {
                    suf_expression.push_back(op.back());
                    op.pop_back();
                }
                op.push_back(it);
            }
        }
        while(!op.empty())
        {
            suf_expression.push_back(op.back());
            op.pop_back();
        }
    }
public:
    theorem();
    friend std::istream & operator>>(std::istream & is, theorem & t);
    friend std::ostream & operator<<(std::ostream & os, theorem & t);
};

#endif