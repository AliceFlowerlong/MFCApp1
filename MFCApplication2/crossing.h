#pragma once


#include "stdafx.h"

class Crossing
{
public:
	Crossing();
	~Crossing();
//��Ա
public:
	int Cro_Id;
	CPoint Cro_Pos;
	int Cro_State;//1��λ 2 ��λ 3 ����
	int Cro_type;//1��Ʋ 2���� 3��Ʋ 4����


//����
public:
	void Draw(CDC *pDC);//�����źŻ�
	void CreatCro(int Cro_Id, CPoint Cro_Pos, int Cro_State);
	//Crossing& operator=(Crossing& s);
	void SetCro(int state);

private:

};


