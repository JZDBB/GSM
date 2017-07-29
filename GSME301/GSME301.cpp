
// GSME301.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GSME301.h"
#include "MainFrm.h"

#include "GSME301Doc.h"
#include "GSME301View.h"

#include "Comm.h"
#include "Sms.h"
#include "CsetSerialPort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGSME301App
BEGIN_MESSAGE_MAP(CGSME301App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CGSME301App::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_SETSERIALPORT, &CGSME301App::OnSetserialport)
	ON_COMMAND(ID_COMM_CONNECT, &CGSME301App::OnCommConnect)
	ON_COMMAND(ID_CHECK_GSM, &CGSME301App::OnCheckGsm)
	ON_COMMAND(ID_TEST_SIM, &CGSME301App::OnTestSim)
	ON_COMMAND(ID_SIMMENU, &CGSME301App::OnSimmenu)
END_MESSAGE_MAP()

// CGSME301App 构造
CGSME301App::CGSME301App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GSME301.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CGSME301App 对象
CGSME301App theApp;

// CGSME301App 初始化
BOOL CGSME301App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGSME301Doc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CGSME301View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	//UINT_PTR uTimerId = SetTimer(NULL, 0, 2000, NULL);
	//TRACE(_T("Timer created - ID=%x\n"), uTimerId);
	ComOpen = false;

	m_pSmsTraffic = new CSmsTraffic;

	return TRUE;
}

int CGSME301App::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CGSME301App 消息处理程序

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTestSim();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_TEST_SIM, &CAboutDlg::OnTestSim)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CGSME301App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
	
}

// CGSME301App 消息处理程序

void CGSME301App::OnSetserialport()
{
	// TODO: 在此添加命令处理程序代码
	CsetSerialPort dlg;

	dlg.m_strPort = m_strPort;
	dlg.m_strRate = m_strRate;
	dlg.m_strBits = m_strBits;
	dlg.m_strPairty = m_strPairty; dlg.m_strStopbits = m_strStopbits; dlg.m_strFlow = m_strFlow;
	if (dlg.DoModal() == IDOK)
	{
		if (m_strPort != dlg.m_strPort)
		{
			AfxMessageBox("端口设置成功！");
		}
		m_strPort = dlg.m_strPort;
		m_strRate = dlg.m_strRate;
		m_strBits = dlg.m_strBits;
		m_strPairty = dlg.m_strPairty;
		m_strStopbits = dlg.m_strStopbits;
		m_strFlow = dlg.m_strFlow;
	}
}


void CGSME301App::OnCommConnect()
{
	// TODO: 在此添加命令处理程序代码
	//if (ComOpen) return;
	int nRate, nParity, nByteSize, nStopBits;
	sscanf(m_strRate, "%d", &nRate);
	if (m_strPairty == "无")nParity = 0;
	else if (m_strPairty == "奇校验")nParity = 1;
	else if (m_strPairty == "偶校验")nParity = 2;
	else nParity = 0;
	sscanf(m_strBits, "%d", &nByteSize);
	if (m_strStopbits == "1")nStopBits = 0;
	else if (m_strStopbits == "1.5")nStopBits = 1;
	else nStopBits = 2;
	while (!::OpenComm(m_strPort, nRate, nParity, nByteSize, nStopBits))
	{
		CString strError;
		strError.Format("无法打开端口%s! 现在设置串口参数吗?", m_strPort);
		if (AfxMessageBox(strError, MB_YESNO) == IDNO) return; 
		CsetSerialPort dlg;
		dlg.m_strPort = m_strPort;
		dlg.m_strRate = m_strRate;
		dlg.m_strBits = m_strBits;
		dlg.m_strPairty = m_strPairty;
		dlg.m_strStopbits = m_strStopbits; dlg.m_strFlow = m_strFlow;
		if (dlg.DoModal() == IDOK)
		{
			m_strPort = dlg.m_strPort;
			m_strRate = dlg.m_strRate;
			m_strBits = dlg.m_strBits;
			m_strPairty = dlg.m_strPairty;
			m_strStopbits = dlg.m_strStopbits;
			m_strFlow = dlg.m_strFlow;
		}
		else
		{
			return;
		}
	}
	CString str;
	str.Format("%s已连接, %s-%s-%s-%s", m_strPort, m_strRate, m_strBits, m_strPairty, m_strStopbits);
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetWindowText(str);
	ComOpen = true;
}


void CGSME301App::OnCheckGsm()
{
	// TODO: 在此添加命令处理程序代码
	if (!gsmInit())
	{
		AfxMessageBox("该端口上没有发现GSM模块!");
		return;
	}
	AfxMessageBox("GSM模块成功响应!");
}

//BOOL CGSME301App::PreTranslateMessage(MSG* pMsg)
//{
//	if (pMsg->message == WM_TIMER)
//	{
//		if (!ComOpen) return false;
//		CString str = "", tmp;
//		if (!gsmInit()) {
//			ComOpen = false;
//			str = "串口线已断开！";
//			CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
//			CStatusBar* pStatus = &pFrame->m_wndStatusBar;
//			pStatus->SetWindowText(str);
//			return true;
//		}
//
//		int rssi, ber;
//		testSignal(rssi, ber);
//		tmp.Format("RSSI=%d,BER=%d;", rssi, ber);
//		str += tmp;
//
//		if (testSIMCARD()) {
//			str += "SIM卡已插入！";
//		}
//		else {
//			str += "SIM卡未插入！";
//		}
//		CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
//		CStatusBar* pStatus = &pFrame->m_wndStatusBar;
//		pStatus->SetWindowText(str);
//
//
//
//#ifdef DEBUG
//		TRACE(_T("Timer fired - ID=%x\n"), pMsg->wParam);
//#endif // DEBUG
//
//		
//	}
//
//	return CWinApp::PreTranslateMessage(pMsg);
//}

////void CAboutDlg::OnTestSim()
////{
////	// TODO: 在此添加命令处理程序代码
////	testSIMCard();
////}


void CGSME301App::OnTestSim()
{
	// TODO: 在此添加命令处理程序代码
	if (!ComOpen) {
		return;
	}
	CString str;
	if (testSIMCARD()) {
		int rssi, ber;
		if (testSignal(rssi, ber)) {
			str.Format("RSSI=%d,BER=%d", rssi, ber);
		}
	}
	else {
		str = "SIM卡未插入！";
	}
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetWindowText(str);

}


void CGSME301App::OnSimmenu()
{
	// TODO: 在此添加命令处理程序代码
	CString str;
	int now1, total1, now2, total2;
	if (gsmTMENU2(now2,total2)&&gsmTMENU(now1,total1))
	{
		str.Format("短信容量 = %d, 现有短信%d条。 电话本总量 = %d，现有联系人%d个", total1, now1, total2, now2);
	}
	else
	{
		str = "暂时无法读取SIM内存";
	}
	
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetWindowText(str);
}
