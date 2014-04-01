

#ifndef _ZSTRING
#define _ZSTRING

#pragma warning(disable:4786) 
#include <string>
#include <deque>
#include <functional>
#include <algorithm>
using namespace std;

class ZString  
{
public:
	ZString();
	~ZString();

	//根据拆分标记对源串进行拆分
	deque<string> Splitter(string strSource,const string strFlag);

	//去除字符串中所有的空格
	string EraseSpace(const string str);

	//去除前面和后面的空格
	string TrimAll(const string str);

	//去掉前面空格
	string TrimLeft(const string str);

	//去掉后面空格
	string TrimRight(const string str);
};

#endif
