
// GSME301View.cpp : CGSME301View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
//	ON_NOTIFY_REFLECT(NM_CLICK, &CGSME301View::OnNMClick)
ON_WM_TIMER()
END_MESSAGE_MAP()

// CGSME301View 构造/析构
CGSME301View::CGSME301View()
{
	// TODO: 在此处添加构造代码

}

CGSME301View::~CGSME301View()
{
}

BOOL CGSME301View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	cs.style |= LVS_SHOWSELALWAYS | LVS_REPORT;
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

// CGSME301View 绘制

void CGSME301View::OnDraw(CDC* /*pDC*/)
{
	CGSME301Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGSME301View 打印

BOOL CGSME301View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGSME301View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGSME301View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGSME301View 诊断

#ifdef _DEBUG
void CGSME301View::AssertValid() const
{
	CListView::AssertValid();
}

void CGSME301View::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CGSME301Doc* CGSME301View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGSME301Doc)));
	return (CGSME301Doc*)m_pDocument;
}
#endif //_DEBUG


// CGSME301View 消息处理程序


void CGSME301View::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CListCtrl& ListCtrl = GetListCtrl();

	//ListCtrl.InsertColumn(0, "", LVCFMT_LEFT, 30);
	ListCtrl.InsertColumn(0, "号码", LVCFMT_LEFT, 100);
	ListCtrl.InsertColumn(1, "时间", LVCFMT_LEFT, 140);
	ListCtrl.InsertColumn(2, "消息内容", LVCFMT_LEFT, 500);

	SetTimer(1, 1000, NULL);//设置定时器1，每秒触发一次

}


BOOL CGSME301View::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	KillTimer(1);//关闭定时器1

	return CListView::DestroyWindow();
}


//void CGSME301View::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}


void CGSME301View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == 1) //对应 3 中的 SetTimer(1, 1000, NULL)
	{
		SM_PARAM SmParam;
		CString strTime;
		CString strNumber;
		CString strContent;
		CListCtrl& ListCtrl = GetListCtrl();
		// 取接收到的短消息
		if (theApp.m_pSmsTraffic->GetRecvMessage(&SmParam))
		{
			// 取短消息信息
			strNumber = SmParam.TPA;
			strContent = SmParam.TP_UD;
			strTime = "20" + CString(&SmParam.TP_SCTS[0], 2)
				+ "-" + CString(&SmParam.TP_SCTS[2], 2)
				+ "-" + CString(&SmParam.TP_SCTS[4], 2)
				+ " " + CString(&SmParam.TP_SCTS[6], 2)
				+ ":" + CString(&SmParam.TP_SCTS[8], 2)
				+ ":" + CString(&SmParam.TP_SCTS[10], 2);
			// 去掉号码前的"86"
			if (strNumber.Left(2) == "86") strNumber = strNumber.Mid(2);
			// 最多保留 200 条
			int nItemCount = ListCtrl.GetItemCount();
			if (nItemCount >= 200)
			{
				ListCtrl.DeleteItem(0);
				nItemCount--;
			}
			// 插入新消息
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