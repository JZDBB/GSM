
// GSME301.h : GSME301 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "SmsTraffic.h"


// CGSME301App:
// �йش����ʵ�֣������ GSME301.cpp
//

class CGSME301App : public CWinApp
{
public:
	CGSME301App();
	CString m_strPort;
	CString m_strRate;
	CString m_strBits;
	CString m_strStopbits;
	CString m_strPairty;
	CString m_strFlow;
	bool ComOpen;
public://������������
	CSmsTraffic* m_pSmsTraffic;
// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSetserialport();
	afx_msg void OnCommConnect();
	afx_msg void OnCheckGsm();
	//BOOL PreTranslateMessage(MSG * pMsg);
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTestSim();
	afx_msg void OnSimmenu();
};

extern CGSME301App theApp;
