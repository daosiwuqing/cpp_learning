#include <iostream>
#include <vector>



using namespace std;

int main()
{
    vector<int> vector1;
    for (int i = 0; i < 10; ++i)
    {
        vector1.push_back(i);
    }

    //正向迭代器
    //容器类名::iterator 迭代器名;
/*     vector<int>::iterator iter1;
    for (iter1 = vector1.begin(); iter1 != vector1.end(); ++iter1)
    {
        cout << *iter1 << endl; //"*迭代器名"表示迭代器指向的元素
        *iter1 *= 2; //修改vector1中的元素
    } */

    //反向迭代器
    //容器类名::reverse_iterator 迭代器名;
/*     vector<int>::reverse_iterator iter2;
    for (iter2 = vector1.rbegin(); iter2 != vector1.rend(); ++iter2)
    {
        cout << *iter2 << endl;
    } */

    //常量正向迭代器，与普通迭代器相比，普通迭代器可读可写，常量迭代器只能读取容器元素，不能修改容器元素
    //容量类名::const_iterator 迭代器名;

    //常量反向迭代器
    //容器类名::const_reverse_iterator 迭代器名;


    return 0;
}


