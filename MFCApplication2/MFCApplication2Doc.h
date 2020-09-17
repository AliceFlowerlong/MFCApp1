
// MFCApplication2Doc.h: CMFCApplication2Doc 类的接口
//



#pragma once
#pragma once
#include"Signal.h"
#include"Track.h"
#include"Crossing.h"
#include"InterLock.h"
#include"Train.h"

using namespace std;
//#include"Train.h"
//#include"MessageArea.h"
#define SigNum 11
#define TraNum 19
#define CroNum 6
#define LockingNum 6

class CMFCApplication2Doc : public CDocument
{
protected: // 仅从序列化创建
	CMFCApplication2Doc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication2Doc)

// 成员
public:
	Signal Sig[SigNum];
	Track Tra[TraNum];
	Crossing Cro[CroNum];
	InterLock Lock[LockingNum];

	Train Car;

	int LockingIndex  ;//第几条进路
	int TrackIndex;//行驶到第几条进路
	bool Init;
	bool bSigFlag;//始端信号机和终端信号机确认进路序号
	bool CroFlag;//道岔是否正确 true 为全部正确
	bool TraFlag;//轨道电路空闲
	bool SigFlag;//敌对信号关闭
	bool ComingFlag;//迎面进路关闭
	bool GuideFlag;//引导进路标志	
	

// 函数
public:
	void UpdataSig();
	void UpdataTra();
	
	void ButtonSigCheck(CString str1, CString str2);
	void OccupyCrossingCheck();
	void OccupyTrackCheck();//轨道电路占用/出清检查
	void  OccupySignalCheck();
	void ThreePointCheck();//三点检查
	int TraFront(Track tra);//轨道区段前方下一个轨道区段
	int TraBack(Track tra);//轨道区段后方上一个轨道区段

	

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMFCApplication2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
