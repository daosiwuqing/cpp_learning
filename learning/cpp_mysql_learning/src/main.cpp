#include <iostream>
#include <string>
#include "mysql.h"




using namespace std;
MYSQL mysql1; //创建MYSQL对象mysql1
bool connect_database();
bool manage_database();



int main()
{
	connect_database();
	manage_database();

	//获取结果集
	MYSQL_RES* result = mysql_store_result(&mysql1);
	if (!result)
	{
		cout << "mysql_use_result faied! " << mysql_error(&mysql1) << endl;
	}
	//遍历结果集
	MYSQL_ROW row;
	while (row = mysql_fetch_row(result))
	{
		unsigned long* lens = mysql_fetch_lengths(result);
		cout << lens[0] << "[" << row[0] << "," << row[1] << "]" << endl;
	}
	//清理结果集
	mysql_free_result(result);
	mysql_close(&mysql1);
	mysql_library_end();

	return true;
}



//连接数据库
bool connect_database()
{
	//初始化mysql
	mysql_init(&mysql1);
	string host = "localhost";
	string user = "root";
	string psw = "09221017ZB";
	string db_base = "cpp_mysql";
	int port = 3306;
	//返回false则连接失败，返回true则连接成功
	if (!(mysql_real_connect(&mysql1, host.c_str(), user.c_str(), psw.c_str(), db_base.c_str(), port, NULL, 0))) //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等）
	{
        cout << "Connecting Failed: " << mysql_error(&mysql1) << endl;

		return false;
	}
	else
	{
        cout << "Connecting Succeed!" << endl;

		return true;
	}
}



//管理数据库
bool manage_database()
{
	//string sql = "DROP TABLE IF EXISTS `test1`"; //删除表
	//string sql = "CREATE TABLE IF NOT EXISTS test1 (`date` DATE NOT NULL, `code` VARCHAR(32), `open` double, `high` double, `low` double, `close` double, `volume` double, `turnover` double, `open_interest` double);"; //创建表
	//string sql = "INSERT INTO test1 (date, code, open, high, low, close, volume, turnover, open_interest) VALUES('2023-01-01', 'AU', '1', '2', '3', '4', '5', '6', '7');"; //插入数据
	string sql = "SELECT * FROM test1;"; //查询表
	int re = mysql_query(&mysql1, sql.c_str());
	if (re != 0)
	{
		cout << "Failed!: " << mysql_error(&mysql1) << endl;
	}

	return true;
}


