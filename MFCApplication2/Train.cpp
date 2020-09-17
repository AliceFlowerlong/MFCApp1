#include "stdafx.h"
#include "Train.h"


Train::Train()
{
	

}


Train::~Train()
{
}

void Train::TrainGo(int dis)
{
	if (flag)
	{
		TraStart.x += dis;
		TraEnd.x += dis;

		TraEnd.y = 360 - (TraEnd.x - 635) * 3;
		TraStart.y = TraEnd.y;

	}
	else if (flag2)
	{
		TraStart.x += dis;
		TraEnd.x += dis;

		TraEnd.y = 270 + (TraEnd.x - 785) * 3;
		TraStart.y = TraEnd.y;
	}
	else
	{
		TraStart.x += dis;
		TraEnd.x += dis;
	}

}

void Train::Draw(CDC *pDC)
{
	CPoint p1, p2, p3, p4;
	p1.x = TraStart.x;
	p1.y = TraStart.y - 13;
	//p2.x = p1.x + 15;
	p2.y = p1.y;
	p3.x = TraEnd.x;
	p3.y = TraEnd.y - 2;
	p4.x = p1.x;
	p4.y = p3.y;
	CPen newPen(PS_SOLID, 2, BLUE);
	CPen* oldPen = pDC->SelectObject(&newPen);
	pDC->Rectangle(p1.x, p1.y, p3.x, p3.y);
}