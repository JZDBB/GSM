// CsetSerialPort.cpp : 实现文件
//

#include "stdafx.h"
#include "GSME301.h"
#include "CsetSerialPort.h"
#include "afxdialogex.h"


// CsetSerialPort 对话框

IMPLEMENT_DYNAMIC(CsetSerialPort, CDialog)

CsetSerialPort::CsetSerialPort(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SETSERIALPORTDLG, pParent)
{

}

CsetSerialPort::~CsetSerialPort()
{
}

void CsetSerialPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_portnum);
	DDX_Control(pDX, IDC_COMBO2, m_brate);
	DDX_Control(pDX, IDC_COMBO3, m_nbits);
	DDX_Control(pDX, IDC_COMBO4, m_pairty);
	DDX_Control(pDX, IDC_COMBO5, m_stopbits);
	DDX_Control(pDX, IDC_COMBO6, m_flowctrl);
}


BEGIN_MESSAGE_MAP(CsetSerialPort, CDialog)
	ON_BN_CLICKED(IDOK, &CsetSerialPort::OnBnClickedOk)
END_MESSAGE_MAP()


// CsetSerialPort 消息处理程序


BOOL CsetSerialPort::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strComm;
	for (int i = 0; i<9; i++)
	{
		strComm.Format("COM%d", i + 1);
		m_portnum.AddString(strComm);
	}
	m_brate.AddString("9600");
	m_brate.AddString("14400");
	m_brate.AddString("19200");
	m_brate.AddString("28800");
	m_brate.AddString("38400");
	m_brate.AddString("57600");
	m_brate.AddString("115200");
	m_nbits.AddString("5");
	m_nbits.AddString("6");
	m_nbits.AddString("7");
	m_nbits.AddString("8");
	m_pairty.AddString("偶校验");
	m_pairty.AddString("奇校验");
	m_pairty.AddString("无");
	m_stopbits.AddString("1");
	m_stopbits.AddString("1.5");
	m_stopbits.AddString("2");
	m_flowctrl.AddString("Xon/Xoff");
	m_flowctrl.AddString("硬件");
	m_flowctrl.AddString("无");
	if (m_strPort.IsEmpty()) m_strPort = "COM1";
	if (m_strRate.IsEmpty()) m_strRate = "9600";
	if (m_strPairty.IsEmpty()) m_strPairty = "无";
	if (m_strBits.IsEmpty()) m_strBits = "8";
	if (m_strStopbits.IsEmpty()) m_strStopbits = "1";
	if (m_strFlow.IsEmpty()) m_strFlow = "无"; m_portnum.SelectString(-1, m_strPort);
	m_brate.SelectString(-1, m_strRate);
	m_pairty.SelectString(-1, m_strPairty);
	m_nbits.SelectString(-1, m_strBits);
	m_stopbits.SelectString(-1, m_strStopbits);
	m_flowctrl.SelectString(-1, m_strFlow);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
								// 异常: OCX 属性页应返回 FALSE
}


void CsetSerialPort::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData();
	int nSel;
	nSel = m_portnum.GetCurSel();
	if (nSel > -1) m_portnum.GetLBText(nSel, m_strPort);
	nSel = m_brate.GetCurSel();
	if (nSel > -1) m_brate.GetLBText(nSel, m_strRate);
	nSel = m_pairty.GetCurSel();
	if (nSel > -1) m_pairty.GetLBText(nSel, m_strPairty);
	nSel = m_nbits.GetCurSel();
	if (nSel > -1) m_nbits.GetLBText(nSel, m_strBits);////
	nSel = m_stopbits.GetCurSel();
	if (nSel > -1) m_stopbits.GetLBText(nSel, m_strStopbits);
	nSel = m_flowctrl.GetCurSel();
	if (nSel > -1) m_flowctrl.GetLBText(nSel, m_strFlow);
	if (m_strPort.IsEmpty() || m_strRate.IsEmpty() || m_strPairty.IsEmpty() || m_strBits.IsEmpty() || m_strStopbits.IsEmpty() || m_strFlow.IsEmpty())
	{
		AfxMessageBox("请正确设置端口!");
		//return;
	}

	CDialog::OnOK();
}
