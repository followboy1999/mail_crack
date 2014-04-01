

#ifndef _ZSYSINFO
#define _ZSYSINFO

#pragma warning(disable:4786) 
#include <string>
#include <deque>
using namespace std;

#include "ZThunk.h"
#include "Tlhelp32.h"

#include <winsock2.h>
#pragma comment(lib,"WS2_32.lib")

class ZSysInfo  
{
public:

	ZSysInfo();
	~ZSysInfo();
private:

	//此对像用于将回调函数封装成类成员函数
	ZThunk m_thunk;

/*-------------------------------------------------------------------------*/
private:

	SYSTEMTIME m_SYSTEMTIME;

public:

	//获取年,月,日,时,分,秒,毫秒(以整型值返回)
	int GetYear();
	int GetMonth();
	int GetDay();
	int GetHour();
	int GetMinute();
	int GetSecond();
	int GetMillisecond();

	/*
	获取年,月,日,时,分,秒,毫秒(以字符串值返回)
	FillZero:如果不足十是否为零填充
	*/
	string GetYear_str();
	string GetMonth_str(bool FillZero=true);
	string GetDay_str(bool FillZero=true);
	string GetHour_str(bool FillZero=true);
	string GetMinute_str(bool FillZero=true);
	string GetSecond_str(bool FillZero=true);
	string GetMillisecond_str(bool FillZero=true);

/*-------------------------------------------------------------------------*/

	/*
	获取操作系统版本
	返回值:
		  0 未知
		  1 win 98
		  2 win Me
		  3 win NT 3.51
		  4 win NT 4.0
		  5 win 2000
		  6 win xp
		  7 win 2003
	*/
	static int GetOSVersion();

/*-------------------------------------------------------------------------*/
private:

	//本机名称
	string m_LocalhostName;

public:

	//获取本机IP列表
	deque<string> GetLocalhostIP();

	//获取本机名称
	string GetLocalhostName();

/*-------------------------------------------------------------------------*/

public:

	//获取进程进息
	deque<PROCESSENTRY32> GetProcessInfo();
	
	//获取线程信息
	deque<THREADENTRY32> GetThreadInfo(unsigned int Pid);

	//根据进程名获取进程ID
	deque<int> GetProcessID(char* szProcessName);

	//根据PID获取进程名称
	string GetProcessName(int ProcessID);

	/*
	根据线程ID获取线程句柄,调用失败返回0xFFFFFFFF
	win98的Kernel32.dll不含有OpenThread函数,
	故此函数不能应用在win98环境下
	*/
	HANDLE ZSysInfo::GetThreadHandle(unsigned int ThreadID);

private:

	HWND m_HWND;

	typedef struct _CtrlInfo
	{ 
	  long CtrlID; 
	  long CtrlStyle; 
	} CTRLINFO,*PCTRLINFO;

private:

	//枚举子窗口回调函数
	bool EnumChildProc(HWND hwnd,LPARAM lParam);

public:

	//根据父句柄及控件ID获取句柄,没找到则返回0xFFFFFFFF
	HWND FindChildWindow(HWND hParent,long CtrlID,long CtrlStyle);
};

#endif

	

