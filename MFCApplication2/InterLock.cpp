#include "stdafx.h"
#include "InterLock.h"



InterLock::InterLock()
{}

InterLock::~InterLock()
{}

void InterLock::PrintAllCro(CDC *pDC)
{
	//��ʾ�����·����
	CFont fn;
	fn.CreatePointFont(70, TEXT("΢���ź�"), pDC);
	CFont *oldfn = pDC->SelectObject(&fn);

	CString StrCode, Str1,Str2;
	int data;
	COLORREF clr1;
	clr1 = WHITE;

	//��·������λ�ú�״̬
	for (it = Locking_Cro.begin(); it != Locking_Cro.end(); it++)
	{
		data = *it;
		StrCode.Format(_T("..%d"), data);
		Str1 = Str1 + StrCode;
	}

	for (it = Locking_CroState.begin(); it != Locking_CroState.end(); it++)
	{
		data = *it;
		StrCode.Format(_T("..%d"), data);
		Str2 = Str2 + StrCode;
	}

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(clr1);
	pDC->TextOut(200, 50, Str1);
	pDC->TextOut(200, 70, Str2);
	pDC->SetTextColor(WHITE);
	pDC->SelectObject(oldfn);


}


