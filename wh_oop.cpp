#include<iostream>
#include<stdio.h>
#include<list>
#include<string>
#include<unordered_map>
#include<set>
#include"thm.h"

using std::cin, std::cout, std::endl;

int main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    theorem a;
    cin >> a;
    cout << a << endl << a.prove() << endl << "---" << endl;
    std::string s;
    cin >> s;
    theorem b;
    b = theorem(s);
    cout << b << endl << b.prove() << endl << "---" << endl;
    cin >> s;
    theorem c = s;
    cout << c << endl << c.prove() << endl << "---" << endl;
    return 0;
}