
// GSME301.h : GSME301 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "SmsTraffic.h"


// CGSME301App:
// 有关此类的实现，请参阅 GSME301.cpp
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
public://定义在类里面
	CSmsTraffic* m_pSmsTraffic;
// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
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
