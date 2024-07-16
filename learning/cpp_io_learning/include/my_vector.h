#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>
#include <string>
#include <vector>



using namespace std;

class Vector
{
	private:

	public:
		Vector();
		~Vector();
		bool is_element_in_vector(vector<string> vector1, string element1);
		int find_pos_vector(vector<string> vector1, string element1);
        vector<string> unique_element_in_vector(vector<string> vector1);
        vector<string> vectors_intersection(vector<string> vector1, vector<string> vector2);
        vector<string> vectors_set_union(vector<string> vector1, vector<string> vector2);
};



#endif