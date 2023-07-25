
#include <iostream>
using namespace std;


template<class T>
void Swap(T & x, T & y)
{
    T tmp = x;
    x = y;
    y = tmp;
}


template <class T>
T Inc(int n)
{
    return 1 + n;
}

int main()
{
    // 采用函数模板定义输入
    int n = 1, m = 2;
    cout<< "n: " << n << endl;
    cout<< "m: " << m << endl;
    Swap(n, m);  //编译器自动生成 void Swap (int &, int &)函数
    cout<< "n: " << n << endl;
    cout<< "m: " << m << endl;

    double f = 1.2, g = 2.3;
    cout<< "f: " << f << endl;
    cout<< "g: " << g << endl;
    Swap(f, g);  //编译器自动生成 void Swap (double &, double &)函数
    cout<< "f: " << f << endl;
    cout<< "g: " << g << endl;


    // 采用函数模板定义输出类型
    cout<< endl;
    cout << Inc<float>(4) / 2;

    return 0;
}
