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
    cout << a << endl << a.prove();
    return 0;
}