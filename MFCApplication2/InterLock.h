#pragma once
#include "vector"
#include"Signal.h"
#include"Track.h"
#include"Crossing.h"
#include "stdafx.h"
using namespace std;

#define WHITE RGB(255,255,255)

class InterLock
{

public:
	InterLock() ;
	~InterLock();

public:
	int LockCroNum; //һ����·����Ҫ���������Ŀ
	int LockTraNum;//һ����·����Ҫ�������·����Ŀ
	int LockSigNum;//һ����·����Ҫ���ж��źŵ���Ŀ
	CString StartSigID, EndSigID; //��·��ʼ���źŻ����ն��źŻ�ID
	int Lock_SigState; //��·ƥ���ʼ���źŻ�������ɫ

	vector<int> Locking_Cro;//һ����·����Ҫ������еĵ������
	vector<int> Locking_CroState;//һ����·����Ҫ������еĵ���״̬�����
	vector<CString> Locking_Sig;//һ����·����Ҫ������еĵж��źŴ����
	vector<CString> Locking_Tra;//һ����·����Ҫ������еĹ����·�����

	vector<int>::iterator it;//vetcor����������

public:
	void PrintAllCro(CDC *pDC);

};
