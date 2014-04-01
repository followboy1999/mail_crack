

#include "stdafx.h"
#include "ZString.h"


ZString::ZString()
{

}

ZString::~ZString()
{

}

deque<string> ZString::Splitter(string strSource,const string strFlag)
{
	deque<string> dqResult;
	
	//参数检查
	if(strSource==strFlag)
	{
		dqResult.push_back(strSource);
		return dqResult;
	}
	else if(strSource.length()<=strFlag.length())
	{
		return dqResult;
	}

	//首期处理
	if(strSource.substr(strSource.length()-strFlag.length())!=strFlag)
	{
		strSource+=strFlag;
	}

	string strTmp;
	int Pos=strSource.find(strFlag);

	while(Pos!=-1)
	{
		dqResult.push_back(strSource.substr(0,Pos));
		strSource.erase(0,Pos+strFlag.length());
		Pos=strSource.find(strFlag);
	}

	return dqResult;
}

string ZString::EraseSpace(const string str)
{
	string strTmp=str;
	strTmp.erase(remove_if(strTmp.begin(),strTmp.end(),ptr_fun(::isspace)),strTmp.end());
	return strTmp;
}

string ZString::TrimLeft(const string str)
{
	string strTmp=str;
	string::iterator pos=find_if(strTmp.begin(),strTmp.end(),not1(ptr_fun(::isspace)));
	strTmp.erase(strTmp.begin(), pos);
	return strTmp;
}

string ZString::TrimRight(const string str)
{
	string strTmp=str;
	string::reverse_iterator rpos = find_if(strTmp.rbegin(),strTmp.rend(),not1(ptr_fun(::isspace)));   
	strTmp.erase(rpos.base(),strTmp.end());
	return strTmp;
}

string ZString::TrimAll(const string str)
{
	return TrimLeft(TrimRight(str));
}
