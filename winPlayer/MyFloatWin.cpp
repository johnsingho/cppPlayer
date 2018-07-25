// MyFloatWin.cpp : implementation file
//

#include "stdafx.h"
#include "winPlayer.h"
#include "MyFloatWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFloatWin

CMyFloatWin::CMyFloatWin()
{
}

CMyFloatWin::~CMyFloatWin()
{
}


BEGIN_MESSAGE_MAP(CMyFloatWin, CWnd)
	//{{AFX_MSG_MAP(CMyFloatWin)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyFloatWin message handlers
// 
// BOOL CMyFloatWin::PreTranslateAppMessage(MSG* pMsg)
// {   
//     // If we get a keyboard or mouse message, hide the splash screen.
//     if (pMsg->message == WM_KEYDOWN ||
//         pMsg->message == WM_SYSKEYDOWN ||
//         pMsg->message == WM_LBUTTONDOWN ||
//         pMsg->message == WM_RBUTTONDOWN ||
//         pMsg->message == WM_MBUTTONDOWN ||
//         pMsg->message == WM_NCLBUTTONDOWN ||
//         pMsg->message == WM_NCRBUTTONDOWN ||
//         pMsg->message == WM_NCMBUTTONDOWN)
//         {
//             TRACE("special key down\n");
//             return TRUE;	// message handled here
//         }
//         
//         return FALSE;	// message not handled
// }


BOOL CMyFloatWin::Create(CWnd* pParentWnd)
{
    return CreateEx(0,
        AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH)),
        NULL, WS_POPUP|WS_VISIBLE|WS_CAPTION, 100, 100, 400, 300, pParentWnd->GetSafeHwnd(), NULL);
}

int CMyFloatWin::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // Center the window.
    //CenterWindow();
    MoveWindow(CRect(100,100,500,400));

    return 0;
}


