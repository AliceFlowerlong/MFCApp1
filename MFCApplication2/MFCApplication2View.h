
// MFCApplication2View.h: CMFCApplication2View 类的接口
//
#include<vector>
#pragma once
using namespace std;


class CMFCApplication2View : public CView
{
protected: // 仅从序列化创建
	CMFCApplication2View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication2View)

// 特性
public:
	CMFCApplication2Doc* GetDocument() const;

// 操作
public:
	//按钮
	CButton *GuideButton;//引导总锁闭按钮
	CButton *CancelBtn;//取消进路按钮
	CButton *ManCancelBtn;//人工取消进路按钮
	CButton *TrackClearBtn;//区段故障解锁按钮
	CButton *AllFixedBtn;//总定位
	CButton *AllUnFixedBtn;//总反位
	CButton *ReOpenBtn;//信号重开


	
public:
	Signal sig1, sig2;//进路始端、终端记录
	bool StopFlag;//用以暂停程序运行（暂停走车）
	int StartSigIndex;//记录始端信号机是哪一位


public:
	void Routeselection();//建立进路
	void LockTrack();//锁闭进路
	void ClearAllData();

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void DrawStation(CDC *pDC);//尝试利用双缓冲问题解决闪烁
	void DrawTrackGray(CDC* pDC);//画灰线
	void Write_Name(CDC* pDC);//写名字
	void DrawBackGround(CDC* pDC);//
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void TrackOccupied();
	afx_msg void ClearTrackOccupied();
	afx_msg void ManClearTrack();
	afx_msg void CrossFixed();
	afx_msg void CrossUnfixed();
	afx_msg void CrossOccupied();
	afx_msg void ClearCrossOccupied();
	afx_msg void OnBtnGuideDown();
	afx_msg void OnBtnCancelDown();
	afx_msg void OnBtnTrackClearDown();
	afx_msg void OnBtnManCancelDown();
	afx_msg void OnBtnReOpenDown();
	afx_msg void OnBtnAllfixedDown();
	afx_msg void OnBtnAllUnfixedDown();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MFCApplication2View.cpp 中的调试版本
inline CMFCApplication2Doc* CMFCApplication2View::GetDocument() const
   { return reinterpret_cast<CMFCApplication2Doc*>(m_pDocument); }
#endif

