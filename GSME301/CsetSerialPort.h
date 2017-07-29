#pragma once
#include "afxwin.h"


// CsetSerialPort �Ի���

class CsetSerialPort : public CDialog
{
	DECLARE_DYNAMIC(CsetSerialPort)

public:
	CsetSerialPort(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CsetSerialPort();

	CString m_strPort;
	CString m_strRate;
	CString m_strBits;
	CString m_strStopbits;
	CString m_strPairty;
	CString m_strFlow;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETSERIALPORTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
