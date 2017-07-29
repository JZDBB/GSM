
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "GSME301.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString * SplitString(CString str, char split, int& iSubStrs);
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_SEND, &CMainFrame::OnBnClickedSend)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	if (!m_wndDialogBar.Create(this, IDD_SEND_SM, CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY, IDD_SEND_SM))
	{
		TRACE0("未能创建对话框\n");
		return -1;
	}

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDialogBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndDialogBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox* pNumberWnd = (CComboBox*)m_wndDialogBar.GetDlgItem(IDC_NUMBER);
	CComboBox* pContentWnd = (CComboBox*)m_wndDialogBar.GetDlgItem(IDC_CONTENT);
	CString strSmsc;
	CString strNumber;
	CString strContent;
	strSmsc = "13800280500"; //成都移动短信中心号码，如果是联通请改为 13010811500
	pNumberWnd->GetWindowText(strNumber);
	pContentWnd->GetWindowText(strContent);
	// 检查号码
	if (strNumber.GetLength() < 11)
	{
		AfxMessageBox("请输入正确的号码！");
		pNumberWnd->SetFocus();
		pNumberWnd->SetEditSel(-1, 0);
		return;
	}
	// 检查短消息内容是否空，或者超长
	CString strUnicode;
	WCHAR wchar[1024];
	int nCount = ::MultiByteToWideChar(CP_ACP, 0, strContent, -1, wchar, 1024);
	if (nCount <= 1)
	{
		AfxMessageBox("请输入消息内容！");
		pContentWnd->SetFocus();
		pContentWnd->SetEditSel(-1, 0);
		return;
	}
	else if (nCount > 70) // 全部用 UCS2 编码，最大 70 个字符(半角/全角)
	{
		AfxMessageBox("消息内容太长，无法发送！");
		pContentWnd->SetFocus();
		pContentWnd->SetEditSel(-1, 0);
		return;
	}
	if (AfxMessageBox("确定发送吗？", MB_YESNO) == IDYES)
	{
		SM_PARAM SmParam;
		memset(&SmParam, 0, sizeof(SM_PARAM));
		CString getnumber;
		int StrNum;
		CString* pStr;
		pStr = SplitString(strNumber, ';', StrNum);
		//如果子字符串的数量为1
		if (StrNum == 1)
		{
			//Convert CString to char
			CString pCh = (LPSTR)(LPCTSTR)strNumber;
			// 去掉号码前的"+"
			if (strSmsc[0] == '+') strSmsc = strSmsc.Mid(1);
			if (pCh[0] == '+') pCh = pCh.Mid(1);
			// 在号码前加"86"
			if (strSmsc.Left(2) != "86") strSmsc = "86" + strSmsc;
			if (pCh.Left(2) != "86") pCh = "86" + pCh;
			// 填充短消息结构
			strcpy(SmParam.SCA, strSmsc);
			strcpy(SmParam.TPA, pCh);
			strcpy(SmParam.TP_UD, strContent);
			SmParam.TP_PID = 0;
			SmParam.TP_DCS = GSM_UCS2;
			// 发送短消息
			theApp.m_pSmsTraffic->PutSendMessage(&SmParam);
		}
		else
		{
			//输出所有子字符串
			for (int i = 0; i < StrNum; i++)
			{
				//Convert CString to char
				CString pCh = (LPSTR)(LPCTSTR)pStr[i];
				// 去掉号码前的"+"
				if (strSmsc[0] == '+') strSmsc = strSmsc.Mid(1);
				if (pCh[0] == '+') pCh = pCh.Mid(1);
				// 在号码前加"86"
				if (strSmsc.Left(2) != "86") strSmsc = "86" + strSmsc;
				if (pCh.Left(2) != "86") pCh = "86" + pCh;
				// 填充短消息结构
				strcpy(SmParam.SCA, strSmsc);
				strcpy(SmParam.TPA, pCh);
				strcpy(SmParam.TP_UD, strContent);
				SmParam.TP_PID = 0;
				SmParam.TP_DCS = GSM_UCS2;
				// 发送短消息
				theApp.m_pSmsTraffic->PutSendMessage(&SmParam);
			}
			delete[]pStr;
		}
		
		//// 去掉号码前的"+"
		//if (strSmsc[0] == '+') strSmsc = strSmsc.Mid(1);
		//if (strNumber[0] == '+') strNumber = strNumber.Mid(1);
		//// 在号码前加"86"
		//if (strSmsc.Left(2) != "86") strSmsc = "86" + strSmsc;
		//if (strNumber.Left(2) != "86") strNumber = "86" + strNumber;
		//// 填充短消息结构
		//strcpy(SmParam.SCA, strSmsc);
		//strcpy(SmParam.TPA, strNumber);
		//strcpy(SmParam.TP_UD, strContent);
		//SmParam.TP_PID = 0;
		//SmParam.TP_DCS = GSM_UCS2;
		//// 发送短消息
		//theApp.m_pSmsTraffic->PutSendMessage(&SmParam);
		// 列表中加入新串
		if (pNumberWnd->FindStringExact(-1, strNumber)<0) pNumberWnd->InsertString(0, strNumber);
		if (pContentWnd->FindStringExact(-1, strContent)<0) pContentWnd->InsertString(0, strContent);
	}
	pContentWnd->SetFocus();
	pContentWnd->SetEditSel(-1, 0);
}


CString * SplitString(CString str, char split, int& iSubStrs)
{
	int iPos = 0; //分割符位置
	int iNums = 0; //分割符的总数
	CString strTemp = str;
	CString strRight;
	//先计算子字符串的数量
	while (iPos != -1)
	{
		iPos = strTemp.Find(split);
		if (iPos == -1)
		{
			break;
		}
		strRight = strTemp.Mid(iPos + 1, str.GetLength());
		strTemp = strRight;
		iNums++;
	}
	if (iNums == 0) //没有找到分割符
	{
		//子字符串数就是字符串本身
		iSubStrs = 1;
		return NULL;
	}
	//子字符串数组
	iSubStrs = iNums + 1; //子串的数量 = 分割符数量 + 1
	CString* pStrSplit;
	pStrSplit = new CString[iSubStrs];
	strTemp = str;
	CString strLeft;
	for (int i = 0; i < iNums; i++)
	{
		iPos = strTemp.Find(split);
		//左子串
		strLeft = strTemp.Left(iPos);
		//右子串
		strRight = strTemp.Mid(iPos + 1, strTemp.GetLength());
		strTemp = strRight;
		pStrSplit[i] = strLeft;
	}
	pStrSplit[iNums] = strTemp;
	return pStrSplit;
}