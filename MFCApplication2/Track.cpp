#include "stdafx.h"
#include "Track.h"
#define BLACK RGB(0,0,0)
#define RED RGB(255,0,0)
#define GREEN RGB(0,200,0)
#define YELLOW RGB(255,255,0)
#define WHITE RGB(220,220,233)
#define GRAY RGB(128,128,128)
#define BLUE RGB(0,128,255)

Track::Track()
{
}


Track::~Track()
{
}

void Track::Draw(CDC* pDC)
{
	
	CPen aPen(PS_SOLID, 3, GRAY);//画股道
	CPen bPen(PS_SOLID, 2, GRAY);//画绝缘节
	CPen cPen(PS_SOLID, 2, GRAY);//道岔带动部分
	CPen dPen(PS_SOLID, 2, GREEN);//画道岔
	CPen *oldPen = pDC->SelectObject(&aPen);

	//不同颜色画笔
	switch (traState)
	{
	case 0://空闲
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, GRAY);
		pDC->SelectObject(&aPen);
		break;
	case 1://锁闭
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, WHITE);
		pDC->SelectObject(&aPen);
		break;
	case 2://正常占用
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, RED);
		pDC->SelectObject(&aPen);
		break;
	case 3://故障占用
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, RED);
		pDC->SelectObject(&aPen);
		break;
	case 4://不正常解锁
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3,GREEN);
		pDC->SelectObject(&aPen);
		break;
	default:
		break;
	}

	//显示轨道电路名称
	CFont fn;
	fn.CreatePointFont(70, TEXT("微软雅黑"), pDC);
	CFont *oldfn = pDC->SelectObject(&fn);
	CPoint CodePos;
	CodePos.x = (traStart.x + traEnd.x) / 2;
	CodePos.y = traStart.y + 10;
	CString StrCode;
	StrCode = TraID;
	COLORREF clr1;	
	clr1 = WHITE;
	

	//道岔部分不显示名称，其他则显示
	if (traType == 1 || traType == 2)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(clr1);
		pDC->TextOut(CodePos.x - 8, CodePos.y, StrCode);
		pDC->SetTextColor(WHITE);
		pDC->SelectObject(oldfn);
	}
	

	

	//
	
	//轨道电路不同类型画图
	//1 离去接近 2绝缘节股道 3.双动道岔 4.单动道岔 5.道岔连接部分 6.道岔节点
	switch (traType)
	{
	case 1:
		pDC->MoveTo(traStart);
		pDC->LineTo(traEnd);
		pDC->SelectObject(oldPen);
		break;
	case 2:
		pDC->MoveTo(traStart);
		pDC->LineTo(traEnd);
		pDC->SelectObject(oldPen);
		pDC->SelectObject(bPen);
		pDC->MoveTo(traStart.x, traStart.y + 5);
		pDC->LineTo(traStart.x, traStart.y - 5);
		pDC->MoveTo(traEnd.x, traEnd.y + 5);
		pDC->LineTo(traEnd.x, traEnd.y - 5);
		pDC->SelectObject(oldPen);
		break;
	case 3:
	
		pDC->MoveTo(traStart);
		pDC->LineTo(traEnd);
		pDC->SelectObject(oldPen);
		pDC->SelectObject(bPen);
		//画绝缘节
		pDC->MoveTo(((traStart.x + traEnd.x) / 2 ), (traStart.y + traEnd.y) / 2 - 5);
		pDC->LineTo(((traStart.x + traEnd.x) / 2 ), (traStart.y + traEnd.y) / 2 + 5);
		pDC->SelectObject(oldPen);
		break;
	case 4:
		pDC->MoveTo(traStart);
		pDC->LineTo(traEnd);
		pDC->SelectObject(oldPen);
		pDC->SelectObject(bPen);
		pDC->MoveTo(((traStart.x + traEnd.x) / 2), (traStart.y + traEnd.y) / 2 - 5);
		pDC->LineTo(((traStart.x + traEnd.x) / 2), (traStart.y + traEnd.y) / 2 + 5);
		pDC->SelectObject(oldPen);
		break;
	case 5:
		pDC->MoveTo(traStart);
		pDC->LineTo(traEnd);
		pDC->SelectObject(oldPen);
		break;
	case 6:
		pDC->MoveTo(traStart);
		pDC->LineTo(traEnd);
		pDC->SelectObject(dPen);
		break;
	default:
		break;
	}
		
	
}

void Track::setCode(int Code)
{
	this->traCode = Code;
}

void Track::createTra(CString TraID, CPoint traStart, CPoint traEnd, int traType, int traState, int traCode)
{
	this->TraID = TraID;
	this->traStart = traStart;
	this->traEnd = traEnd;
	this->traType = traType;
	this->traState = traState;
	this->traCode = traCode;
}

Track& Track::operator=(Track &T)
{
	this->TraID = T.TraID;
	this->traStart = T.traStart;
	this->traEnd = T.traEnd;
	this->traType = T.traType;
	this->traState = T.traState;
	this->traCode = T.traCode;
	this->error = T.error;
	this->lock = T.lock;
	this->lock1 = T.lock1;
	this->lock2 = T.lock2;
	this->Intrusion = T.Intrusion;
	this->DefectiveShunting = T.DefectiveShunting;
	this->flag = T.flag;
	return *this;
}

void Track::suobi(Track t)
{
	this->flag = t.flag;
	this->lock = t.lock;
	this->lock1 = t.lock1;
	this->lock2 = t.lock2;
	this->traState = t.traState;
}