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
	int LockCroNum; //一条进路中需要检查道岔的数目
	int LockTraNum;//一条进路中需要检查轨道电路的数目
	int LockSigNum;//一条进路中需要检查敌对信号的数目
	CString StartSigID, EndSigID; //进路中始端信号机与终端信号机ID
	int Lock_SigState; //进路匹配后，始端信号机开放颜色

	vector<int> Locking_Cro;//一条进路中需要检查所有的道岔储存表
	vector<int> Locking_CroState;//一条进路中需要检查所有的道岔状态储存表
	vector<CString> Locking_Sig;//一条进路中需要检查所有的敌对信号储存表
	vector<CString> Locking_Tra;//一条进路中需要检查所有的轨道电路储存表

	vector<int>::iterator it;//vetcor遍历迭代器

public:
	void PrintAllCro(CDC *pDC);

};
