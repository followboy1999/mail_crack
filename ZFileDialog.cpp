

#include "stdafx.h"
#include "ZFileDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZFileDialog::ZFileDialog()
{

}

ZFileDialog::~ZFileDialog()
{

}

/***********************
ʹOpen��Save�Ի������
***********************/
UINT_PTR ZFileDialog::OFNHookProc(HWND hdlg,UINT uiMsg,WPARAM wParam,LPARAM lParam)
{
	if(uiMsg==WM_SHOWWINDOW)
	{
		RECT rtWnd,sysRect;
		::GetWindowRect(GetParent(hdlg),&rtWnd);
		SystemParametersInfo(SPI_GETWORKAREA,0,&sysRect,0);

		::MoveWindow(GetParent(hdlg),
					(sysRect.right-(rtWnd.right-rtWnd.left))/2,
					(sysRect.bottom-(rtWnd.bottom-rtWnd.top))/2,
					rtWnd.right-rtWnd.left,
					rtWnd.bottom-rtWnd.top,
					true);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// options
//////////////////////////////////////////////////////////////////////

string ZFileDialog::GetSelectDirectory(HWND hwnd,const char* szTitle)
{
	string ReturnValue;
	char Path[256]={0};
	BROWSEINFO browseinfo;   
	LPCITEMIDLIST lpcitemidlist;
	browseinfo.hwndOwner=0;   
	browseinfo.pszDisplayName=Path;   
	browseinfo.pidlRoot=NULL;   
	browseinfo.ulFlags=BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS;   
	browseinfo.lpfn=NULL;   
	browseinfo.lpszTitle=szTitle;   
	browseinfo.iImage=0;   
	browseinfo.hwndOwner = hwnd;

	lpcitemidlist=SHBrowseForFolder(&browseinfo);

	if(lpcitemidlist)
	{
		if(SHGetPathFromIDList(lpcitemidlist,Path))
			ReturnValue=Path;
	}
	return ReturnValue;
}

deque<string> ZFileDialog::GetOpenFileName(HWND hwnd,bool MultiSelect,const char* szFilter)
{
	deque<string> dqFileNames;

	char file[256]={0};
	OPENFILENAMEEX openfilename; 
	ZeroMemory(&openfilename, sizeof(OPENFILENAMEEX));

	if( m_sysinfo.GetOSVersion()==1 || 
		m_sysinfo.GetOSVersion()==2 || 
		m_sysinfo.GetOSVersion()==3 || 
		m_sysinfo.GetOSVersion()==4)
		openfilename.lStructSize = sizeof(OPENFILENAME);
	else
		openfilename.lStructSize = sizeof(OPENFILENAMEEX);

	openfilename.hInstance = 0;
	openfilename.lpstrFilter=szFilter;
	openfilename.lpstrFile=file;
	openfilename.nMaxFile=256;
	openfilename.Flags=OFN_EXPLORER | OFN_HIDEREADONLY | OFN_ENABLEHOOK;
	openfilename.Flags|=MultiSelect ? OFN_ALLOWMULTISELECT:0;
	openfilename.hwndOwner=hwnd;
	openfilename.lpfnHook=(LPOFNHOOKPROC)
	m_thunk.Callback(this,&ZFileDialog::OFNHookProc,ZThunk::THISCALL);

	if(::GetOpenFileName(&openfilename))
	{
		char* ptr=openfilename.lpstrFile;
		int Count=0;
		bool IsMulti=false;
		while(*ptr++)
		{
			if(++Count>=2)
			{
				IsMulti=true;
				break;
			}
			while(*ptr++);
		}
		if(IsMulti)
		{
			ptr=openfilename.lpstrFile;
			int nFiles=0;
			string strTmp="";
			while(*ptr++)
			{
				nFiles++;
				if(nFiles==1)
				{
					strTmp=ptr-1;
					if(strTmp[strTmp.size()-1]!='\\')
					{
						strTmp+="\\";
					}
				}
				else if(nFiles>=2)
				{
					if((_access((strTmp+(ptr-1)).c_str(),0))==-1)
						::MessageBox(NULL,(strTmp+(ptr-1)).c_str(),"�ļ�δ�ҵ�",MB_OK);
					else
						dqFileNames.push_back(strTmp+(ptr-1));
				}
				while(*ptr++);
			}
		}
		else
		{
			if((_access(openfilename.lpstrFile,0))==-1)
				::MessageBox(NULL,openfilename.lpstrFile,"�ļ�δ�ҵ�",MB_OK);
			else
				dqFileNames.push_back(openfilename.lpstrFile);
		}
	}
	return dqFileNames;
}

string ZFileDialog::GetSaveFileName(HWND hwnd,bool AutoAddSuffixName,const char* szFilter)
{
	string strFileName="";

	char file[256]={0};
	OPENFILENAMEEX openfilename; 
	ZeroMemory(&openfilename, sizeof(OPENFILENAMEEX));

	if( m_sysinfo.GetOSVersion()==1 || 
		m_sysinfo.GetOSVersion()==2 || 
		m_sysinfo.GetOSVersion()==3 || 
		m_sysinfo.GetOSVersion()==4)
		openfilename.lStructSize = sizeof(OPENFILENAME);
	else
		openfilename.lStructSize = sizeof(OPENFILENAMEEX);
	
	openfilename.hInstance =0;
	openfilename.lpstrFile=file;
	openfilename.nMaxFile=256;
	openfilename.lpstrFilter=szFilter;
	openfilename.Flags=OFN_EXPLORER | OFN_ENABLEHOOK;
	openfilename.hwndOwner=hwnd;
	openfilename.lpfnHook=(LPOFNHOOKPROC)
	m_thunk.Callback(this,&ZFileDialog::OFNHookProc,ZThunk::THISCALL);

	if(!::GetSaveFileName(&openfilename)) return strFileName;

	strFileName=file;
	if(!AutoAddSuffixName) return strFileName;

	//�ж��û���д���ļ����Ƿ��к�׺
	bool IsHaveSuffix=strFileName.find_last_of(".")==-1?false:true;

	//��const char* Filter���������
	deque<string> FilterArray;
	while(*szFilter++)
	{
		FilterArray.push_back(szFilter-1);
		while(*szFilter++);
	}

	//�����������Ϊ"*.*",�򲻽��д���,ֱ�ӷ���
	string strFilter=FilterArray[openfilename.nFilterIndex];
	strFilter.erase(remove_if(strFilter.begin(),strFilter.end(),ptr_fun(::isspace)),strFilter.end());
	if(strFilter=="*.*")  return strFileName;

	string strSuffixName=strFilter.substr(2).c_str();
	if(IsHaveSuffix)
	{
		//����û�����ĺ�׺�͹������еĺ�׺һ��
		if(strFileName.substr(strFileName.find_last_of(".")+1)==strSuffixName)
		{
			return strFileName;
		}
		else
		{
			strFileName+=".";
			strFileName+=strSuffixName;
			return strFileName;
		}
	}
	else
	{
		strFileName+=".";
		strFileName+=strSuffixName;
		return strFileName;
	}
}
