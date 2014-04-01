

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

	//�˶������ڽ��ص�������װ�����Ա����
	ZThunk m_thunk;

/*-------------------------------------------------------------------------*/
private:

	SYSTEMTIME m_SYSTEMTIME;

public:

	//��ȡ��,��,��,ʱ,��,��,����(������ֵ����)
	int GetYear();
	int GetMonth();
	int GetDay();
	int GetHour();
	int GetMinute();
	int GetSecond();
	int GetMillisecond();

	/*
	��ȡ��,��,��,ʱ,��,��,����(���ַ���ֵ����)
	FillZero:�������ʮ�Ƿ�Ϊ�����
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
	��ȡ����ϵͳ�汾
	����ֵ:
		  0 δ֪
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

	//��������
	string m_LocalhostName;

public:

	//��ȡ����IP�б�
	deque<string> GetLocalhostIP();

	//��ȡ��������
	string GetLocalhostName();

/*-------------------------------------------------------------------------*/

public:

	//��ȡ���̽�Ϣ
	deque<PROCESSENTRY32> GetProcessInfo();
	
	//��ȡ�߳���Ϣ
	deque<THREADENTRY32> GetThreadInfo(unsigned int Pid);

	//���ݽ�������ȡ����ID
	deque<int> GetProcessID(char* szProcessName);

	//����PID��ȡ��������
	string GetProcessName(int ProcessID);

	/*
	�����߳�ID��ȡ�߳̾��,����ʧ�ܷ���0xFFFFFFFF
	win98��Kernel32.dll������OpenThread����,
	�ʴ˺�������Ӧ����win98������
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

	//ö���Ӵ��ڻص�����
	bool EnumChildProc(HWND hwnd,LPARAM lParam);

public:

	//���ݸ�������ؼ�ID��ȡ���,û�ҵ��򷵻�0xFFFFFFFF
	HWND FindChildWindow(HWND hParent,long CtrlID,long CtrlStyle);
};

#endif

	

