
// MFCApplication2Doc.cpp: CMFCApplication2Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication2Doc

IMPLEMENT_DYNCREATE(CMFCApplication2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication2Doc, CDocument)
END_MESSAGE_MAP()


// CMFCApplication2Doc 构造/析构

CMFCApplication2Doc::CMFCApplication2Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	Init = true;//初始化标志

	CString FileName;
	FileName = _T("data\\SignalData1.txt");
	CStdioFile file;
	CFileException e;

	//初始化各个标识符
	CroFlag = false;
	TraFlag = false;
	SigFlag = false;
	bSigFlag = false;
	GuideFlag = false;
	ComingFlag = true;
	LockingIndex = 0;
	TrackIndex = 0;

	//读数据
	if (file.Open(FileName, CFile::typeText | CFile::modeReadWrite), &e)
	{
		//初始化信号机数据
		file.SeekToBegin();
		CString str;
		int idx;
		for (int j = 0; j < SigNum; j++)
		{
			file.ReadString(str);
			CString data[6];
			for (int i = 0; i < 6; i++)
			{
				idx = str.Find(_T("	"), 0);
				if (idx == -1)
				{
					data[i] = str;
				}
				else
				{
					data[i] = str.Left(idx);
				}
				str.Delete(0, idx + 1);
			}
			Sig[j].Sig_ID = data[0];
			Sig[j].Sig_Type = _ttoi(data[1]);
			Sig[j].Sig_Dire = _ttoi(data[2]);
			Sig[j].Sig_NF = _ttoi(data[3]);
			Sig[j].Sig_Pos.x = _ttoi(data[4]);
			Sig[j].Sig_Pos.y = _ttoi(data[5]);
			Sig[j].Sig_State = 2;
			Sig[j].error = false;
			Sig[j].GreenError = false;
			Sig[j].YellowError = false;
		}
		file.Close();
	}
	
	//初始化轨道电路
	FileName = _T("data\\TrackData1.txt");
	CStdioFile file2;
	if (file2.Open(FileName, CFile::typeText | CFile::modeReadWrite), &e)
	{
		file2.SeekToBegin();
		CString str;
		int idx;
		for (int j = 0; j < TraNum; j++)
		{
			file2.ReadString(str);
			CString data[6];
			for (int i = 0; i < 6; i++)
			{
				idx = str.Find(_T("	"), 0);
				if (idx == -1)
				{
					data[i] = str;
				}
				else
				{
					data[i] = str.Left(idx);
				}
				str.Delete(0, idx + 1);
			}
			Tra[j].TraID = data[0];
			Tra[j].traStart.x = _ttoi(data[1]);
			Tra[j].traStart.y = _ttoi(data[3]);
			Tra[j].traEnd.x = _ttoi(data[2]);
			Tra[j].traEnd.y = _ttoi(data[5]);
			Tra[j].traType = _ttoi(data[4]);
			Tra[j].traState = 0;
			Tra[j].traCode = HU;
			Tra[j].error = false;
			Tra[j].lock = false;
			Tra[j].lock1 = false;
			Tra[j].lock2 = false;
			Tra[j].Intrusion = false;
			Tra[j].DefectiveShunting = false;
			Tra[j].flag = false;
		}

		file2.Close();
	}

	//初始化道岔

	FileName = _T("data\\CrossingData1.txt");
	CStdioFile file3;
	if (file3.Open(FileName, CFile::typeText | CFile::modeReadWrite), &e)
	{
		file3.SeekToBegin();
		CString str;
		int idx;
		for (int j = 0; j < CroNum; j++)
		{
			file3.ReadString(str);
			CString data[5];
			for (int i = 0; i < 5; i++)
			{
				idx = str.Find(_T("	"), 0);
				if (idx == -1)
				{
					data[i] = str;
				}
				else
				{
					data[i] = str.Left(idx);
				}
				str.Delete(0, idx + 1);
			}
			Cro[j].Cro_Id = _ttoi(data[0]);
			Cro[j].Cro_Pos.x = _ttoi(data[1]);
			Cro[j].Cro_Pos.y = _ttoi(data[2]);
			Cro[j].Cro_State = _ttoi(data[3]);
			Cro[j].Cro_type = _ttoi(data[4]);
		
		}

		file3.Close();
	}

	//联锁表信号机初始化
	FileName = _T("data\\LockSigData.txt");
	CStdioFile file4;
	if (file4.Open(FileName, CFile::typeText | CFile::modeReadWrite), &e)
	{
		file4.SeekToBegin();
		CString str;
		int idx;
		for (int j = 0; j < LockingNum; j++)
		{
			file4.ReadString(str);
			CString data[3];
			for (int i = 0; i < 3; i++)
			{
				idx = str.Find(_T("	"), 0);
				if (idx == -1)
				{
					data[i] = str;
				}
				else
				{
					data[i] = str.Left(idx);
				}
				str.Delete(0, idx + 1);
			}
			Lock[j].StartSigID = data[0];
			Lock[j].EndSigID = data[1];
			Lock[j].Lock_SigState = _ttoi(data[2]);
		}
		file4.Close();
	}
	
	//联锁表道岔初始化
	FileName = _T("data\\LockCroData.txt");
	CStdioFile file5;
	if (file5.Open(FileName, CFile::typeText | CFile::modeReadWrite), &e)
	{
		file5.SeekToBegin();
		CString str, data;
		int idx, LockingCroNum, ndata;
		//

		for (int j = 0; j < LockingNum; j++)
		{
			file5.ReadString(str);

			idx = str.Find(_T("	"), 0);
			if (idx == -1)
			{
				data = str;
			}
			else
			{
				data = str.Left(idx);
			}
			str.Delete(0, idx + 1);

			LockingCroNum = _ttoi(data);
			Lock[j].LockCroNum = LockingCroNum;

			for (int i = 0; i < 2 * LockingCroNum ; i++)
			{
				idx = str.Find(_T("	"), 0);
				if (idx == -1)
				{
					data = str;
				}
				else
				{
					data = str.Left(idx);
				}
				str.Delete(0, idx + 1);
				ndata = _ttoi(data);
				if (i % 2 == 0)
				{
					Lock[j].Locking_Cro.push_back(ndata);
				}
				else
				{
					Lock[j].Locking_CroState.push_back(ndata);
				}				
			}
		}

		file5.Close();
	}

	//联锁表轨道电路初始化
	FileName = _T("data\\LockTraData.txt");
	CStdioFile file6;
	if (file6.Open(FileName, CFile::typeText | CFile::modeReadWrite), &e)
	{
		file6.SeekToBegin();
		CString str, data;
		int idx, Num;
		//
		for (int j = 0; j < LockingNum; j++)
		{
			file6.ReadString(str);

			idx = str.Find(_T("	"), 0);
			if (idx == -1)
			{
				data = str;
			}
			else
			{
				data = str.Left(idx);
			}
			str.Delete(0, idx + 1);

			Num = _ttoi(data);
			Lock[j].LockTraNum = Num;

			for (int i = 0; i < Num; i++)
			{
				idx = str.Find(_T("	"), 0);
				if (idx == -1)
				{
					data = str;
				}
				else
				{
					data = str.Left(idx);
				}
				str.Delete(0, idx + 1);
				Lock[j].Locking_Tra.push_back(data);

			}
		}
		file6.Close();
	}

	//联锁表敌对信号初始化
	FileName = _T("data\\LockAntiSigData.txt");
	CStdioFile file7;
	if (file7.Open(FileName, CFile::typeText | CFile::modeReadWrite), &e)
	{
		file7.SeekToBegin();
		CString str, data;
		int idx, Num;
		//
		for (int j = 0; j < LockingNum; j++)
		{
			file7.ReadString(str);

			idx = str.Find(_T("	"), 0);
			if (idx == -1)
			{
				data = str;
			}
			else
			{
				data = str.Left(idx);
			}
			str.Delete(0, idx + 1);

			Num = _ttoi(data);
			Lock[j].LockSigNum = Num;

			for (int i = 0; i < Num; i++)
			{
				idx = str.Find(_T("	"), 0);
				if (idx == -1)
				{
					data = str;
				}
				else
				{
					data = str.Left(idx);
				}
				str.Delete(0, idx + 1);				
				Lock[j].Locking_Sig.push_back(data);
			}
		}
		file7.Close();
	}
	   
}

CMFCApplication2Doc::~CMFCApplication2Doc()
{

}

BOOL CMFCApplication2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

void CMFCApplication2Doc::ButtonSigCheck(CString str1, CString str2)
{
	bSigFlag = false;

	for (int i = 0; i < LockingNum; i++)
	{
		if (str1 == Lock[i].StartSigID \
			&& str2 == Lock[i].EndSigID)
		{
			bSigFlag = true;
			LockingIndex = i;		
			continue;
		}
	}

}

void  CMFCApplication2Doc::OccupyCrossingCheck()
{
	CroFlag = false;
	int CheckNum = 0;
	if (LockingIndex < 0 || LockingIndex > LockingNum)//防止下标超界
	{
		return;
	}	
	else
	{
		for (int i = 0; i < Lock[LockingIndex].LockCroNum; i++)
		{
			
			for (int j = 0; j < CroNum; j++)
			{
				if (Lock[LockingIndex].Locking_Cro[i]== Cro[j].Cro_Id)
				{
					Cro[j].Cro_State = Lock[LockingIndex].Locking_CroState[i];
					CheckNum++;
				}
			}
		}
	}
	if (CheckNum == Lock[LockingIndex].LockCroNum)
	{
		CroFlag = true;
	}

}





void CMFCApplication2Doc::OccupyTrackCheck()
{
	TraFlag = false;
	int CheckNum = 0;
	if (LockingIndex < 0 || LockingIndex > LockingNum) 
	{
		return ;
	}
	else
	{
		for (int i = 0; i < Lock[LockingIndex].LockTraNum; i++)
		{
			for (int j = 0; j < TraNum; j++)
			{
				if (Tra[j].TraID == Lock[LockingIndex].Locking_Tra[i] \
					&&( Tra[j].traState == 0 || Tra[j].traState == 1))
				{
					CheckNum++;
				}
				
			}
		}
	}

	if (CheckNum == Lock[LockingIndex].LockTraNum)
	{
		TraFlag = true;
	}

}

void CMFCApplication2Doc::OccupySignalCheck()
{
	SigFlag = false;
	int CheckNum = 0;
	if (LockingIndex < 0 || LockingIndex > LockingNum)
	{
		return;
	}
	else
	{
		for (int i = 0; i < Lock[LockingIndex].LockSigNum; i++)
		{
			for (int j = 0; j < SigNum; j++)
			{
				if (Sig[j].Sig_ID == Lock[LockingIndex].Locking_Sig[i] \
					&& Sig[j].Sig_State == 2)
				{
					CheckNum++;
				}

			}
		}
	}
	if (CheckNum == Lock[LockingIndex].LockSigNum)
	{
		SigFlag = true;
	}
}


void CMFCApplication2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}
void CMFCApplication2Doc::ThreePointCheck()
{
	int frontindex;
	if (TrackIndex <= 0 || TrackIndex > Lock[LockingIndex].LockTraNum)
	{
		return;
	}
	if (TrackIndex == 1)
	{
		for (int j = 0; j < TraNum; j++)
		{
			if (Tra[j].TraID == Lock[LockingIndex].Locking_Tra[TrackIndex])//TrackIndex是占用的第几条股道，和序号0开始编号相差1 
			{
				Tra[j].lock1 = false;//压入时，1LJ解锁

			}
		}
	}
	if (TrackIndex > 1 && TrackIndex <= Lock[LockingIndex].LockTraNum)
	{
		for (int j = 0; j < TraNum; j++)
		{
			if (Tra[j].TraID == Lock[LockingIndex].Locking_Tra[TrackIndex - 1])
			{

				Tra[j].lock1 = false;//
				frontindex = TraFront(Tra[j]);
				Tra[frontindex].lock2 = false;

				if (Tra[frontindex].lock1 = false || Tra[frontindex].lock2 == false)
				{
					Tra[frontindex].lock = false;
					
					Tra[frontindex].traState = 0;
				}
			}
		}
	}
	if (TrackIndex == Lock[LockingIndex].LockTraNum + 1)
	{
		for (int j = 0; j < TraNum; j++)
		{
			if (Tra[j].TraID == Lock[LockingIndex].Locking_Tra[TrackIndex - 1])
			{

				frontindex = TraFront(Tra[j]);
				Tra[frontindex].lock2 = false;
				if (Tra[frontindex].lock1 = false || Tra[frontindex].lock2 == false)
				{
					Tra[frontindex].lock = false;					
					Tra[frontindex].traState = 0;					
				}
			}
		}
	}
}

int CMFCApplication2Doc::TraFront(Track tra)
{

	for (int j = 0; j < TraNum; j++)
	{
		if (Tra[j].TraID == Lock[LockingIndex].Locking_Tra[TrackIndex - 2])
		{
			return j;
		}
	}
}
int CMFCApplication2Doc::TraBack(Track tra)
{

	for (int j = 0; j < TraNum; j++)
	{
		if (Tra[j].TraID == Lock[LockingIndex].Locking_Tra[TrackIndex])
		{
			return j;
		}
	}
}

void CMFCApplication2Doc::UpdataSig() {}
void CMFCApplication2Doc::UpdataTra() {}




#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMFCApplication2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMFCApplication2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMFCApplication2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication2Doc 诊断

#ifdef _DEBUG
void CMFCApplication2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication2Doc 命令
