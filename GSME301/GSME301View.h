
// GSME301View.h : CGSME301View ��Ľӿ�
//

#pragma once


class CGSME301View : public CListView
{
protected: // �������л�����
	CGSME301View();
	DECLARE_DYNCREATE(CGSME301View)

// ����
public:
	CGSME301Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGSME301View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
//	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // GSME301View.cpp �еĵ��԰汾
inline CGSME301Doc* CGSME301View::GetDocument() const
   { return reinterpret_cast<CGSME301Doc*>(m_pDocument); }
#endif

