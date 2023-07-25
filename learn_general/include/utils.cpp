//
// Created by shguan on 7/21/23.
//
#include "utils.h"

ostream & operator <<(ostream & o, const CFraction & f)
{//重载 << 使得分数对象可以通过cout输出
    o << f.numerator << "/" << f.denominator; //输出"分子/分母" 形式
    return o;
}