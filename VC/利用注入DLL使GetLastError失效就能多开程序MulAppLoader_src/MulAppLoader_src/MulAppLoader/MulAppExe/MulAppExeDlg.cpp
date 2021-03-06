// MulAppExeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MulAppExe.h"
#include "MulAppExeDlg.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMulAppExeDlg 对话框




CMulAppExeDlg::CMulAppExeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMulAppExeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMulAppExeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEditMessage);
	DDX_Control(pDX, IDC_EDIT_FILE, m_EditFile);
}

BEGIN_MESSAGE_MAP(CMulAppExeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CMulAppExeDlg::OnNMClickSyslink1)
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CMulAppExeDlg::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE, &CMulAppExeDlg::OnBnClickedButtonExecute)
END_MESSAGE_MAP()


void AppendRichEditMessage(CRichEditCtrl *pRichEdit, LPTSTR lpTextAppend)
{
	pRichEdit->SetSel(-1, -1);				//插入点移动到最后
	pRichEdit->ReplaceSel(lpTextAppend);	//插入文字
	pRichEdit->PostMessage(WM_VSCROLL,SB_LINEDOWN,0);
}

// CMulAppExeDlg 消息处理程序

BOOL CMulAppExeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	DragAcceptFiles(TRUE);
	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	AppendRichEditMessage(&m_RichEditMessage, _T("Finish Time:2012/11/24 11:00\nCoded By:peheaven\nQQ技术交流群:275372932\n\n"));
	// TODO: 在此添加额外的初始化代码

	//CHARFORMAT cf1; //定义字体格式结构体变量
	//cf1.dwEffects = 0; //字体的效果
	//cf1.crTextColor = RGB(255,0,0); //字体的颜色
	//cf1.yHeight = 200; //字体的大小（并非我们常见的字号概念）
	//m_RichEditMessage.SetDefaultCharFormat(cf1);

	CHARFORMAT cf0;
	CHARFORMAT cf;
	cf.dwEffects = 0;
	//m_RichEditMessage.SetSel(0, m_RichEditMessage.GetTextLength());
	m_RichEditMessage.GetSelectionCharFormat(cf0);
	cf.dwMask|=CFM_BOLD;
	cf.dwEffects|=CFE_BOLD;//设置粗体，取消用cf.dwEffects&=~CFE_BOLD;
	cf.dwMask|=CFM_ITALIC;
	cf.dwEffects|=CFE_ITALIC;//设置斜体，取消用cf.dwEffects&=~CFE_ITALIC;
	cf.dwMask|=CFM_UNDERLINE;
	cf.dwEffects|=CFE_UNDERLINE;//设置斜体，取消用cf.dwEffects&=~CFE_UNDERLINE;
	cf.dwMask|=CFM_COLOR;
	cf.crTextColor = RGB(255, 0, 0);//设置颜色
	cf.dwMask|=CFM_SIZE;
	cf.yHeight =250;//设置高度
	cf.dwMask|=CFM_FACE;
	_tcscpy_s(cf.szFaceName, _countof(cf.szFaceName), _T("楷书"));//设置字体

	m_RichEditMessage.SetSel(0, m_RichEditMessage.GetTextLength());
	m_RichEditMessage.SetSelectionCharFormat(cf);

	m_RichEditMessage.SetSel(-1, -1);
	m_RichEditMessage.SetSelectionCharFormat(cf0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMulAppExeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMulAppExeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMulAppExeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

_declspec(naked) void LoadLibraryStart()
{
	__asm
	{
		pushad
		mov		eax, 0x10101010				// address of loadlibraryA/W
		call	$ + 5
		add		DWORD PTR[esp], 0x0D        //指向 PathDll 在后面赋值上DLLpath
		call	eax
		popad
		
		push	0x20202020					// address of original eip
		ret
	}
}

_declspec(naked) void LoadLibraryEnd(){}

void CMulAppExeDlg::RunAppWithHook(LPTSTR tzFilePathName, LPTSTR tzDllPath)
{
	do 
	{
		STARTUPINFO	si = {sizeof(si)};
		PROCESS_INFORMATION	pi = {};
		TCHAR	tzFileFolder[MAX_PATH] = {};
		TCHAR	tzMessage[260] = {};

		_tcscpy_s(tzFileFolder, _countof(tzFileFolder), tzFilePathName);
		PathRemoveFileSpec(tzFileFolder);

		if(!CreateProcess(NULL, tzFilePathName, NULL, NULL, 
			TRUE, CREATE_SUSPENDED | CREATE_DEFAULT_ERROR_MODE, 
			NULL, tzFileFolder, &si, &pi))
		{
			_sntprintf_s(tzMessage, _countof(tzMessage), _TRUNCATE, _T("CreateProcess fail:0x%.8x\n"), GetLastError());
			AppendRichEditMessage(&m_RichEditMessage, tzMessage);
			break;
		}

		CONTEXT	ThreadContext;

		ThreadContext.ContextFlags = CONTEXT_FULL;
		if(!GetThreadContext(pi.hThread, &ThreadContext))
		{
			_sntprintf_s(tzMessage, _countof(tzMessage), _TRUNCATE, _T("GetThreadContext fail:0x%.8x\n"), GetLastError());
			AppendRichEditMessage(&m_RichEditMessage, tzMessage);
			break;
		}

		CHAR	pShellCode[1024] = {};

		DWORD	dwShellCodeSize = (DWORD)LoadLibraryEnd;
		dwShellCodeSize -= (DWORD)LoadLibraryStart;

		RtlCopyMemory(pShellCode, LoadLibraryStart, dwShellCodeSize);

		*(DWORD *)(pShellCode + 0x02) = (DWORD)LoadLibrary;
		*(DWORD *)(pShellCode + 0x13) = (DWORD)ThreadContext.Eip;
		RtlCopyMemory(pShellCode + 0x18, (PCHAR)tzDllPath, _tcslen(tzDllPath) * sizeof(TCHAR));

		LPVOID lpRemoteLoadLibraryStart = VirtualAllocEx(pi.hProcess, NULL, 1024, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if(lpRemoteLoadLibraryStart == NULL)
		{
			_sntprintf_s(tzMessage, _countof(tzMessage), _TRUNCATE, _T("VirtualAllocEx fail:0x%.8x\n"), GetLastError());
			AppendRichEditMessage(&m_RichEditMessage, tzMessage);
			break;
		}

		DWORD	nNumberOfBytesWritten;
		if(!WriteProcessMemory(pi.hProcess, lpRemoteLoadLibraryStart, pShellCode, 1024, &nNumberOfBytesWritten))
		{
			_sntprintf_s(tzMessage, _countof(tzMessage), _TRUNCATE, _T("WriteProcessMemory fail:0x%.8x\n"), GetLastError());
			AppendRichEditMessage(&m_RichEditMessage, tzMessage);
			break;
		}

		ThreadContext.Eip = (DWORD)lpRemoteLoadLibraryStart;

		if(!SetThreadContext(pi.hThread, &ThreadContext))
		{
			_sntprintf_s(tzMessage, _countof(tzMessage), _TRUNCATE, _T("SetThreadContext fail:0x%.8x\n"), GetLastError());
			AppendRichEditMessage(&m_RichEditMessage, tzMessage);
			break;
		}

		ResumeThread(pi.hThread);

		Sleep(2000);

		VirtualFreeEx(pi.hThread, lpRemoteLoadLibraryStart, 0, MEM_RELEASE);

	} while (0);
}

// 由程序的Lnk路径得到对应的绝对路径
bool ReadShortcut(LPWSTR lpwLnkFile, LPTSTR lpDescFile)
{
	HRESULT hr;
	IShellLink *pShellLink;

	::CoInitialize(NULL);

	hr = CoCreateInstance (CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
		IID_IShellLink, (void **)&pShellLink) >= 0;
	if(SUCCEEDED(hr))
	{
		IPersistFile *ppf;
		hr = pShellLink->QueryInterface(IID_IPersistFile, (void **)&ppf) >= 0;
		if(SUCCEEDED(hr))
		{
			hr = ppf->Load(lpwLnkFile, TRUE) >= 0;
			if(SUCCEEDED(hr))
			{
				hr = pShellLink->GetPath(lpDescFile, MAX_PATH, NULL, 0);

				if(SUCCEEDED(hr) && GetLastError() == 0)
				{
					hr = 0;
				}
				else
				{
					hr = -1;
				}
			}
			ppf->Release ();
		}
		pShellLink->Release ();
	}
	::CoUninitialize();

	return SUCCEEDED(hr);
}

void CMulAppExeDlg::OnDropFiles(HDROP hDropInfo)
{
	CDialog::OnDropFiles(hDropInfo);

	TCHAR	tzFilePathName[MAX_PATH] = {};
	TCHAR	tzDllPath[MAX_PATH] = {};

	DragQueryFile(hDropInfo, 0, tzFilePathName, MAX_PATH);

	if(_tcsicmp(_T(".lnk"), PathFindExtension(tzFilePathName)) == 0)
	{
		AppendRichEditMessage(&m_RichEditMessage, tzFilePathName);
		AppendRichEditMessage(&m_RichEditMessage, _T("\nUnsupport drag lnk file.\n"));
		return;

		//
		// 这里有问题，无法成功得到快捷方式所指向的文件路径，在win7 x64机器上测的
		//
		/*if(!ReadShortcut(tzFilePathName, tzFilePathName))
		{
			TCHAR	tzMessage[260] = {};
			_sntprintf_s(tzMessage, _countof(tzMessage), _TRUNCATE, _T("Parse link to path fail.\n%s\n"), tzFilePathName);
			AppendRichEditMessage(&m_RichEditMessage, tzMessage);
			return;
		}*/
	}

	GetModuleFileName(NULL, tzDllPath, MAX_PATH);
	PathRemoveFileSpec(tzDllPath);
	PathRemoveBackslash(tzDllPath);
	PathAppend(tzDllPath, _T("MulAppDll.dll"));

	AppendRichEditMessage(&m_RichEditMessage, tzFilePathName);
	AppendRichEditMessage(&m_RichEditMessage, _T("\n"));

	RunAppWithHook(tzFilePathName, tzDllPath);
}

void CMulAppExeDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(NULL, _T("open"), _T("www.peheaven.cn"), NULL, NULL, SW_SHOWNORMAL);
	*pResult = 0;
}

void CMulAppExeDlg::OnBnClickedButtonFile()
{
	CFileDialog dlg(TRUE,//TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框 
		_T(".exe"),//默认的打开文件的类型 
		NULL,//默认打开的文件名 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//打开只读文件 
		_T("可执行文件(*.exe)||"));//所有可以打开的文件类型 
	//点打开文件对话框上面的确定键后 
	if(dlg.DoModal()==IDOK)   
	{ 
		CString m_FilePath = dlg.GetPathName();////////取出文件路径 
		m_EditFile.SetWindowText(m_FilePath);
	}
}

void CMulAppExeDlg::OnBnClickedButtonExecute()
{
	TCHAR	tzFilePathName[MAX_PATH] = {};
	TCHAR	tzDllPath[MAX_PATH] = {};

	m_EditFile.GetWindowText(tzFilePathName, MAX_PATH);

	GetModuleFileName(NULL, tzDllPath, MAX_PATH);
	PathRemoveFileSpec(tzDllPath);
	PathRemoveBackslash(tzDllPath);
	PathAppend(tzDllPath, _T("MulAppDll.dll"));

	AppendRichEditMessage(&m_RichEditMessage, tzFilePathName);
	AppendRichEditMessage(&m_RichEditMessage, _T("\n"));

	RunAppWithHook(tzFilePathName, tzDllPath);
}
