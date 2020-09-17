#pragma once
#define BLACK RGB(0,0,0)
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define DARKGREEN RGB(0,139,0)//ֻ��վ���źŻ�������DARKGREEN����Ϊ��Ҫ�г��źŻ���ť
#define SLATEBLUE RGB(72,118,255)//ֻ��վ���źŻ�������PURPLE����Ϊ��Ҫ������ť
#define YELLOW RGB(255,255,0)
#define WHITE RGB(255,255,255)
#define GRAY RGB(128,128,128)
#define BLUE RGB(0,128,255)

#include"Track.h"
#include "stdafx.h"

//�źŻ���
class Signal
{
	//��Ա
public:
	CString Sig_ID;//�źŻ�ID
	CPoint Sig_Pos;//�źŻ�λ��
	int Sig_Dire;//�źŻ�����
	int Sig_Type;//�źŻ����� 1��վ 2��վ 3����
	int Sig_NF;//������
	int Sig_State;//�źŻ�״̬����ʾ�Ƶ���ɫ��1.��� 2.��� 3.˫�� 4.�Ƶ� 5.�̻� 6.�̵� 7.��� 8.���� 
				//��Ϊʲô L2L3L4��Sig��״̬
				
	bool error;//��˿��˿
	bool GreenError;//˫��λ�̵ƶ�˿
	bool YellowError;//˫��λ�Ƶƶ�˿

	CRect rect1;//��һ��λ
	CRect rect2;//�ڶ���λ
	CRect rect3;
	CRect rect4;
	CRect rect5;
	CRect sig_point; //������ǵڼ���λ


	//����
public:
	void Draw(CDC *pDC);//�����źŻ�
	void CreatSig(CString Sig_ID, CPoint Sig_Pos, int Sig_Dire, int Sig_Type, int Sig_NF, int Sig_State);
	Signal& operator=(Signal& s);
	void SetSig(int state);

public:
	Signal();
	~Signal();
};
