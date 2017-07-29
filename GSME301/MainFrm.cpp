
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	if (!m_wndDialogBar.Create(this, IDD_SEND_SM, CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY, IDD_SEND_SM))
	{
		TRACE0("δ�ܴ����Ի���\n");
		return -1;
	}

	// TODO: �������Ҫ��ͣ������������ɾ��������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



void CMainFrame::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CComboBox* pNumberWnd = (CComboBox*)m_wndDialogBar.GetDlgItem(IDC_NUMBER);
	CComboBox* pContentWnd = (CComboBox*)m_wndDialogBar.GetDlgItem(IDC_CONTENT);
	CString strSmsc;
	CString strNumber;
	CString strContent;
	strSmsc = "13800280500"; //�ɶ��ƶ��������ĺ��룬�������ͨ���Ϊ 13010811500
	pNumberWnd->GetWindowText(strNumber);
	pContentWnd->GetWindowText(strContent);
	// ������
	if (strNumber.GetLength() < 11)
	{
		AfxMessageBox("��������ȷ�ĺ��룡");
		pNumberWnd->SetFocus();
		pNumberWnd->SetEditSel(-1, 0);
		return;
	}
	// ������Ϣ�����Ƿ�գ����߳���
	CString strUnicode;
	WCHAR wchar[1024];
	int nCount = ::MultiByteToWideChar(CP_ACP, 0, strContent, -1, wchar, 1024);
	if (nCount <= 1)
	{
		AfxMessageBox("��������Ϣ���ݣ�");
		pContentWnd->SetFocus();
		pContentWnd->SetEditSel(-1, 0);
		return;
	}
	else if (nCount > 70) // ȫ���� UCS2 ���룬��� 70 ���ַ�(���/ȫ��)
	{
		AfxMessageBox("��Ϣ����̫�����޷����ͣ�");
		pContentWnd->SetFocus();
		pContentWnd->SetEditSel(-1, 0);
		return;
	}
	if (AfxMessageBox("ȷ��������", MB_YESNO) == IDYES)
	{
		SM_PARAM SmParam;
		memset(&SmParam, 0, sizeof(SM_PARAM));
		CString getnumber;
		int StrNum;
		CString* pStr;
		pStr = SplitString(strNumber, ';', StrNum);
		//������ַ���������Ϊ1
		if (StrNum == 1)
		{
			//Convert CString to char
			CString pCh = (LPSTR)(LPCTSTR)strNumber;
			// ȥ������ǰ��"+"
			if (strSmsc[0] == '+') strSmsc = strSmsc.Mid(1);
			if (pCh[0] == '+') pCh = pCh.Mid(1);
			// �ں���ǰ��"86"
			if (strSmsc.Left(2) != "86") strSmsc = "86" + strSmsc;
			if (pCh.Left(2) != "86") pCh = "86" + pCh;
			// ������Ϣ�ṹ
			strcpy(SmParam.SCA, strSmsc);
			strcpy(SmParam.TPA, pCh);
			strcpy(SmParam.TP_UD, strContent);
			SmParam.TP_PID = 0;
			SmParam.TP_DCS = GSM_UCS2;
			// ���Ͷ���Ϣ
			theApp.m_pSmsTraffic->PutSendMessage(&SmParam);
		}
		else
		{
			//����������ַ���
			for (int i = 0; i < StrNum; i++)
			{
				//Convert CString to char
				CString pCh = (LPSTR)(LPCTSTR)pStr[i];
				// ȥ������ǰ��"+"
				if (strSmsc[0] == '+') strSmsc = strSmsc.Mid(1);
				if (pCh[0] == '+') pCh = pCh.Mid(1);
				// �ں���ǰ��"86"
				if (strSmsc.Left(2) != "86") strSmsc = "86" + strSmsc;
				if (pCh.Left(2) != "86") pCh = "86" + pCh;
				// ������Ϣ�ṹ
				strcpy(SmParam.SCA, strSmsc);
				strcpy(SmParam.TPA, pCh);
				strcpy(SmParam.TP_UD, strContent);
				SmParam.TP_PID = 0;
				SmParam.TP_DCS = GSM_UCS2;
				// ���Ͷ���Ϣ
				theApp.m_pSmsTraffic->PutSendMessage(&SmParam);
			}
			delete[]pStr;
		}
		
		//// ȥ������ǰ��"+"
		//if (strSmsc[0] == '+') strSmsc = strSmsc.Mid(1);
		//if (strNumber[0] == '+') strNumber = strNumber.Mid(1);
		//// �ں���ǰ��"86"
		//if (strSmsc.Left(2) != "86") strSmsc = "86" + strSmsc;
		//if (strNumber.Left(2) != "86") strNumber = "86" + strNumber;
		//// ������Ϣ�ṹ
		//strcpy(SmParam.SCA, strSmsc);
		//strcpy(SmParam.TPA, strNumber);
		//strcpy(SmParam.TP_UD, strContent);
		//SmParam.TP_PID = 0;
		//SmParam.TP_DCS = GSM_UCS2;
		//// ���Ͷ���Ϣ
		//theApp.m_pSmsTraffic->PutSendMessage(&SmParam);
		// �б��м����´�
		if (pNumberWnd->FindStringExact(-1, strNumber)<0) pNumberWnd->InsertString(0, strNumber);
		if (pContentWnd->FindStringExact(-1, strContent)<0) pContentWnd->InsertString(0, strContent);
	}
	pContentWnd->SetFocus();
	pContentWnd->SetEditSel(-1, 0);
}


CString * SplitString(CString str, char split, int& iSubStrs)
{
	int iPos = 0; //�ָ��λ��
	int iNums = 0; //�ָ��������
	CString strTemp = str;
	CString strRight;
	//�ȼ������ַ���������
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
	if (iNums == 0) //û���ҵ��ָ��
	{
		//���ַ����������ַ�������
		iSubStrs = 1;
		return NULL;
	}
	//���ַ�������
	iSubStrs = iNums + 1; //�Ӵ������� = �ָ������ + 1
	CString* pStrSplit;
	pStrSplit = new CString[iSubStrs];
	strTemp = str;
	CString strLeft;
	for (int i = 0; i < iNums; i++)
	{
		iPos = strTemp.Find(split);
		//���Ӵ�
		strLeft = strTemp.Left(iPos);
		//���Ӵ�
		strRight = strTemp.Mid(iPos + 1, strTemp.GetLength());
		strTemp = strRight;
		pStrSplit[i] = strLeft;
	}
	pStrSplit[iNums] = strTemp;
	return pStrSplit;
}