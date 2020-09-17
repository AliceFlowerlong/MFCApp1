#pragma once


#include "stdafx.h"

class Crossing
{
public:
	Crossing();
	~Crossing();
//成员
public:
	int Cro_Id;
	CPoint Cro_Pos;
	int Cro_State;//1定位 2 反位 3 故障
	int Cro_type;//1上撇 2上捺 3下撇 4下捺


//函数
public:
	void Draw(CDC *pDC);//绘制信号机
	void CreatCro(int Cro_Id, CPoint Cro_Pos, int Cro_State);
	//Crossing& operator=(Crossing& s);
	void SetCro(int state);

private:

};


