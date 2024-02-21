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
    void initSuf()
    {
        // insert P|!P into prefix
        // after swap, it will be suffix
        Node *P = new Node('P', nullptr, nullptr);
        pre.push_back(P); pre.push_back(P);
        Node *tp = pre.back(); pre.pop_back();
        Node *tmp = new Node('!', 0, tp);
        pre.push_back(tmp);
        Node *tp1 = pre.back(); pre.pop_back();
        Node *tp2 = pre.back(); pre.pop_back();
        tmp = new Node('|', tp2, tp1);
        pre.push_back(tmp);
    }
    void init()
    {
        for(auto& it : suf_expression)
        {
            if(isOp(it))
            {
                if(&it == &suf_expression.back() && it == '>')
                {
                    Node *tp = pre.back();
                    pre.pop_back();
                    suf.push_back(tp);
                    break;
                } // split logical expression
                if(isRightOp(it))
                {
                    Node *tp = pre.back();
                    pre.pop_back();
                    Node *tmp = new Node(it, 0, tp);
                    pre.push_back(tmp);
                }
                else
                {
                    Node *tp1 = pre.back();
                    pre.pop_back();
                    Node *tp2 = pre.back();
                    pre.pop_back();
                    Node *tmp = new Node(it, tp2, tp1);
                    pre.push_back(tmp);
                }
            }
            else
            {
                Node *tmp = new Node(it, nullptr, nullptr);
                pre.push_back(tmp);
            }
        }
        if(suf.empty())
        {
            std::swap(pre, suf);
            initSuf();
        }
    }
    bool check(std::list<Node*> q)
    {
        for(auto it : q) if(isOp(it->c)) return 0;
        return 1;
    }
    bool prove_p(std::list<Node*> ql, std::list<Node*> qr)
    {
        // pop_back push_front
        if(!check(ql))
        {
            Node *tp = ql.back();
            if(isOp(tp->c))
            {
                auto tql = ql, tqr = qr;
                auto tql2 = ql, tqr2 = qr;
                tql.pop_back(); tql2.pop_back();
                if(isRightOp(tp->c))
                {
                    tqr.push_front(tp->rs);
                    return prove_p(tql, tqr);
                }
                else if(tp->c == '&')
                {
                    tql.push_front(tp->ls);
                    tql.push_front(tp->rs);
                    return prove_p(tql, tqr);
                }
                else if(tp->c == '|')
                {
                    tql.push_front(tp->ls);
                    tql2.push_front(tp->rs);
                    return prove_p(tql, tqr) && prove_p(tql2, tqr);
                }
                else if(tp->c == '>')
                {
                    tql2.push_front(tp->rs);
                    tqr2.push_front(tp->ls);
                    return prove_p(tql2, tqr) && prove_p(tql, tqr2);
                }
                else if(tp->c == '=')
                {
                    tql2.push_front(tp->ls);
                    tql2.push_front(tp->rs);
                    tqr2.push_front(tp->ls);
                    tqr2.push_front(tp->rs);
                    return prove_p(tql2, tqr) && prove_p(tql, tqr2);
                }
            }
            else
            {
                auto tql = ql, tqr = qr;
                tql.pop_back();
                tql.push_front(tp);
                return prove_p(tql, tqr);
            }
        }
        if(!check(qr))
        {
            Node *tp = qr.back();
            if(isOp(tp->c))
            {
                auto tql = ql, tqr = qr;
                auto tql2 = ql, tqr2 = qr;
                tqr.pop_back(); tqr2.pop_back();
                if(isRightOp(tp->c))
                {
                    tql.push_front(tp->rs);
                    return prove_p(tql, tqr);
                }
                else if(tp->c == '&')
                {
                    tqr.push_front(tp->ls);
                    tqr2.push_front(tp->rs);
                    return prove_p(tql, tqr) && prove_p(tql, tqr2);
                }
                else if(tp->c == '|')
                {
                    tqr.push_front(tp->ls);
                    tqr.push_front(tp->rs);
                    return prove_p(tql, tqr);
                }
                else if(tp->c == '>')
                {
                    tql.push_front(tp->ls);
                    tqr.push_front(tp->rs);
                    return prove_p(tql, tqr);
                }
                else if(tp->c == '=')
                {
                    tql.push_front(tp->ls);
                    tqr.push_front(tp->rs);
                    tql2.push_front(tp->rs);
                    tqr2.push_front(tp->ls);
                    return prove_p(tql, tqr) && prove_p(tql2, tqr2);
                }
            }
            else
            {
                auto tql = ql, tqr = qr;
                tqr.pop_back();
                tqr.push_front(tp);
                return prove_p(tql, tqr);
            }
        }
        std::set<char> st;
        for(auto it : ql) st.insert(it->c);
        for(auto it : qr) if(st.find(it->c) != st.end()) return 1;
        return 0;
    }
public:
    theorem();
    explicit theorem(const std::string & x);
    theorem & operator=(const std::string & x);
    theorem & operator=(const theorem & x);
    ~theorem();
    bool prove();
    friend std::istream & operator>>(std::istream & is, theorem & t);
    friend std::ostream & operator<<(std::ostream & os, theorem & t);
};

#endif