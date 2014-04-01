

#ifndef _ZFILEDIALOG
#define _ZFILEDIALOG

#pragma warning(disable:4786) 
#include <string>
#include <deque>
#include <functional>
#include <algorithm>
using namespace std;
#include "ZThunk.h"
#include "ZSysInfo.h"
#include <io.h>

class ZFileDialog  
{
public:

	ZFileDialog();
	virtual ~ZFileDialog();

private:

	ZThunk m_thunk;
	ZSysInfo m_sysinfo;

	struct OPENFILENAMEEX : public OPENFILENAME
	{ 
		void* pvReserved;
		DWORD dwReserved;
		DWORD FlagsEx;
	};

public:

	//选择目录
	string GetSelectDirectory(HWND hwnd,const char* szTitle="Please select directory");

private:

	// 文件打开对话框的回调过程,用于使打开或保存对话框居中
	UINT_PTR OFNHookProc(HWND hdlg,UINT uiMsg,WPARAM wParam,LPARAM lParam);

public:

	/*********************************************************
	选择文件(单选或多选)
	ultiSelect文件是否可以多选
	Filter文件类型过滤
	备  注:例:Filter=="所有文件 (*.*)\0*.*\0文本文件 (*.txt)\0*.txt\0\0";
	*********************************************************/
	deque<string> GetOpenFileName(HWND hwnd,bool MultiSelect,const char* szFilter);

	/*********************************************************
	获取用户保存的文件名
	AutoAddSuffixName是否自动添加保存的文件后缀名(根据文件框的过滤下拉框添加)
	Filter文件类型过滤
	备  注:例:Filter=="所有文件 (*.*)\0*.*\0文本文件 (*.txt)\0*.txt\0\0";
	*********************************************************/
	string GetSaveFileName(HWND hwnd,bool AutoAddSuffixName,const char* szFilter);
};

#endif
