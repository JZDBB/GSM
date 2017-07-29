#pragma once
#include "afxwin.h"


// CsetSerialPort 对话框

class CsetSerialPort : public CDialog
{
	DECLARE_DYNAMIC(CsetSerialPort)

public:
	CsetSerialPort(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CsetSerialPort();

	CString m_strPort;
	CString m_strRate;
	CString m_strBits;
	CString m_strStopbits;
	CString m_strPairty;
	CString m_strFlow;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETSERIALPORTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_portnum;
	CComboBox m_brate;
	CComboBox m_nbits;
	CComboBox m_pairty;
	CComboBox m_stopbits;
	CComboBox m_flowctrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
