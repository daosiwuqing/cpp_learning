//该脚本的作用：学习cpp的数据类型
#include <iostream>



using namespace std;

int main()
{
    ////1、基础数据类型
    ////1.1、整型
    // int n_int = INT_MAX;
    // short n_short = SHRT_MAX;
    // long n_long = LONG_MAX;
    // long long n_llong = LLONG_MAX;
    // cout << "n_int's type: " << typeid(n_int).name() << endl; // 该类型数据的名称
    // cout << "n_int's byte: " << sizeof(n_int) << " bytes." << endl; // 该类型数据所占字节大小
    // cout << "n_int's max value: " << n_int << endl; // 该类型数据所能容纳的最大值
    // cout << "n_short's type: " << typeid(n_short).name() << endl;
    // cout << "n_short's byte: " << sizeof(n_short) << " bytes." << endl;
    // cout << "n_short's max value: " << n_short << endl;
    // cout << "n_long's type: " << typeid(n_long).name() << endl;
    // cout << "n_long's byte: " << sizeof(n_long) << " bytes." << endl;
    // cout << "n_long's max value: " << n_long << endl;
    // cout << "n_llong's type: " << typeid(n_llong).name() << endl;
    // cout << "n_llong's bytes: " << sizeof(n_llong) << " bytes." << endl;
    // cout << "n_llong's max value: " << n_llong << endl;


    ////1.2、浮点数
    //float n_float = 10.0/3.0;
    //double n_double = 10.0/3.0;
    //long double n_ldouble = 10.0/3.0;
    //cout << "n_float's type: " << typeid(n_float).name() << endl; // 该类型数据的名称
    //cout << "n_float's byte: " << sizeof(n_float) << " bytes." << endl; // 该类型数据所占字节大小
    //cout << "n_double's type: " << typeid(n_double).name() << endl;
    //cout << "n_double's byte: " << sizeof(n_double) << " bytes." << endl;
    //cout << "n_ldouble's type: " << typeid(n_ldouble).name() << endl;
    //cout << "n_ldouble's bype: " << sizeof(n_ldouble) << " bytes." << endl;


    ////1.3、字符（char）型，本质上依然是整型，在计算机中把字符型转化为整型储存，只是输入输出时再把整型转化为字符型
    //char ch1 = '1';
    //int n1 = ch1;
    //char ch2 = ch1 + 1;
    //int n2 = ch2;
    //cout << "ch1's type: " << typeid(ch1).name() << endl;
    //cout << "The ASCII code for " << ch1 << " is " << n1 << endl; // ch1的数值编码
    //cout << &ch1 << endl;
    //cout << &n1 << endl; // ch1的内存地址
    //cout << "ch2's type: " << typeid(ch2).name() << endl;
    //cout << "The ASCII code for " << ch2 << " is " << n2 << endl;
    //cout << &ch2 << endl;
    //cout << &n2 << endl;



    ////2、数组
    ////2.1、一维数组
    //int array_int[] = {1, 12, 3, 24}; // 数值数组
    //char array_char1[] = {'a', 'b', 'c', 'd'}; // not a string，字符数组
    //char array_char2[] = {'a', 'b', 'c', 'd', '\0'}; // a string
    //char array_char3[] = { "abcd" }; // a string
    //char array_char4[] = "abcd"; // a string
    //cout << typeid(array_int).name() << endl;
    //cout << array_int << endl; //数值数组本身是其储存的数据的地址，所以在其前边加取地址符没有效果
    //cout << array_int[0] << endl;
    //cout << &array_int << endl;
    //cout << typeid(array_char1).name() << endl;
    //cout << array_char1 << endl; //字符数组本身是其储存的字符加一些无意义的字符，所以在其前边加取地址符会取出字符数组储存的数据的地址
    //cout << array_char1[0] << endl;
    //cout << &array_char1 << endl;
    //cout << typeid(array_char2).name() << endl;
    //cout << array_char2 << endl; //字符串本身是其储存的字符
    //cout << array_char2[0] << endl;
    //cout << &array_char2 << endl;
    //cout << typeid(array_char3).name() << endl;
    //cout << array_char3 << endl;
    //cout << array_char3[0] << endl;
    //cout << &array_char3 << endl;
    //cout << typeid(array_char4).name() << endl;
    //cout << array_char4 << endl;
    //cout << array_char4[0] << endl;
    //cout << &array_char4 << endl;


    ////2.2、二维数组
    //int array_int[3][4] = { {1,2,3,4}, {4,5,6,7},{7,8,9,10} };
    //char array_char1[2][3] = { {'a','b','c'}, {'d','e','f'} };
    //char array_char2[2][4] = { {'a', 'b', 'c','\0'}, {'d','e','f','\0'} };
    //char array_char3[2][4] = { "abc", "def"};
    //cout << typeid(array_int).name() << endl;
    //cout << array_int << endl;
    //cout << array_int[0] << endl;
    //cout << array_int[0][0] << endl;
    //cout << &array_int << endl;
    //cout << typeid(array_char1).name() << endl;
    //cout << array_char1 << endl;
    //cout << array_char1[0] << endl;
    //cout << array_char1[0][0] << endl;
    //cout << &array_char1 << endl;
    //cout << typeid(array_char2).name() << endl;
    //cout << array_char2 << endl;
    //cout << array_char2[0] << endl;
    //cout << array_char2[0][0] << endl;
    //cout << &array_char2 << endl;
    //cout << typeid(array_char3).name() << endl;
    //cout << array_char3 << endl;
    //cout << array_char3[0] << endl;
    //cout << array_char3[0][0] << endl;
    //cout << &array_char3 << endl;



    ////3、结构体
    //struct my_struct
    //{
    //    int n_int;
    //    float n_float;
    //    char ch1;
    //};
    //my_struct struct1 = { 1, 1.1, 'a' };
    //cout << struct1.n_int << "、"  << struct1.n_float << "、" << struct1.ch1 << endl;



    ////4、指针
    ////4.1情形1
    //int n1 = 9;
    //int* pt1;
    //pt1 = &n1;
    //cout << "pt1's type: " << typeid(pt1).name() << endl;
    //cout << "*pt1's type: " << typeid(*pt1).name() << endl;
    //cout << "n1's value = " << n1 << endl;
    //cout << "value pointed by pt1 = " << *pt1 << endl;
    //cout << "n1's address = " << &n1 << endl;
    //cout << "n1's address = " << pt1 << endl;
    //cout << "pt1's address = " << &pt1 << endl;


    ////4.2情形2
    //int* pt2 = new int;
    //*pt2 = 9;
    //cout << "pt2's type: " << typeid(pt2).name() << endl;
    //cout << "*pt2's type: " << typeid(*pt2).name() << endl;
    //cout << "pt2's value = " << pt2 << endl;
    //cout << "pt2's address = " << &pt2 << endl;
    //cout << "value pointed by pt2 = " << *pt2 << endl;
    //delete pt2;


    ////4.3情形3
    //const char* pt3 = "zhaobo";
    //cout << "pt3's type: " << typeid(pt3).name() << endl;
    //cout << "*pt3's type: " << typeid(*pt3).name() << endl;
    //cout << "pt3's value = " << pt3 << endl;
    //cout << "pt3's address = " << &pt3 << endl;
    //cout << "value pointed by pt3 = " << *pt3 << endl;
    //cout << "(pt3 + 1)'s value = " << pt3 + 1 << endl;
    //cout << "(pt3 + 1)'s address = " << &pt3 + 1 << endl;
    //cout << "value pointed by (pt3 + 1) = " << *(pt3 + 1) << endl;



    ////5、const限定符
    //const int C1 = 12; //const和数据类型（如：int）可以随意调换位置，const本质上是在修饰C1、C2
    //int const C2 = 13;
    //cout << C1 << "、" << C2 << endl;



    ////6、指针&数组
    ////6.1、情形1
    //int array_int[] = {1, 12, 3, 24};
    //int* p_int = array_int;
    //cout << "p_int's type: " << typeid(p_int).name() << endl;
    //cout << "*p_int's type: " << typeid(*p_int).name() << endl;
    //cout << p_int << endl;
    //cout << p_int[0] << endl;
    //cout << p_int[1] << endl;
    //cout << *p_int << endl;
    //cout << &p_int << endl;
    //cout << array_int << endl;
    //cout << &array_int << endl;


    ////6.2、情形2
    // char array_char1[] = {'a', 'b', 'c', 'd'};
    // char* p_char1 = array_char1;
    // cout << "p_char1's type: " << typeid(p_char1).name() << endl;
    // cout << "*p_char1's type: " << typeid(*p_char1).name() << endl;
    // cout << p_char1 << endl;
    // cout << p_char1[0] << endl;
    // cout << p_char1[1] << endl;
    // cout << *p_char1 << endl;
    // cout << &p_char1 << endl;
    // cout << array_char1 << endl;
    // cout << &array_char1 << endl;


    ////6.3、情形3
    // char array_char2[] = "abcd"; // 也可以是char array_char2[] = {'a', 'b', 'c', 'd', '\0'}或char array_char2[] = { "abcd" };
    // char* p_char2 = array_char2;
    // cout << "p_char2's type: " << typeid(p_char2).name() << endl;
    // cout << "*p_char2's type: " << typeid(*p_char2).name() << endl;
    // cout << p_char2 << endl;
    // cout << p_char2[0] << endl;
    // cout << p_char2[1] << endl;
    // cout << *p_char2 << endl;
    // cout << &p_char2 << endl;
    // cout << array_char2 << endl;
    // cout << &array_char2 << endl;


    ////6.4、情形4
    // char* p_char3[] = { "abc", "bcd", "cde" }; // 也可以是char* p_char3[] = { {'a', 'b', 'c','\0'}, {'b','c','d','\0'} , {'c','d','e','\0'} }或char* p_char3[] = { {"abc"}, {"def"} , {"cde"} };
    // cout << "p_char3's type: " << typeid(p_char3).name() << endl;
    // cout << "*p_char3's type: " << typeid(*p_char3).name() << endl;
    // cout << p_char3 << endl;
    // cout << p_char3[0] << endl;
    // cout << p_char3[1] << endl;
    // cout << *p_char3 << endl;
    // cout << &p_char3 << endl;
    ////情形4的本质原理
    // char* pt1 = "abc";
    // char* pt2 = "bcd";
    // char* pt3 = "cde";
    // char* p_char3[] = { pt1, pt2, pt3 };


    ////6.5、情形5
    // const char array_char4[] = "abcd";
    // const char* p_char4 = array_char4; // const在*号之前，此时指针可以指向一个const变量也可以指向一个非const变量，但const变量只能被指向const变量的指针指向
    // cout << "p_char4's type: " << typeid(p_char4).name() << endl;
    // cout << "*p_char4's type: " << typeid(*p_char4).name() << endl;
    // cout << p_char4 << endl;
    // cout << p_char4[0] << endl;
    // cout << p_char4[1] << endl;
    // cout << *p_char4 << endl;
    // cout << &p_char4 << endl;
    // cout << array_char4 << endl;
    // cout << &array_char4 << endl;


    ////6.6、情形6
    //const char* p_char5[] = { "abc", "bcd", "cde" }; // 也可以是const char* p_char5[] = { {'a', 'b', 'c','\0'}, {'b','c','d','\0'} , {'c','d','e','\0'} }或const char* p_char5[] = { {"abc"}, {"def"} , {"cde"} };
    //cout << "p_char5's type: " << typeid(p_char5).name() << endl;
    //cout << "*p_char5's type: " << typeid(*p_char5).name() << endl;
    //cout << p_char5 << endl;
    //cout << p_char5[0] << endl;
    //cout << p_char5[1] << endl;
    //cout << *p_char5 << endl;
    //cout << &p_char5 << endl;
    ////情形6的本质原理
    //const char* pt1 = "abc";
    //const char* pt2 = "bcd";
    //const char* pt3 = "cde";
    //const char* p_char5[] = { pt1, pt2, pt3 };



    ////7、指针&结构体
    ////7.1情形1
    //struct my_struct1
    //{
    //    int n_int;
    //    float n_float;
    //    char ch1;
    //};
    //my_struct1 struct1{1, 1.1, 'a'};
    //my_struct1* pt1;
    //pt1 = &struct1;
    //cout << pt1->n_int << "、" << pt1->n_float << "、" << pt1->ch1 << "、" << endl;
    
    
    ////7.2情形2
    //struct my_struct2
    //{
    //    int n_int;
    //    float n_float;
    //    char ch1;
    //    my_struct2* pt_next;
    //};
    //my_struct2 struct2{ 1, 1.1, 'a', NULL};
    //my_struct2 struct3{ 2, 2.2, 'b', &struct2};
    //cout << struct2.pt_next << endl;
    //cout << &struct2 << endl;
    //cout << &struct2.n_int << endl;
    //cout << struct3.pt_next << endl;



    ////8、指针&const
    ////8.1、指向const变量的指针，const在*号之前，此时指针可以指向一个const变量也可以指向一个非const变量，但const变量只能被指向const变量的指针指向
    //const int a = 10;
    //int b = 20;
    //const int * pt1 = &a;
    //cout << &a << *pt1 << endl;
    //pt1 = &b;
    //cout << &b << *pt1 << endl;
    
    
    ////8.2、被const修饰的指针，const在*号之后，此时被const修饰的指针的指向不能被改变
    //int c = 30;
    //int * const pt2 = &c;



    return 0;
}