

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

	//���ݲ�ֱ�Ƕ�Դ�����в��
	deque<string> Splitter(string strSource,const string strFlag);

	//ȥ���ַ��������еĿո�
	string EraseSpace(const string str);

	//ȥ��ǰ��ͺ���Ŀո�
	string TrimAll(const string str);

	//ȥ��ǰ��ո�
	string TrimLeft(const string str);

	//ȥ������ո�
	string TrimRight(const string str);
};

#endif
