#if !defined(AFX_SIMPLEWIN_H__712CBA06_981D_4F33_9923_5854C0CB0087__INCLUDED_)
#define AFX_SIMPLEWIN_H__712CBA06_981D_4F33_9923_5854C0CB0087__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//这个用作窗口句柄
typedef void* MY_WIN;

// 简单窗口，用于显示视频
//
class CSimpleWin  
{
public:
	CSimpleWin();
    virtual ~CSimpleWin();

    bool Create(int left, int right, int width, int height, MY_WIN hParent=0);
    void Show();
    void Hide();
    void Destroy();

    inline MY_WIN getHwnd(){ return m_hWnd;}
public:
    MY_WIN m_hWnd;
};




#endif // !defined(AFX_SIMPLEWIN_H__712CBA06_981D_4F33_9923_5854C0CB0087__INCLUDED_)
