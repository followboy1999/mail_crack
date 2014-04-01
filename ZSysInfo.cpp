

#include "stdafx.h"
#include "ZSysInfo.h"

ZSysInfo::ZSysInfo()
{
	
}

ZSysInfo::~ZSysInfo()
{

}

int ZSysInfo::GetYear()
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	return this->m_SYSTEMTIME.wYear;
}

int ZSysInfo::GetMonth()
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	return this->m_SYSTEMTIME.wMonth;
}

int ZSysInfo::GetDay()
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	return this->m_SYSTEMTIME.wDay;
}

int ZSysInfo::GetHour()
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	if(this->m_SYSTEMTIME.wHour+8>=24)
		return this->m_SYSTEMTIME.wHour+8-24;
	else
		return this->m_SYSTEMTIME.wHour+8;
}

int ZSysInfo::GetMinute()
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	return this->m_SYSTEMTIME.wMinute;
}

int ZSysInfo::GetSecond()
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	return this->m_SYSTEMTIME.wSecond;
}

int ZSysInfo::GetMillisecond()
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	return this->m_SYSTEMTIME.wMilliseconds;
}

string ZSysInfo::GetYear_str()
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	string strYear;
	char Temp[5];
	memset(Temp,0,5);
	itoa(this->m_SYSTEMTIME.wYear,Temp,10);
	strYear=Temp;
	return strYear;
}

string ZSysInfo::GetMonth_str(bool FillZero)
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	string strMonth;
	char Temp[3];
	memset(Temp,0,3);
	itoa(this->m_SYSTEMTIME.wMonth,Temp,10);
	if(FillZero)
	{
		if(this->m_SYSTEMTIME.wMonth<10)
		{
			strMonth="0";
			strMonth+=Temp;
		}
		else
		{
			strMonth=Temp;
		}
	}
	else
	{
		strMonth=Temp;
	}
	return strMonth;
}

string ZSysInfo::GetDay_str(bool FillZero)
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	string strDay;
	char Temp[3];
	memset(Temp,0,3);
	itoa(this->m_SYSTEMTIME.wDay,Temp,10);
	if(FillZero)
	{
		if(this->m_SYSTEMTIME.wDay<10)
		{
			strDay="0";
			strDay+=Temp;
		}
		else
		{
			strDay=Temp;
		}
	}
	else
	{
		strDay=Temp;
	}
	return strDay;
}

string ZSysInfo::GetHour_str(bool FillZero)
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	string strHour;
	char Temp[3];
	memset(Temp,0,3);
	if(this->m_SYSTEMTIME.wHour+8>=24)
		itoa(this->m_SYSTEMTIME.wHour+8-24,Temp,10);
	else
		itoa(this->m_SYSTEMTIME.wHour+8,Temp,10);

	if(FillZero)
	{
		if(this->m_SYSTEMTIME.wHour+8>=24)
		{
			if(this->m_SYSTEMTIME.wHour+8-24<10)
			{
				strHour="0";
				strHour+=Temp;
			}
			else
			{
				strHour=Temp;
			}
		}
		else
		{
			if(this->m_SYSTEMTIME.wHour+8<10)
			{
				strHour="0";
				strHour+=Temp;
			}
			else
			{
				strHour=Temp;
			}
		}
	}
	else
	{
		strHour=Temp;
	}
	return strHour;
}

string ZSysInfo::GetMinute_str(bool FillZero)
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	string strMinute;
	char Temp[3];
	memset(Temp,0,3);
	itoa(this->m_SYSTEMTIME.wMinute,Temp,10);
	if(FillZero)
	{
		if(this->m_SYSTEMTIME.wMinute<10)
		{
			strMinute="0";
			strMinute+=Temp;
		}
		else
		{
			strMinute=Temp;
		}
	}
	else
	{
		strMinute=Temp;
	}
	return strMinute;
}

string ZSysInfo::GetSecond_str(bool FillZero)
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	string strSecond;
	char Temp[3];
	memset(Temp,0,3);
	itoa(this->m_SYSTEMTIME.wSecond,Temp,10);
	if(FillZero)
	{
		if(this->m_SYSTEMTIME.wSecond<10)
		{
			strSecond="0";
			strSecond+=Temp;
		}
		else
		{
			strSecond=Temp;
		}
	}
	else
	{
		strSecond=Temp;
	}
	return strSecond;
}

string ZSysInfo::GetMillisecond_str(bool FillZero)
{
	::GetSystemTime(&this->m_SYSTEMTIME);
	string strMillisecond;
	char Temp[5];
	memset(Temp,0,5);
	itoa(this->m_SYSTEMTIME.wMilliseconds,Temp,10);
	if(FillZero)
	{
		if(strlen(Temp)==1)
		{
			strMillisecond="000";
			strMillisecond=Temp;
		}
		else if(strlen(Temp)==2)
		{
			strMillisecond="00";
			strMillisecond+=Temp;
		}
		else if(strlen(Temp)==3)
		{
			strMillisecond="0";
			strMillisecond+=Temp;
		}
		else
		{
			strMillisecond=Temp;
		}
	}
	else
	{
		strMillisecond=Temp;
	}
	return strMillisecond;
}

deque<PROCESSENTRY32> ZSysInfo::GetProcessInfo()
{
	deque<PROCESSENTRY32> dqProcess;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap == INVALID_HANDLE_VALUE) return dqProcess;
	PROCESSENTRY32 processentry32;
	processentry32.dwSize =sizeof(PROCESSENTRY32);

	if(Process32First(hProcessSnap,&processentry32))
	{
		do
		{
			dqProcess.push_back(processentry32);
		}while(::Process32Next(hProcessSnap,&processentry32));
	}
	CloseHandle(hProcessSnap);
	return dqProcess;
}

int ZSysInfo::GetOSVersion()
{
	OSVERSIONINFOEX osvi;
	osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);
	if(!GetVersionEx((OSVERSIONINFO *)&osvi))
	{
		return 0;
	}
	switch(osvi.dwPlatformId)
	{
	//Windows 95, Windows 98, or Windows Me.
	case VER_PLATFORM_WIN32_WINDOWS:
		if(osvi.dwMajorVersion==4 && osvi.dwMinorVersion ==10) return 1; //win 98
		if(osvi.dwMajorVersion==4 && osvi.dwMinorVersion ==90) return 2; //win Me
		if(osvi.dwMajorVersion==3 && osvi.dwMinorVersion ==51) return 3; //win NT 3.51
		if(osvi.dwMajorVersion==4 && osvi.dwMinorVersion ==0)  return 4; //win NT 4.0
	//Windows NT, Windows 2000, Windows XP, or Windows Server 2003 family.	
	case VER_PLATFORM_WIN32_NT:
		if(osvi.dwMajorVersion==5 && osvi.dwMinorVersion ==0) return 5; //win 2000
		if(osvi.dwMajorVersion==5 && osvi.dwMinorVersion ==1) return 6; //win xp
		if(osvi.dwMajorVersion==5 && osvi.dwMinorVersion ==2) return 7; //win 2003
	//unknow OptionSystem
	default:
		return 0;
	}
}

deque<string> ZSysInfo::GetLocalhostIP()
{
	//±¾»úÃû³Æ
	char Name[256]={0};
	deque<string> dqIPList;

	WSADATA WSAData;
	HOSTENT *host_info;
	WORD  wVersionRequested;
	wVersionRequested = MAKEWORD( 2, 2 ); 
	if(0==WSAStartup(wVersionRequested,&WSAData))
	{
		gethostname(Name,sizeof(Name));
		this->m_LocalhostName=Name;
		host_info=gethostbyname(Name);
		for( int i = 0; host_info!= NULL && host_info->h_addr_list[i]!= NULL; i++)
		{
			dqIPList.push_back(inet_ntoa (*(struct in_addr *)host_info->h_addr_list[i]));
		}
	}
	WSACleanup();
	return dqIPList;
}

string ZSysInfo::GetLocalhostName()
{
	if(m_LocalhostName.empty())
		GetLocalhostIP();
	return m_LocalhostName;
}

deque<THREADENTRY32> ZSysInfo::GetThreadInfo(unsigned int Pid)
{
	deque<THREADENTRY32> dqThread;
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); 
	if(hThreadSnap == INVALID_HANDLE_VALUE) return dqThread;
	THREADENTRY32 threadentry32;
	threadentry32.dwSize=sizeof(THREADENTRY32);
	if (Thread32First(hThreadSnap,&threadentry32))
	{
		do
		{
			if (threadentry32.th32OwnerProcessID == Pid)
			{
				dqThread.push_back(threadentry32);
			}
		}while(Thread32Next(hThreadSnap,&threadentry32));
	}
	CloseHandle(hThreadSnap);
	return dqThread;
}

deque<int> ZSysInfo::GetProcessID(char* szProcessName)
{
	deque<int> dqPid;
	deque<PROCESSENTRY32> dqProcess=GetProcessInfo();
	string strProcessName;
	for(int i=0;i<dqProcess.size();i++)
	{
		strProcessName=CharUpper(((PROCESSENTRY32)dqProcess[i]).szExeFile);
		if(GetOSVersion()==1 || GetOSVersion()==2)
		{
			if(strProcessName.substr(strProcessName.find_last_of("\\")+1)==CharUpper(szProcessName))
			dqPid.push_back(((PROCESSENTRY32)dqProcess[i]).th32ProcessID);
		}
		else
		{
			if(strProcessName==CharUpper(szProcessName))
			dqPid.push_back(((PROCESSENTRY32)dqProcess[i]).th32ProcessID);
		}
	}
	return dqPid;
}

string ZSysInfo::GetProcessName(int ProcessID)
{
	deque<PROCESSENTRY32> dqProcess=GetProcessInfo();
	for(int i=0;i<dqProcess.size();i++)
	{
		if(((PROCESSENTRY32)dqProcess[i]).th32ProcessID==ProcessID)
		{
			return ((PROCESSENTRY32)dqProcess[i]).szExeFile;
		}
	}
	return "";
}

HANDLE ZSysInfo::GetThreadHandle(unsigned int ThreadID)
{
	typedef HANDLE (__stdcall *OPENTHREAD) (DWORD dwDesiredAccess,BOOL bInheritHandle,DWORD dwThreadId);
	HMODULE hModule=LoadLibrary("Kernel32.dll");
	if(hModule==NULL) return (HANDLE)0xFFFFFFFF;
	OPENTHREAD lpfnOpenThread=(OPENTHREAD)::GetProcAddress(hModule,"OpenThread");
	if(lpfnOpenThread==NULL) return (HANDLE)0xFFFFFFFF;
	HANDLE hThread=lpfnOpenThread(THREAD_ALL_ACCESS,false,ThreadID);
	FreeLibrary(hModule);
	return hThread;	
}

/*
MSDN:
Return Values
To continue enumeration, the callback function must return TRUE;
to stop enumeration, it must return FALSE. 
*/
bool ZSysInfo::EnumChildProc(HWND hwnd,LPARAM lParam)
{
	if(((CTRLINFO*)(void*)lParam)->CtrlID==GetWindowLong(hwnd,GWL_ID) && 
	((CTRLINFO*)(void*)lParam)->CtrlStyle==GetWindowLong(hwnd,GWL_STYLE))
	{
		m_HWND=hwnd;
		return false;
	}
	return true;
}

HWND ZSysInfo::FindChildWindow(HWND hParent,long CtrlID,long CtrlStyle)
{
	m_HWND=(HWND)-1; // 0xFFFFFFFF
	CTRLINFO ctrlinfo;
	ctrlinfo.CtrlID=CtrlID;
	ctrlinfo.CtrlStyle=CtrlStyle;
	if(::EnumChildWindows(hParent,
		(WNDENUMPROC)m_thunk.Callback(this,&ZSysInfo::EnumChildProc,ZThunk::THISCALL),
		(LPARAM)(void*)(&ctrlinfo)))
	{
		return m_HWND;
	}
	return m_HWND;
}
