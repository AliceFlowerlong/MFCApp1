#pragma once


#define HU 0
#define HB 1
#define U 2
#define LU 3
#define L 4
#define L2 5
#define L3 6
#define L4 7
#define L5 8
#define B 9
#define UU 10
#define U2 11
#define JC 12
#define H 13
#define NONE 14

class Track
{
	//成员
public:
	CString TraID;
	CPoint traStart;
	CPoint traEnd;
	
	int traType;
	//1 离去接近 2绝缘节股道 3.双动道岔 4. 单动道岔

	int traState;// 0.空闲 1.锁闭 2.正常占用 3.故障占用
	int traCode;
	bool error;
	bool Intrusion;
	bool DefectiveShunting;

	bool lock;//区段占用锁
	bool lock1;
	bool lock2;//三点检查标志

	bool flag;
	//方法:
	void Draw(CDC* pDC);
	void setCode(int Code);
	void createTra(CString TraID, CPoint traStart, CPoint traEnd, int traType, int traState, int TraCode);
	Track& operator=(Track &T);
	void suobi(Track t);
public:
	Track();
	~Track();

};
