; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMySmtpDlg
LastTemplate=CScrollBar
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MySmtp.h"

ClassCount=4
Class1=CMySmtpApp
Class2=CMySmtpDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CScrollBarEx
Resource3=IDD_MYSMTP_DIALOG

[CLS:CMySmtpApp]
Type=0
HeaderFile=MySmtp.h
ImplementationFile=MySmtp.cpp
Filter=N

[CLS:CMySmtpDlg]
Type=0
HeaderFile=MySmtpDlg.h
ImplementationFile=MySmtpDlg.cpp
Filter=T
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMySmtpDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=MySmtpDlg.h
ImplementationFile=MySmtpDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MYSMTP_DIALOG]
Type=1
Class=CMySmtpDlg
ControlCount=18
Control1=IDC_EDIT_PORT,edit,1350639744
Control2=IDC_EDIT_ACCOUNT,edit,1350631552
Control3=IDC_EDIT_PASSWORD,edit,1350631584
Control4=IDC_BTN_BROWSER,button,1342242816
Control5=IDC_BTN_SEND,button,1342242816
Control6=IDC_BTN_ABOUT,button,1342242816
Control7=IDOK,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_COMBO_FILELIST,combobox,1344339971
Control15=IDC_COMBO_SMTP,combobox,1344339970
Control16=IDC_LIST_RESULT,SysListView32,1350565889
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_LENGTH,edit,1350631552

[CLS:CScrollBarEx]
Type=0
HeaderFile=ScrollBarEx.h
ImplementationFile=ScrollBarEx.cpp
BaseClass=CScrollBar
Filter=W

