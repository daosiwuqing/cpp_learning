#include "my_data_frame.h"
#include "my_vector.h"



using namespace std;

int main()
{
	string path1 = "D:/cpp_learning/learning/cpp_io_learning/others/test1.csv";

	Dataframe dataframe1;
	Vector vector1;

	vector<vector<string>> df1;
	vector<string> v1;

	df1 = dataframe1.get_dataframe(path1);
	for (int i = 0; i < df1.size(); ++i)
	{
		v1.push_back(df1[i][0]);
	}

	int row_number1;
	row_number1 = vector1.find_pos_vector(v1, "2004/12/10");
	cout << row_number1 << endl;
	if (row_number1 == -1)
	{
		cout << "can't find the data!" << endl;
	}
	else
	{
		for (int i = 0; i < df1[row_number1].size(); ++i)
		{
			cout << df1[row_number1][i] << endl;
		}
	}

	return 0;
}


