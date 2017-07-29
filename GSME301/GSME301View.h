
// GSME301View.h : CGSME301View 类的接口
//

#pragma once


class CGSME301View : public CListView
{
protected: // 仅从序列化创建
	CGSME301View();
	DECLARE_DYNCREATE(CGSME301View)

// 特性
public:
	CGSME301Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGSME301View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
//	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // GSME301View.cpp 中的调试版本
inline CGSME301Doc* CGSME301View::GetDocument() const
   { return reinterpret_cast<CGSME301Doc*>(m_pDocument); }
#endif

