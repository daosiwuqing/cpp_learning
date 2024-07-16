#include <algorithm>
#include "my_vector.h"



Vector::Vector()
{
    cout << "Vector start!" << endl;
}


Vector::~Vector()
{
    cout << "Vector end!" << endl;
}


bool Vector::is_element_in_vector(vector<string> vector1, string element1) //判断vector中是否存在某个元素
{
    vector<string>::iterator iter;
    iter = std::find(vector1.begin(), vector1.end(), element1);
    if (iter != vector1.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}


int Vector::find_pos_vector(vector<string> vector1, string element1) //寻找元素在vector的位置
{
    vector<string>::iterator iter;
    iter = std::find(vector1.begin(), vector1.end(), element1);
    if(iter == vector1.end())
    {
        return -1;
    }
    else
    {
        return std::distance(vector1.begin(), iter);
    }
}


vector<string> Vector::unique_element_in_vector(vector<string> vector1) //容器vector中去重
{
    vector<string>::iterator vector_iter;
    std::sort(vector1.begin(), vector1.end());
    vector_iter = std::unique(vector1.begin(), vector1.end());
    if (vector_iter != vector1.end())
    {
        vector1.erase(vector_iter, vector1.end());
    }

    return vector1;
}


vector<string> Vector::vectors_intersection(vector<string> vector1, vector<string> vector2) //两个vector求交集
{
	vector<string> vector3;
	std::sort(vector1.begin(), vector1.end());
	std::sort(vector2.begin(), vector2.end());
	std::set_intersection(vector1.begin(), vector1.end(), vector2.begin(), vector2.end(), back_inserter(vector3)); //求交集

	return vector3;
}


vector<string> Vector::vectors_set_union(vector<string> vector1, vector<string> vector2) //两个vector并集
{
	vector<string> vector3;
	std::sort(vector1.begin(), vector1.end());
	std::sort(vector2.begin(), vector2.end());
	std::set_union(vector1.begin(), vector1.end(), vector2.begin(), vector2.end(), back_inserter(vector3)); //求并集

	return vector3;
}