#include "Interlocking.h"
#include "stdafx.h"


InterLocking::InterLocking()
{
}

InterLocking::~InterLocking()
{
}


#define WHITE RGB(108,166,233)



void InterLocking::PrintAllCro(CDC *pDC)
{
	//显示轨道电路名称
	CFont fn;
	fn.CreatePointFont(70, TEXT("微软雅黑"), pDC);
	CFont *oldfn = pDC->SelectObject(&fn);

	CString StrCode, Str;
	int data;
	COLORREF clr1;
	clr1 = WHITE;


	for (it = LockingCro.begin(); it != LockingCro.end(); it++)
	{
		data = *it;
		StrCode.Format(_T("%d"), data);
		Str = Str + StrCode;
	}

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(clr1);
	pDC->TextOut(200, 50, Str);
	pDC->SetTextColor(WHITE);
	pDC->SelectObject(oldfn);


}