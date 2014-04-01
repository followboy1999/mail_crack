// MySmtp.h : main header file for the MYSMTP application
//

#if !defined(AFX_MYSMTP_H__162C518C_B08D_4530_9CC0_C6D284E92687__INCLUDED_)
#define AFX_MYSMTP_H__162C518C_B08D_4530_9CC0_C6D284E92687__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMySmtpApp:
// See MySmtp.cpp for the implementation of this class
//

class CMySmtpApp : public CWinApp
{
public:
	CMySmtpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySmtpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMySmtpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSMTP_H__162C518C_B08D_4530_9CC0_C6D284E92687__INCLUDED_)
