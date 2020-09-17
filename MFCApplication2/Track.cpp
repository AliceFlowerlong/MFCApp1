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
	
	CPen aPen(PS_SOLID, 3, GRAY);//���ɵ�
	CPen bPen(PS_SOLID, 2, GRAY);//����Ե��
	CPen cPen(PS_SOLID, 2, GRAY);//�����������
	CPen dPen(PS_SOLID, 2, GREEN);//������
	CPen *oldPen = pDC->SelectObject(&aPen);

	//��ͬ��ɫ����
	switch (traState)
	{
	case 0://����
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, GRAY);
		pDC->SelectObject(&aPen);
		break;
	case 1://����
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, WHITE);
		pDC->SelectObject(&aPen);
		break;
	case 2://����ռ��
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, RED);
		pDC->SelectObject(&aPen);
		break;
	case 3://����ռ��
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3, RED);
		pDC->SelectObject(&aPen);
		break;
	case 4://����������
		aPen.DeleteObject();
		aPen.CreatePen(PS_SOLID, 3,GREEN);
		pDC->SelectObject(&aPen);
		break;
	default:
		break;
	}

	//��ʾ�����·����
	CFont fn;
	fn.CreatePointFont(70, TEXT("΢���ź�"), pDC);
	CFont *oldfn = pDC->SelectObject(&fn);
	CPoint CodePos;
	CodePos.x = (traStart.x + traEnd.x) / 2;
	CodePos.y = traStart.y + 10;
	CString StrCode;
	StrCode = TraID;
	COLORREF clr1;	
	clr1 = WHITE;
	

	//�����ֲ���ʾ���ƣ���������ʾ
	if (traType == 1 || traType == 2)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(clr1);
		pDC->TextOut(CodePos.x - 8, CodePos.y, StrCode);
		pDC->SetTextColor(WHITE);
		pDC->SelectObject(oldfn);
	}
	

	

	//
	
	//�����·��ͬ���ͻ�ͼ
	//1 ��ȥ�ӽ� 2��Ե�ڹɵ� 3.˫������ 4.�������� 5.�������Ӳ��� 6.����ڵ�
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
		//����Ե��
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