#include "stdafx.h"
#include "Signal.h"

Signal::Signal()
{
}


Signal::~Signal()
{
}

void Signal::Draw(CDC *pDC)
{
	//画灯线
	CPen newPen1(PS_SOLID, 2, GRAY);
	CPen* oldPen1 = pDC->SelectObject(&newPen1);
	CPen nullPen1(PS_NULL, 2, GRAY);
	//画灯框轮廓线
	CPen newPen2(PS_SOLID, 0.5, GRAY);
	//CPen* oldPen2 = pDC->SelectObject(&newPen2);
	CPen nullPen2(PS_NULL, 2, GRAY);

	int y0 = 20;//灯柱高度
	int d = 15;//圆形灯大小


	//灯柱的位置
	CPoint p0;

	//每个灯位的位置
	CPoint p1;
	CPoint p2;
	CPoint p3;
	CPoint p4;
	CPoint p5;
	CSize size(d, d);

	//
	if (Sig_Dire == 0)
	{
		//信号机的纵坐标采用绝缘节所在，并向上抬像素点
		p0.x = Sig_Pos.x;
		p0.y = Sig_Pos.y + 5;

		p1.x = p0.x + 1;
		p1.y = p0.y;
		CRect recttmp1(p1, size);
		rect1 = recttmp1;

		p2.x = p0.x + d + 1.5;//1是留出来的空白位置
		p2.y = p0.y;
		CRect recttmp2(p2, size);
		rect2 = recttmp2;

		p3.x = p0.x - d - 1;
		p3.y = p0.y;
		CRect recttmp3(p3, size);
		rect3 = recttmp3;

		p4.x = p0.x - 2 * d - 1;
		p4.y = p0.y;
		CRect recttmp4(p4, size);
		rect4 = recttmp4;

		p5.x = p0.x - 3 * d - 1;
		p5.y = p0.y;
		CRect recttmp5(p5, size);
		rect5 = recttmp5;
	}
	else if (Sig_Dire == 1)
	{
		p0.x = Sig_Pos.x;
		p0.y = Sig_Pos.y + 5;

		p1.x = p0.x - d +2;
		p1.y = p0.y;
		CRect recttmp1(p1, size);
		rect1 = recttmp1;

		p2.x = p0.x - 2 * d + 2 ;//1是留出来的空白位置
		p2.y = p0.y;
		CRect recttmp2(p2, size);
		rect2 = recttmp2;

		p3.x = p0.x + 3.5;
		p3.y = p0.y;
		CRect recttmp3(p3, size);
		rect3 = recttmp3;

		p4.x = p0.x + d + 3.5;
		p4.y = p0.y;
		CRect recttmp4(p4, size);
		rect4 = recttmp4;

		p5.x = p0.x + 2 * d + 3.5;
		p5.y = p0.y;
		CRect recttmp5(p5, size);
		rect5 = recttmp5;
	}

	//画灯线
	pDC->MoveTo(p0);
	pDC->LineTo(p0.x, p0.y + d);
	pDC->SelectObject(oldPen1);
	pDC->SelectObject(nullPen1);



	CBrush brush(RED);
	CBrush brushGreen(DARKGREEN);
	CBrush brushBlue(SLATEBLUE);
	CBrush *nullBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

	pDC->SelectObject(&brush);
	//
	//画不同信号机类型 1进站 2出站 3调车
	switch (Sig_Type)
	{
	case 1:
		brush.DeleteObject();
		brush.CreateSolidBrush(RED);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);
		pDC->SelectObject(&newPen2);
		brush.DeleteObject();
		pDC->SelectObject(nullBrush);
		pDC->Ellipse(rect2);
		brush.CreateSolidBrush(BLUE);
		pDC->SelectObject(&brush);
		pDC->Rectangle(rect3);
		pDC->Rectangle(rect5);
		brush.DeleteObject();
		pDC->SelectObject(nullBrush);
		brush.CreateSolidBrush(GREEN);
		pDC->SelectObject(&brush);
		pDC->Rectangle(rect4);
		pDC->SelectObject(nullBrush);
		pDC->SelectObject(nullPen2);
		break;
	case 2:
		brush.DeleteObject();
		brush.CreateSolidBrush(RED);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);
		pDC->SelectObject(&newPen2);
		brush.DeleteObject();
		pDC->SelectObject(nullBrush);
		pDC->Ellipse(rect2);
		brush.CreateSolidBrush(GREEN);
		pDC->SelectObject(&brush);
		pDC->Rectangle(rect3);
		break;
	case 3:
		pDC->SelectObject(nullBrush);
		brush.DeleteObject();
		brush.CreateSolidBrush(BLUE);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);
		pDC->SelectObject(nullBrush);
		break;
	}

	//把型号不同的信号机刷成不同状态
	//1.灭灯 2.红灯 3.双黄 4.黄灯 5.绿黄 6.绿灯 7.红白 8.蓝灯 
	switch (Sig_State)
	{
	case 1:
		brush.DeleteObject();
		brush.CreateSolidBrush(GRAY);
		//CBrush *oldBrush = pDC->SelectObject(&brush);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);
		//pDC->SelectObject(oldBrush);
		pDC->SelectObject(nullBrush);
		pDC->Ellipse(rect2);//存疑，一个空刷子
		break;
	case 2:
		brush.DeleteObject();
		brush.CreateSolidBrush(RED);
		//CBrush *oldBrush = pDC->SelectObject(&brush);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);
		//pDC->SelectObject(oldBrush);
		pDC->SelectObject(nullBrush);
		pDC->Ellipse(rect2);
		break;
	case 3:
		brush.DeleteObject();
		brush.CreateSolidBrush(YELLOW);
		//CBrush *oldBrush = pDC->SelectObject(&brush);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);
		pDC->Ellipse(rect2);
		break;
	case 4:
		brush.DeleteObject();
		brush.CreateSolidBrush(YELLOW);
		//CBrush *oldBrush = pDC->SelectObject(&brush);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);
		//pDC->SelectObject(oldBrush);
		pDC->SelectObject(nullBrush);		
		break;
	case 5:
		brush.DeleteObject();
		brush.CreateSolidBrush(GREEN);
		//CBrush *oldBrush = pDC->SelectObject(&brush);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);
		//pDC->SelectObject(oldBrush);
		brush.DeleteObject();
		brush.CreateSolidBrush(YELLOW);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect2);
		//pDC->SelectObject(oldBrush);
		break;	
	case 6:
		brush.DeleteObject();
		brush.CreateSolidBrush(GREEN);
		//CBrush *oldBrush = pDC->SelectObject(&brush);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);		
		break;
	case 7:
		brush.DeleteObject();
		brush.CreateSolidBrush(RED);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);
		brush.DeleteObject();
		brush.CreateSolidBrush(WHITE);
		pDC->SelectObject(brush);
		pDC->Ellipse(rect2);
		break;
	case 8:
		brush.DeleteObject();
		brush.CreateSolidBrush(BLUE);
		//CBrush *oldBrush = pDC->SelectObject(&brush);
		pDC->SelectObject(&brush);
		pDC->Ellipse(rect1);
		//pDC->SelectObject(oldBrush);
		pDC->SelectObject(nullBrush);
		pDC->Ellipse(rect2);
		break;
	}


	//显示信号机名称
	//显示轨道电路名称
	CFont fn;
	fn.CreatePointFont(70, TEXT("微软雅黑"), pDC);
	CFont *oldfn = pDC->SelectObject(&fn);	
	
	COLORREF clr1 = WHITE;
	
	
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(clr1);
	pDC->TextOut(Sig_Pos.x, Sig_Pos.y - 19,Sig_ID);
	pDC->SetTextColor(WHITE);
	pDC->SelectObject(oldfn);
	

}
	

void Signal::CreatSig(CString Sig_ID, CPoint Sig_Pos, int Sig_Dire, int Sig_Type, int Sig_NF, int Sig_State)
{

	this->Sig_ID = Sig_ID;
	this->Sig_Pos = Sig_Pos;
	this->Sig_Dire = Sig_Dire;
	this->Sig_Type = Sig_Type;
	this->Sig_NF = Sig_NF;
	this->Sig_State = Sig_State;
}

void Signal::SetSig(int State)
{
	Sig_State = State;
}

Signal& Signal::operator=(Signal &S)
{
	this->Sig_ID = S.Sig_ID;
	this->Sig_Pos = S.Sig_Pos;
	this->Sig_Dire = S.Sig_Dire;
	this->Sig_Type = S.Sig_Type;
	this->Sig_NF = S.Sig_NF;
	this->Sig_State = S.Sig_State;
	this->error = S.error;
	return *this;
}
