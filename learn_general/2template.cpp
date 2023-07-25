//
// Created by shguan on 7/21/23.
//
#include <iostream>
#include "./include/utils.h"
using namespace std;


int main()
{
    int a[5] = { 1,5,2,3,4 };
    CFraction f[4] = { CFraction(8,6),CFraction(-8,4),
                       CFraction(3,2), CFraction(5,6) };
    cout << MaxElement(a, 5) << endl;
    cout << MaxElement(f, 4) << endl;
    return 0;
}

