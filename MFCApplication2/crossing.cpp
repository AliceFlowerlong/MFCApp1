#include "stdafx.h"
#include "Crossing.h"
#define BLACK RGB(0,0,0)
#define RED RGB(255,0,0)
#define GREEN RGB(0,200,0)
#define YELLOW RGB(255,255,0)
#define WHITE RGB(108,166,233)
#define GRAY RGB(128,128,128)
#define BLUE RGB(0,128,255)

void Crossing::Draw(CDC *pDC)
{
	CPen aPen(PS_SOLID, 3, GRAY);//������ı�
	CPen *oldPen = pDC->SelectObject(&aPen);

	//��ͬ��ɫ����
	switch (Cro_State)
	{
	case 1://��λ
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, GREEN);
		pDC->SelectObject(aPen);
		break;
	case 2://��λ
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, YELLOW);
		pDC->SelectObject(aPen);
		break;
	case 3://����ռ��
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, RED);
		pDC->SelectObject(aPen);
		break;
	default:
		break;
	}

	
	//������
	pDC->MoveTo(Cro_Pos);
	pDC->LineTo(Cro_Pos.x + 8,Cro_Pos.y);
	pDC->SelectObject(oldPen);


	//��ʾ��������
	CFont fn;
	fn.CreatePointFont(70, TEXT("΢���ź�"), pDC);
	CFont *oldfn = pDC->SelectObject(&fn);
	COLORREF clr1 = WHITE;
	CString str;
	str.Format(_T("%d"), Cro_Id);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(clr1);
	pDC->TextOut(Cro_Pos.x, Cro_Pos.y + 5, str);
	pDC->SetTextColor(WHITE);
	pDC->SelectObject(oldfn);


	
	



}

void Crossing::CreatCro(int Cro_Id, CPoint Cro_Pos, int Cro_State)
{
	this->Cro_Id = Cro_Id;
	this->Cro_Pos = Cro_Pos;
	this->Cro_State = Cro_State;



}
void  Crossing::SetCro(int state)
{
	Cro_State = state;
}

Crossing::Crossing()
{
}

Crossing::~Crossing()
{
}

