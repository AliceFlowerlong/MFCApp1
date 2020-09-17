
// MFCApplication2View.cpp: CMFCApplication2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//?
CPoint point1;
CPoint point2;

// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32771, &CMFCApplication2View::TrackOccupied)
	ON_COMMAND(ID_32772, &CMFCApplication2View::ClearTrackOccupied)
	ON_COMMAND(ID_32773, &CMFCApplication2View::ManClearTrack)
	ON_COMMAND(ID_32774, &CMFCApplication2View::CrossFixed)
	ON_COMMAND(ID_32775, &CMFCApplication2View::CrossUnfixed)
	ON_COMMAND(ID_32776, &CMFCApplication2View::CrossOccupied)
	ON_COMMAND(ID_32777, &CMFCApplication2View::ClearCrossOccupied)

	ON_COMMAND(IDB_BTN_GUIDE, &CMFCApplication2View::OnBtnGuideDown)
	ON_COMMAND(IDB_BTN_CANCEL, &CMFCApplication2View::OnBtnCancelDown)
	ON_COMMAND(IDB_BTN_MANCANCEL, &CMFCApplication2View::OnBtnManCancelDown)
	ON_COMMAND(IDB_BTN_TRACKCLEAR, &CMFCApplication2View::OnBtnTrackClearDown)
	ON_COMMAND(IDB_BTN_FIXED, &CMFCApplication2View::OnBtnAllfixedDown)
	ON_COMMAND(IDB_BTN_UNFIXED, &CMFCApplication2View::OnBtnAllUnfixedDown)
	ON_COMMAND(IDB_BTN_REOPEN, &CMFCApplication2View::OnBtnReOpenDown)

	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCApplication2View 构造/析构

CMFCApplication2View::CMFCApplication2View() noexcept
{
	sig1.Sig_ID = _T("NONE");
	sig2.Sig_ID = _T("NONE");
	StopFlag = false;
	StartSigIndex = 0;
	// TODO: 在此处添加构造代码

}

CMFCApplication2View::~CMFCApplication2View()
{
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication2View 绘图

void CMFCApplication2View::OnDraw(CDC* pDC)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	

	DrawStation(pDC);//双缓冲绘图
	
	//设置一个50ms的定时器，用于走车
	SetTimer(1, 10, NULL);

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplication2View 打印

BOOL CMFCApplication2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication2View 诊断

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication2View 消息处理程序

void CMFCApplication2View::DrawStation(CDC *pDC)
{

	
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	

	//双缓冲绘图
	CDC MemDC;//新建内存DC
	CBitmap MemBitmap;//新建位图
	CRect memRc;

	GetClientRect(&memRc);//获得客户区矩形大小
	//memRc.bottom = memRc.bottom - 150;

	MemDC.CreateCompatibleDC(pDC);//创建与目标DC兼容的内存DC
	MemBitmap.CreateCompatibleBitmap(pDC, memRc.Width(), memRc.Height()-150);//根据目标DC创建相应的位图
	MemDC.SelectObject(&MemBitmap);//把位图选入内存DC

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));//为内存DC创建画刷
	MemDC.SelectObject(&brush);//将画刷选入内存DC
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);

	//先用背景色将位图清理干净，这里用黑色	
	MemDC.FillSolidRect(memRc.left, memRc.top, memRc.Width(), memRc.Height(), BLACK);
	

	pDC->SetTextColor(WHITE);
	pDC->SetBkColor(BLACK);
	
	for (int i = 0; i < SigNum; i++)
	{
		pDoc->Sig[i].Draw(&MemDC);
	}//绘制信号机

	for (int i = 0; i < TraNum; i++)
	{
		pDoc->Tra[i].Draw(&MemDC);
	}//绘制轨道电路

	for (int i = 0; i < CroNum; i++)
	{
		pDoc->Cro[i].Draw(&MemDC);
		
	}//绘制轨道电路

	//检验Cro是否读入
	pDoc->Lock[pDoc->LockingIndex].PrintAllCro(&MemDC);

	//
	DrawTrackGray(&MemDC);

	

	CString str, str2, str3,str4,str5;
	//str.Format(_T("hasdj:  %d = "), pDoc->Cro[pDoc->LockingIndex].Cro_State);

	str2.Format(_T("已按下始端按钮 ：") + sig1.Sig_ID);
	/*str3.Format(_T("已按下终端按钮 ：") + sig2.Sig_ID);
	str4.Format(_T("第几条进路: %d    引导总锁闭状态: %d  轨道电路第几段 %d") , pDoc->LockingIndex, pDoc->GuideFlag, pDoc->TrackIndex);
	str5.Format(_T("bSigFlag：%d  SigFlag：%d  CroFlag：%d  TraFlag：%d ComingFlag：%d"), pDoc->bSigFlag, pDoc->SigFlag, pDoc->CroFlag, pDoc->TraFlag, pDoc->ComingFlag);
	
	MemDC.TextOut(200, 40, str);
	
	MemDC.TextOut(20, 60, str3);
	MemDC.TextOut(20, 80, str4);
	MemDC.TextOut(20, 100, str5);*/
	MemDC.TextOut(20, 40, str2);

	Write_Name(&MemDC);
	
	pDC->BitBlt(memRc.left, memRc.top, memRc.Width(), memRc.Height(), &MemDC, 0, 0, SRCCOPY);//将内存DC上的全部内容放入pDC,这样才会在显示窗口上显示出来
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}

void CMFCApplication2View::DrawBackGround(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));//为内存DC创建画刷
	
	pDC->SelectObject(&brush);
	pDC->Rectangle(rc);
}


int CMFCApplication2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GuideButton = new CButton;
	CancelBtn = new CButton;//取消进路按钮
	ManCancelBtn = new CButton;//人工取消进路按钮
	TrackClearBtn = new CButton;//区段故障解锁按钮
	AllFixedBtn = new CButton;//总定位
	AllUnFixedBtn = new CButton;//总反位
	ReOpenBtn = new CButton;//信号重开

	GuideButton->Create(_T("引导总锁闭"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(100, 550, 185, 580), this, IDB_BTN_GUIDE);
	CancelBtn->Create(_T("取消进路"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(195, 550, 270, 580), this, IDB_BTN_CANCEL);
	ManCancelBtn->Create(_T("人工取消"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(280, 550, 355, 580), this, IDB_BTN_MANCANCEL);
	TrackClearBtn->Create(_T("区段故障解锁"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(365, 550, 470, 580), this, IDB_BTN_TRACKCLEAR);	AllFixedBtn->Create(_T("总定位"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(480, 550, 540, 580), this, IDB_BTN_FIXED);
	AllUnFixedBtn->Create(_T("总反位"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(550, 550, 610, 580), this, IDB_BTN_UNFIXED);
	ReOpenBtn->Create(_T("信号重开"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(620, 550, 700, 580), this, IDB_BTN_REOPEN);
		
	return 0;
}


BOOL CMFCApplication2View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CView::OnEraseBkgnd(pDC);
}


void CMFCApplication2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	point1.x = point.x;
	point1.y = point.y;//保存鼠标左击位置	


	//画图准备
	CDC *pDC = GetDC();
	pDC->SetTextColor(WHITE);
	pDC->SetBkColor(BLACK);

	//测试左键点击是否有反应
	CString str;
	CString str1;
	CString str2;	
	
	//第一次点击是否记录下信号机	

	bool flag;
	flag = false;
	for (int i = 0; i < SigNum; i++)
	{

		CPoint p;
		if (pDoc->Sig[i].Sig_Dire == 1)
		{
			p.x = pDoc->Sig[i].Sig_Pos.x;
			p.y = pDoc->Sig[i].Sig_Pos.y ;
		}
		if (pDoc->Sig[i].Sig_Dire == 0)
		{
			p.x = pDoc->Sig[i].Sig_Pos.x - 5 ;
			p.y = pDoc->Sig[i].Sig_Pos.y - 10;
		}

		//列车进路点击方块
		//30刚好是两个灯位的距离
		if (point.x > p.x - 15 &&point.x<p.x + 30 && point.y >p.y&&point.y < p.y + 30)
		{
			flag = true;
			
			if (true)//进站信号机
			{
				
				if (sig1.Sig_ID == _T("NONE") && sig2.Sig_ID == _T("NONE"))
				{
					sig1 = pDoc->Sig[i];		
					StartSigIndex = i;

				}
				else if (sig1.Sig_ID != _T("NONE") && sig2.Sig_ID == _T("NONE"))
				{
					sig2 = pDoc->Sig[i];
					//pDoc->Sig[i].SetSig(4);
					//str.Format(TEXT("x = %d"), pDoc->Sig[i].Sig_State);
					//MessageBox(str);
					Routeselection();
					
				}
				else if (sig1.Sig_ID != _T("NONE") && sig2.Sig_ID != _T("NONE"))
				{					
					Routeselection();
				}
				else
				{
					sig1.Sig_ID = _T("NONE");
					sig2.Sig_ID = _T("NONE");
					
				}
			}
			
		}	

	}
	if (!flag)
	{
		sig1.Sig_ID = _T("NONE");
		sig2.Sig_ID = _T("NONE");
	}
	
	Invalidate(false);

	ReleaseDC(pDC);
	
	//选择进路
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnLButtonUp(nFlags, point);
}


void CMFCApplication2View::OnRButtonUp(UINT nFlags, CPoint point)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	point1.x = point.x;
	point1.y = point.y;//保存鼠标右击位置	
	CPoint pos;
	GetCursorPos(&pos);//控制菜单出现位置
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CMenu *TrackMenu = menu.GetSubMenu(0);//轨道电路菜单	
	CMenu *CrossMenu = menu.GetSubMenu(1);//道岔菜单

	for (int i = 0; i < TraNum; i++)
	{
		if (pDoc->Tra[i].traStart.x < point.x&&pDoc->Tra[i].traEnd.x>point.x&&point.y - pDoc->Tra[i].traStart.y<2 && point.y - pDoc->Tra[i].traStart.y > -2)
		{
			TrackMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pos.x, pos.y, GetParent());
		}

	}//控制轨道电路相关菜单
	
	for (int i = 0; i < CroNum; i++)
	{
		if (pDoc->Cro[i].Cro_Pos.x > point.x - 4 && pDoc->Cro[i].Cro_Pos.x < point.x + 4 && pDoc->Cro[i].Cro_Pos.y > point.y -5  && pDoc->Cro[i].Cro_Pos.y < point.y + 5)
		{
			CrossMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pos.x, pos.y, GetParent());
		}

	}//控制道岔相关菜单


	

}


BOOL CMFCApplication2View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	HCURSOR hCur1 = LoadCursor(NULL, IDC_HAND);
	HCURSOR hCur2 = LoadCursor(NULL, IDC_ARROW);


	::SetCursor(hCur2);


	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;
	point1.x = point2.x;
	point1.y = point2.y;//保存鼠标	
	CPoint pos;

	
	//信号机部分
	for (int i = 0; i < SigNum; i++)
	{
		CPoint p;
		if (pDoc->Sig[i].Sig_Dire == 1)
		{
			p.x = pDoc->Sig[i].Sig_Pos.x;
			p.y = pDoc->Sig[i].Sig_Pos.y ;
		}
		if (pDoc->Sig[i].Sig_Dire == 0)
		{
			p.x = pDoc->Sig[i].Sig_Pos.x ;
			p.y = pDoc->Sig[i].Sig_Pos.y ;
		}

		if (point2.x > p.x - 15 &&point2.x<p.x + 30 && point2.y>p.y&&point2.y < p.y + 20)
		{
			
			::SetCursor(hCur1);
			
		}
	}//控制信号机相关菜单
	return true;
	return CView::OnSetCursor(pWnd, nHitTest, message);
}





void CMFCApplication2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDC();
	CString str;
	pDC->SetTextColor(WHITE);
	pDC->SetBkColor(BLACK);
	str.Format(_T("%d,%d   "), point.x, point.y);
	pDC->TextOut(20, 20, str);
	ReleaseDC(pDC);
	
	point2 = point;
	CView::OnMouseMove(nFlags, point);
	
}


void CMFCApplication2View::Routeselection()
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CString str;
	

	pDoc->ButtonSigCheck(sig1.Sig_ID, sig2.Sig_ID);
	pDoc->OccupySignalCheck();
	pDoc->OccupyTrackCheck();
	

	if (pDoc->bSigFlag && pDoc->TraFlag&& pDoc->SigFlag)
	{
		pDoc->Sig[StartSigIndex].SetSig(pDoc->Lock[pDoc->LockingIndex].Lock_SigState);
		pDoc->OccupyCrossingCheck();//道岔就位
		LockTrack();//锁闭进路
		
	}
	else if (pDoc->bSigFlag && pDoc->GuideFlag)
	{
		pDoc->Sig[StartSigIndex].SetSig(7);//红白灯
	}
	else
	{
		MessageBox(_T("接车进路建立失败"));
		
	}
				

}

void CMFCApplication2View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnTimer(nIDEvent);
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OccupyCrossingCheck();
	pDoc->OccupySignalCheck();
	pDoc->OccupyTrackCheck();

	if ((pDoc->CroFlag && pDoc->bSigFlag && pDoc->TraFlag&& pDoc->SigFlag)||pDoc->GuideFlag)
	{

	}
	else
	{
		pDoc->Sig[StartSigIndex].SetSig(2);
	}
	
	pDoc->ThreePointCheck();
	
	Invalidate(false);


	CView::OnTimer(nIDEvent);
}


void CMFCApplication2View::LockTrack()
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;	

	for (int i = 0; i < pDoc->Lock[pDoc->LockingIndex].LockTraNum; i++)
	{
		for (int j = 0; j < TraNum; j++)
		{
			if (pDoc->Tra[j].TraID == pDoc->Lock[pDoc->LockingIndex].Locking_Tra[i] \
				&& pDoc->Tra[j].traState == 0)
			{
				pDoc->Tra[j].traState = 1;//锁闭状态			
			}
		}
	}

	if (pDoc->Cro[0].Cro_State == 2 && pDoc->Cro[1].Cro_State == 2)
	{
		pDoc->Tra[13].traState = 1;
	}

	if (pDoc->Cro[2].Cro_State == 2 && pDoc->Cro[3].Cro_State == 2)
	{
		pDoc->Tra[14].traState = 1;
	}
	if (pDoc->Cro[4].Cro_State == 2)
	{
		pDoc->Tra[15].traState = 1;
		pDoc->Tra[16].traState = 1;
	}
	if (pDoc->Cro[5].Cro_State == 2)
	{
		pDoc->Tra[17].traState = 1;
		pDoc->Tra[18].traState = 1;
	}

	
	

	Invalidate(false);
}
void CMFCApplication2View::DrawTrackGray(CDC* pDC)//画灰线
{
	
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen aPen(PS_SOLID, 3, GRAY);//画股道
	pDC->SelectObject(&aPen);

	//双动道岔轨道电路
	int i = 0,j=0,k=0;
	for ( i=0; i < pDoc->Lock[pDoc->LockingIndex].LockCroNum; i++)//所有进路道岔循环检查是否反位
	{
		if (pDoc->Lock[pDoc->LockingIndex].Locking_CroState[i] == 2)//道岔反位
		{
			for (j = 0; j < CroNum; j++)
			{
				if (pDoc->Lock[pDoc->LockingIndex].Locking_Cro[i] == pDoc->Cro[j].Cro_Id)//找出这个道岔
				{
					for (k = 0; k < TraNum; k++)//这个道岔在哪一个轨道电路中
					{
						if (pDoc->Cro[j].Cro_Pos.x > pDoc->Tra[k].traStart.x &&pDoc->Cro[j].Cro_Pos.x < pDoc->Tra[k].traEnd.x\
							&&pDoc->Cro[j].Cro_Pos.y == pDoc->Tra[k].traStart.y)
						{
							switch (pDoc->Cro[j].Cro_type)//根据道岔类型去画灰色的线
							{
							case 1:
								pDC->MoveTo(pDoc->Cro[j].Cro_Pos.x+8, pDoc->Cro[j].Cro_Pos.y );
								pDC->LineTo(pDoc->Tra[k].traStart);
								break;
							case 2:
								pDC->MoveTo(pDoc->Cro[j].Cro_Pos.x + 8, pDoc->Cro[j].Cro_Pos.y );
								pDC->LineTo(pDoc->Tra[k].traEnd);
								break;
							case 3:
								pDC->MoveTo(pDoc->Cro[j].Cro_Pos);
								pDC->LineTo(pDoc->Tra[k].traEnd);
								break;
							case 4:
								pDC->MoveTo(pDoc->Cro[j].Cro_Pos);
								pDC->LineTo(pDoc->Tra[k].traStart);
								break;
							default :
								break;
							}
						}
						continue;
					}

				}
				
			}
		}
	}

}

void CMFCApplication2View::TrackOccupied()
{
	//菜单轨道故障占用响应程序
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rc;
	CPoint Pos;	
	
	CString str2;
	Pos = point1;
	for (int i = 0; i < TraNum; i++)
	{
		if (pDoc->Tra[i].traStart.x < Pos.x&&pDoc->Tra[i].traEnd.x>Pos.x \
			&&Pos.y - pDoc->Tra[i].traStart.y<2 && Pos.y - pDoc->Tra[i].traStart.y > -2)
		{
			pDoc->Tra[i].traState = 2;
			pDoc->Tra[i].error = true;		
		}
	}

	pDoc->TrackIndex++;

	Invalidate(false);

}


void CMFCApplication2View::ClearTrackOccupied()
{
	//菜单轨道清除故障占用响应程序
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CPoint Pos;	
	Pos = point1;
	for (int i = 0; i < TraNum; i++)
	{
		if (pDoc->Tra[i].traStart.x < Pos.x&&pDoc->Tra[i].traEnd.x>Pos.x \
			&&Pos.y - pDoc->Tra[i].traStart.y<2 && Pos.y - pDoc->Tra[i].traStart.y > -2)
		{
			pDoc->Tra[i].traState = 0;
			pDoc->Tra[i].flag = false;
			pDoc->Tra[i].lock = false;
			pDoc->Tra[i].lock1 = false;
			pDoc->Tra[i].lock2 = false;
			pDoc->Tra[i].error = false;
		
		}
	}	
	pDoc->TrackIndex--;
	Invalidate(false);	
}


void CMFCApplication2View::ManClearTrack()
{
	// TODO: 在此添加命令处理程序代码
	//菜单轨道清除故障占用响应程序
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPoint Pos;
	Pos = point1;
	for (int i = 0; i < TraNum; i++)
	{
		if (pDoc->Tra[i].traStart.x < Pos.x&&pDoc->Tra[i].traEnd.x>Pos.x \
			&&Pos.y - pDoc->Tra[i].traStart.y<2 && Pos.y - pDoc->Tra[i].traStart.y > -2)
		{
			pDoc->Tra[i].traState = 4;
			pDoc->Tra[i].flag = false;
			pDoc->Tra[i].lock = false;
			pDoc->Tra[i].lock1 = false;
			pDoc->Tra[i].lock2 = false;
			pDoc->Tra[i].error = false;

		}
	}
	pDoc->TrackIndex--;
	Invalidate(false);
}


void CMFCApplication2View::CrossFixed()
{
	// TODO: 在此添加命令处理程序代码
	//菜单轨道清除故障占用响应程序
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPoint Pos;
	Pos = point2;
	for (int i = 0; i < CroNum; i++)
	{
		if (pDoc->Cro[i].Cro_Pos.x > Pos.x - 2 && pDoc->Cro[i].Cro_Pos.x < Pos.x + 2 \
			&&pDoc->Cro[i].Cro_Pos.y > Pos.y  && pDoc->Cro[i].Cro_Pos.y < Pos.y + 5)
		{
			pDoc->Cro[i].SetCro(1);
		}

	}

	Invalidate(false);
}


void CMFCApplication2View::CrossUnfixed()
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPoint Pos;
	Pos = point2;
	for (int i = 0; i < CroNum; i++)
	{
		if (pDoc->Cro[i].Cro_Pos.x > Pos.x - 3 && pDoc->Cro[i].Cro_Pos.x<Pos.x + 3 \
			&&pDoc->Cro[i].Cro_Pos.y > Pos.y  && pDoc->Cro[i].Cro_Pos.y < Pos.y + 5)
		{
			pDoc->Cro[i].SetCro(2);
		}

	}

	Invalidate(false);
}


void CMFCApplication2View::CrossOccupied()
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPoint Pos;
	Pos = point2;
	for (int i = 0; i < CroNum; i++)
	{
		if (pDoc->Cro[i].Cro_Pos.x > Pos.x - 2 && pDoc->Cro[i].Cro_Pos.x<Pos.x + 2 \
			&&pDoc->Cro[i].Cro_Pos.y > Pos.y  && pDoc->Cro[i].Cro_Pos.y < Pos.y + 5)
		{
			pDoc->Cro[i].Cro_State = 3;
		}

	}
	Invalidate(false);
}


void CMFCApplication2View::ClearCrossOccupied()
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPoint Pos;
	Pos = point2;
	for (int i = 0; i < CroNum; i++)
	{
		if (pDoc->Cro[i].Cro_Pos.x > Pos.x - 2 && pDoc->Cro[i].Cro_Pos.x<Pos.x + 2 \
			&&pDoc->Cro[i].Cro_Pos.y > Pos.y  && pDoc->Cro[i].Cro_Pos.y < Pos.y + 5)
		{
			pDoc->Cro[i].Cro_State = 1;
		}

	}
	Invalidate(false);
}


void CMFCApplication2View::OnBtnGuideDown()
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->GuideFlag)
	{
		pDoc->GuideFlag = false;
		MessageBox(_T("关闭引导总锁闭！"));
		pDoc->Sig[StartSigIndex].SetSig(0);
	}
	else
	{
		pDoc->GuideFlag = true;
		MessageBox(_T("建立引导总锁闭！"));
	}
		
	Invalidate(false);
}


void CMFCApplication2View::OnBtnCancelDown()
{
	ClearAllData();
}
void CMFCApplication2View::OnBtnTrackClearDown()
{}
void CMFCApplication2View::OnBtnManCancelDown()
{}
void CMFCApplication2View::OnBtnReOpenDown()
{}
void CMFCApplication2View::OnBtnAllfixedDown()
{}
void CMFCApplication2View::OnBtnAllUnfixedDown()
{}


void CMFCApplication2View::ClearAllData()
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	for (int i = 0; i < SigNum; i++)
	{
		pDoc->Sig[i].Sig_State = 2;
	}

	for (int i = 0; i < TraNum; i++)
	{
		pDoc->Tra[i].traState = 0;
	}

	for (int i = 0; i < CroNum; i++)
	{
		pDoc->Cro[i].Cro_State = 1;

	}

	pDoc->bSigFlag = false;
	pDoc->SigFlag = false;
	pDoc->CroFlag = false;
	pDoc->TraFlag = false;
	pDoc->ComingFlag = false;

	pDoc->LockingIndex = 0;
	pDoc->TrackIndex = 0;

}


void CMFCApplication2View::Write_Name(CDC *p)
{
	CFont font;
	font.CreatePointFont(100, TEXT("微软雅黑"), p); //参数含义1，字体大小，2字体类型，3字体颜色

	p->SelectObject(&font);

	p->SetBkColor(RGB(0, 0, 0));//将背景设为黑色
	p->SetTextColor(RGB(255, 255, 255));
	p->TextOutW(333, 32, TEXT("轨道2016-04班 陈静欣  2016112351"));
	p->TextOutW(22, 157, TEXT("北"));
	p->TextOutW(22, 224, TEXT("京"));
	p->TextOutW(22, 290, TEXT("方"));
	p->TextOutW(22, 360, TEXT("面"));
	
}

