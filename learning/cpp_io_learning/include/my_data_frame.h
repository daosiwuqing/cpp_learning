#ifndef __DATA_FRAME_H__
#define __DATA_FRAME_H__

#include <iostream> //基于控制台的I/O
#include <string>
#include <vector>



using namespace std;

class Dataframe
{
	private:

	public:
		Dataframe();
		~Dataframe();
		vector<vector<string>> get_dataframe(string path);
};



#endif