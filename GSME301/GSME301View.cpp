
// GSME301View.cpp : CGSME301View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GSME301.h"
#endif

#include "GSME301Doc.h"
#include "GSME301View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGSME301View
IMPLEMENT_DYNCREATE(CGSME301View, CListView)
BEGIN_MESSAGE_MAP(CGSME301View, CListView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
//	ON_NOTIFY_REFLECT(NM_CLICK, &CGSME301View::OnNMClick)
ON_WM_TIMER()
END_MESSAGE_MAP()

// CGSME301View ����/����
CGSME301View::CGSME301View()
{
	// TODO: �ڴ˴���ӹ������

}

CGSME301View::~CGSME301View()
{
}

BOOL CGSME301View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	cs.style |= LVS_SHOWSELALWAYS | LVS_REPORT;
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CListView::PreCreateWindow(cs);
}

// CGSME301View ����

void CGSME301View::OnDraw(CDC* /*pDC*/)
{
	CGSME301Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGSME301View ��ӡ

BOOL CGSME301View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGSME301View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGSME301View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CGSME301View ���

#ifdef _DEBUG
void CGSME301View::AssertValid() const
{
	CListView::AssertValid();
}

void CGSME301View::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CGSME301Doc* CGSME301View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGSME301Doc)));
	return (CGSME301Doc*)m_pDocument;
}
#endif //_DEBUG


// CGSME301View ��Ϣ�������


void CGSME301View::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CListCtrl& ListCtrl = GetListCtrl();

	//ListCtrl.InsertColumn(0, "", LVCFMT_LEFT, 30);
	ListCtrl.InsertColumn(0, "����", LVCFMT_LEFT, 100);
	ListCtrl.InsertColumn(1, "ʱ��", LVCFMT_LEFT, 140);
	ListCtrl.InsertColumn(2, "��Ϣ����", LVCFMT_LEFT, 500);

	SetTimer(1, 1000, NULL);//���ö�ʱ��1��ÿ�봥��һ��

}


BOOL CGSME301View::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	KillTimer(1);//�رն�ʱ��1

	return CListView::DestroyWindow();
}


//void CGSME301View::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}


void CGSME301View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (nIDEvent == 1) //��Ӧ 3 �е� SetTimer(1, 1000, NULL)
	{
		SM_PARAM SmParam;
		CString strTime;
		CString strNumber;
		CString strContent;
		CListCtrl& ListCtrl = GetListCtrl();
		// ȡ���յ��Ķ���Ϣ
		if (theApp.m_pSmsTraffic->GetRecvMessage(&SmParam))
		{
			// ȡ����Ϣ��Ϣ
			strNumber = SmParam.TPA;
			strContent = SmParam.TP_UD;
			strTime = "20" + CString(&SmParam.TP_SCTS[0], 2)
				+ "-" + CString(&SmParam.TP_SCTS[2], 2)
				+ "-" + CString(&SmParam.TP_SCTS[4], 2)
				+ " " + CString(&SmParam.TP_SCTS[6], 2)
				+ ":" + CString(&SmParam.TP_SCTS[8], 2)
				+ ":" + CString(&SmParam.TP_SCTS[10], 2);
			// ȥ������ǰ��"86"
			if (strNumber.Left(2) == "86") strNumber = strNumber.Mid(2);
			// ��ౣ�� 200 ��
			int nItemCount = ListCtrl.GetItemCount();
			if (nItemCount >= 200)
			{
				ListCtrl.DeleteItem(0);
				nItemCount--;
			}
			// ��������Ϣ
			ListCtrl.InsertItem(nItemCount, strNumber);
			ListCtrl.SetItemText(nItemCount, 1, strTime);
			ListCtrl.SetItemText(nItemCount, 2, strContent);
			ListCtrl.EnsureVisible(nItemCount, FALSE);
		}
	}
	else
	{
		// other timers
		CListView::OnTimer(nIDEvent);
	}
	//CListView::OnTimer(nIDEvent);
}