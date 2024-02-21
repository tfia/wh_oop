// compile with wh_oop.cpp
#include<iostream>
#include<stdio.h>
#include<list>
#include<string>
#include<unordered_map>
#include<set>
#include"thm.h"

theorem::theorem()
{
    OP.clear(); opp.clear();
    OP.insert('!'); OP.insert('&'); OP.insert('|'); OP.insert('>'); OP.insert('=');
    ROP.insert('!');
	opp['('] = -1; opp[')'] = -1;
    opp['!'] = 4; opp['&'] = 3; opp['|'] = 2; opp['>'] = 1; opp['='] = 0;
}

theorem::theorem(const std::string & x)
{
    theorem();
    ori_expression = x;
    toInf();
    toSuf();
    init();
}

theorem & theorem::operator=(const std::string & x)
{
    theorem();
    ori_expression = x;
    toInf();
    toSuf();
    init();
    return *this;
}

theorem & theorem::operator=(const theorem & x)
{
    theorem();
    ori_expression = x.ori_expression;
    toInf();
    toSuf();
    init();
    return *this;
}

theorem::~theorem()
{
    while(!pre.empty())
    {
        auto tmp = pre.back();
        pre.pop_back();
        delete tmp;
    }
    while(!suf.empty())
    {
        auto tmp = suf.back();
        suf.pop_back();
        delete tmp;
    }
}

bool theorem::prove()
{
    return prove_p(pre, suf);
}

std::istream & operator>>(std::istream & is, theorem & t)
{
    std::getline(is, t.ori_expression);
    t.toInf();
    t.toSuf();
    t.init();
    return is;
}

std::ostream & operator<<(std::ostream & os, theorem & t)
{
    os << t.suf_expression;
    return os;
}