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
    OP.insert('!'); OP.insert('&'); OP.insert('|'); OP.insert('>'); OP.insert('=');
    ROP.insert('!');
	opp['('] = -1; opp[')'] = -1;
    opp['!'] = 4; opp['&'] = 3; opp['|'] = 2; opp['>'] = 1; opp['='] = 0;
}

std::istream & operator>>(std::istream & is, theorem & t)
{
    is >> t.ori_expression;
    t.toInf();
    t.toSuf();
    return is;
}

std::ostream & operator<<(std::ostream & os, theorem & t)
{
    os << t.suf_expression;
    return os;
}