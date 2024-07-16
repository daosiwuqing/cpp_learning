#include <fstream> //基于文件的I/O
#include <sstream> //基于字符串的I/O
#include "my_data_frame.h"



Dataframe::Dataframe()
{
    cout << "Dataframe start!" << endl;
}


Dataframe::~Dataframe()
{
    cout << "Dataframe end!" << endl;
}


vector<vector<string>> Dataframe::get_dataframe(string path1) //从csv文件中获取dataframe数据
{
	fstream csv_data1(path1, ios::in); //读取csv ios::in；追加csv ios::app；写入csv ios::out

	if (!csv_data1.is_open())
	{
		cout << "Error: opening file fail" << endl;
	}
	else
	{
		string line1;
		vector<vector<string>> str_dataframe1;
		while (getline(csv_data1, line1))
		{
			stringstream ss1(line1);
			string str1;
			vector<string> array1;
			while (getline(ss1, str1, ','))
			{
				array1.push_back(str1);
			}
			str_dataframe1.push_back(array1);
		}
		return str_dataframe1;
	}

	csv_data1.close();
}