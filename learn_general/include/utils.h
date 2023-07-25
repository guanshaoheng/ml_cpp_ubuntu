//
// Created by shguan on 7/21/23.
//

#ifndef ML_CPP_UTILS_H
#define ML_CPP_UTILS_H

#include <iostream>
using namespace std;

template <class T>
T MaxElement(T a[], int size) //size是数组元素个数
{
    T tmpMax = a[0];
    for (int i = 1; i < size; ++i)
        if (tmpMax < a[i])
            tmpMax = a[i];
    return tmpMax;
}


class CFraction //分数类
{
    int numerator;   //分子
    int denominator; //分母
public:
    CFraction(int n, int d) :numerator(n), denominator(d) { };
    bool operator <(const CFraction & f) const
    {//为避免除法产生的浮点误差，用乘法判断两个分数的大小关系
        if (denominator * f.denominator > 0)
            return numerator * f.denominator < denominator * f.numerator;
        else
            return numerator * f.denominator > denominator * f.numerator;
    }
    bool operator == (const CFraction & f) const
    {//为避免除法产生的浮点误差，用乘法判断两个分数是否相等
        return numerator * f.denominator == denominator * f.numerator;
    }
    friend ostream & operator <<(ostream & o, const CFraction & f);
};

#endif //ML_CPP_UTILS_H
