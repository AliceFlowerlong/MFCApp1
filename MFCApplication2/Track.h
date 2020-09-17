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
	//��Ա
public:
	CString TraID;
	CPoint traStart;
	CPoint traEnd;
	
	int traType;
	//1 ��ȥ�ӽ� 2��Ե�ڹɵ� 3.˫������ 4. ��������

	int traState;// 0.���� 1.���� 2.����ռ�� 3.����ռ��
	int traCode;
	bool error;
	bool Intrusion;
	bool DefectiveShunting;

	bool lock;//����ռ����
	bool lock1;
	bool lock2;//�������־

	bool flag;
	//����:
	void Draw(CDC* pDC);
	void setCode(int Code);
	void createTra(CString TraID, CPoint traStart, CPoint traEnd, int traType, int traState, int TraCode);
	Track& operator=(Track &T);
	void suobi(Track t);
public:
	Track();
	~Track();

};
