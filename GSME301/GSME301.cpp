
// GSME301.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_SETSERIALPORT, &CGSME301App::OnSetserialport)
	ON_COMMAND(ID_COMM_CONNECT, &CGSME301App::OnCommConnect)
	ON_COMMAND(ID_CHECK_GSM, &CGSME301App::OnCheckGsm)
	ON_COMMAND(ID_TEST_SIM, &CGSME301App::OnTestSim)
	ON_COMMAND(ID_SIMMENU, &CGSME301App::OnSimmenu)
END_MESSAGE_MAP()

// CGSME301App ����
CGSME301App::CGSME301App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GSME301.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CGSME301App ����
CGSME301App theApp;

// CGSME301App ��ʼ��
BOOL CGSME301App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGSME301Doc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CGSME301View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ�������  ���
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
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
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CGSME301App ��Ϣ�������

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CGSME301App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
	
}

// CGSME301App ��Ϣ�������

void CGSME301App::OnSetserialport()
{
	// TODO: �ڴ���������������
	CsetSerialPort dlg;

	dlg.m_strPort = m_strPort;
	dlg.m_strRate = m_strRate;
	dlg.m_strBits = m_strBits;
	dlg.m_strPairty = m_strPairty; dlg.m_strStopbits = m_strStopbits; dlg.m_strFlow = m_strFlow;
	if (dlg.DoModal() == IDOK)
	{
		if (m_strPort != dlg.m_strPort)
		{
			AfxMessageBox("�˿����óɹ���");
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
	// TODO: �ڴ���������������
	//if (ComOpen) return;
	int nRate, nParity, nByteSize, nStopBits;
	sscanf(m_strRate, "%d", &nRate);
	if (m_strPairty == "��")nParity = 0;
	else if (m_strPairty == "��У��")nParity = 1;
	else if (m_strPairty == "żУ��")nParity = 2;
	else nParity = 0;
	sscanf(m_strBits, "%d", &nByteSize);
	if (m_strStopbits == "1")nStopBits = 0;
	else if (m_strStopbits == "1.5")nStopBits = 1;
	else nStopBits = 2;
	while (!::OpenComm(m_strPort, nRate, nParity, nByteSize, nStopBits))
	{
		CString strError;
		strError.Format("�޷��򿪶˿�%s! �������ô��ڲ�����?", m_strPort);
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
	str.Format("%s������, %s-%s-%s-%s", m_strPort, m_strRate, m_strBits, m_strPairty, m_strStopbits);
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetWindowText(str);
	ComOpen = true;
}


void CGSME301App::OnCheckGsm()
{
	// TODO: �ڴ���������������
	if (!gsmInit())
	{
		AfxMessageBox("�ö˿���û�з���GSMģ��!");
		return;
	}
	AfxMessageBox("GSMģ��ɹ���Ӧ!");
}

//BOOL CGSME301App::PreTranslateMessage(MSG* pMsg)
//{
//	if (pMsg->message == WM_TIMER)
//	{
//		if (!ComOpen) return false;
//		CString str = "", tmp;
//		if (!gsmInit()) {
//			ComOpen = false;
//			str = "�������ѶϿ���";
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
//			str += "SIM���Ѳ��룡";
//		}
//		else {
//			str += "SIM��δ���룡";
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
////	// TODO: �ڴ���������������
////	testSIMCard();
////}


void CGSME301App::OnTestSim()
{
	// TODO: �ڴ���������������
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
		str = "SIM��δ���룡";
	}
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetWindowText(str);

}


void CGSME301App::OnSimmenu()
{
	// TODO: �ڴ���������������
	CString str;
	int now1, total1, now2, total2;
	if (gsmTMENU2(now2,total2)&&gsmTMENU(now1,total1))
	{
		str.Format("�������� = %d, ���ж���%d���� �绰������ = %d��������ϵ��%d��", total1, now1, total2, now2);
	}
	else
	{
		str = "��ʱ�޷���ȡSIM�ڴ�";
	}
	
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	pStatus->SetWindowText(str);
}
