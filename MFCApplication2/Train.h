#pragma once
#pragma once
#define BLACK RGB(0,0,0)
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define YELLOW RGB(255,255,0)
#define WHITE RGB(255,255,255)
#define GRAY RGB(128,128,128)
#define BLUE RGB(0,128,255)
class Train
{
public:
	CPoint TraStart;//起始坐标
	CPoint TraEnd;//终止坐标

	bool flag;//侧线接车标志
	bool flag2;//侧线发车标志
public:
	Train();
	~Train();
public:
	void TrainGo(int dis);
	void Draw(CDC *pDC);
};


