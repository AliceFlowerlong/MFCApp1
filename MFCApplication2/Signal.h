#pragma once
#define BLACK RGB(0,0,0)
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define DARKGREEN RGB(0,139,0)//只有站内信号机定义了DARKGREEN，因为需要列车信号机按钮
#define SLATEBLUE RGB(72,118,255)//只有站内信号机定义了PURPLE，因为需要引导按钮
#define YELLOW RGB(255,255,0)
#define WHITE RGB(255,255,255)
#define GRAY RGB(128,128,128)
#define BLUE RGB(0,128,255)

#include"Track.h"
#include "stdafx.h"

//信号机类
class Signal
{
	//成员
public:
	CString Sig_ID;//信号机ID
	CPoint Sig_Pos;//信号机位置
	int Sig_Dire;//信号机方向
	int Sig_Type;//信号机类型 1进站 2出站 3调车
	int Sig_NF;//正反向
	int Sig_State;//信号机状态（表示灯的颜色）1.灭灯 2.红灯 3.双黄 4.黄灯 5.绿黄 6.绿灯 7.红白 8.蓝灯 
				//？为什么 L2L3L4是Sig的状态
				
	bool error;//灯丝断丝
	bool GreenError;//双灯位绿灯断丝
	bool YellowError;//双灯位黄灯断丝

	CRect rect1;//第一灯位
	CRect rect2;//第二灯位
	CRect rect3;
	CRect rect4;
	CRect rect5;
	CRect sig_point; //点击的是第几灯位


	//方法
public:
	void Draw(CDC *pDC);//绘制信号机
	void CreatSig(CString Sig_ID, CPoint Sig_Pos, int Sig_Dire, int Sig_Type, int Sig_NF, int Sig_State);
	Signal& operator=(Signal& s);
	void SetSig(int state);

public:
	Signal();
	~Signal();
};
