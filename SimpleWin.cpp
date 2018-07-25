//#include "stdafx.h"
#include "SimpleWin.h"

#ifdef _WIN32///////////////////////////////
#include <windows.h>
#else///////////////////////////////////////
// for linux, use libxcb to create window
#include <xcb/xcb.h>
#endif//////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSimpleWin::CSimpleWin()
    : m_hWnd(0)
{
}

CSimpleWin::~CSimpleWin()
{
}

#ifdef _WIN32//////////////////////////////////////
// windows 窗口过程
LONG WINAPI SimpleWndProc(HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam) 
{ 
    switch(msg) 
    { 
    case WM_DESTROY:         
        //PostQuitMessage(0); 
        return 0; 
    case WM_PAINT:
      //ValidateRect(hWnd, NULL); 
      return 0; 
    case WM_CLOSE:
      return 0;
  } 
  return DefWindowProc(hWnd , msg , wParam , lParam); 
} 

const char g_wcName[32]="he_simplewin";

static WNDCLASSEX g_wc = { 
    sizeof(WNDCLASSEX),
        CS_CLASSDC, 
        SimpleWndProc, 
        0, 
        0, 
        GetModuleHandle(NULL), 
        NULL, 
        NULL, 
        (HBRUSH)GetStockObject(BLACK_BRUSH), 
        NULL, 
        g_wcName, 
        NULL
}; 

// 用来修改窗口属性
bool HeModifyStyle(HWND hWnd, 
                   int nStyleIndex,
                   DWORD dwRemove, 
                   DWORD dwAdd)
{
    DWORD dwStyle = GetWindowLong(hWnd, nStyleIndex);
    DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
    if (dwStyle == dwNewStyle)
        return false;    
    SetWindowLong(hWnd, nStyleIndex, dwNewStyle);
    return true;
}
#else/////////////////////////////////////////
// for x window
static xcb_connection_t* g_xcbConn=NULL;

#endif///////////////////////////////////////


bool CSimpleWin::Create( int left, int right, int width, int height, MY_WIN hParent/*=0*/ )
{
#ifdef _WIN32/////////////////////////////////////////
    //for windows
    RegisterClassEx(&g_wc);
    HWND hWnd = CreateWindowEx( 
                    0,
                    g_wcName, 
                    "", 
                    /*WS_VISIBLE*/0, 
                    left, right, width, height, 
                    (HWND)hParent, 
                    NULL, 
                    g_wc.hInstance, 
                    NULL);
    HeModifyStyle(hWnd, GWL_STYLE, WS_CAPTION|WS_BORDER, 0);
    m_hWnd = (MY_WIN)hWnd;
    return (m_hWnd!=0);
#else////////////////////////////////////////////////
    //for linux    
    xcb_screen_t     *screen;
    xcb_window_t      win;
    
    g_xcbConn = xcb_connect (NULL, NULL);    
    /* Get the first screen */
    screen = xcb_setup_roots_iterator(xcb_get_setup(g_xcbConn)).data;
    win = xcb_generate_id(g_xcbConn);
    
    if(!hParent)
    {
        hParent=(MY_WIN)screen->root;
    }
    //窗口默认属性
    uint32_t mask = XCB_CW_BACK_PIXEL |XCB_CW_BORDER_PIXEL/*|XCB_CW_EVENT_MASK*/;
    uint32_t values[8];
    values[0] = screen->black_pixel;
    values[1] = screen->black_pixel;
    values[2] = 0/*XCB_EVENT_MASK_EXPOSURE*/;

    /* Create the window */
    xcb_create_window(g_xcbConn,       /* Connection          */
        XCB_COPY_FROM_PARENT,          /* depth (same as root)*/
        win,                           /* window Id           */
        (unsigned int)hParent,         /* parent window       */
        left, right,                   /* x, y                */
        width, height,                 /* width, height       */
        2,                             /* border_width        */
        XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
        screen->root_visual,           /* visual              */
        mask, values);
    
    m_hWnd=(MY_WIN)win;
    return (m_hWnd!=0);
#endif/////////////////////////////////////////////////
}

void CSimpleWin::Show()
{
#ifdef _WIN32///////////////////////////
    HWND hWnd = (HWND)m_hWnd;
    //ShowWindow(hWnd, SW_SHOW);
#ifdef _DEBUG
    SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
#else
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
#endif    
#else///////////////////////////////////
    xcb_window_t win=(xcb_window_t)m_hWnd;
    xcb_map_window(g_xcbConn, win);
    xcb_flush(g_xcbConn);
#endif//////////////////////////////////
}

void CSimpleWin::Hide()
{
#ifdef _WIN32///////////////////////////
    HWND hWnd = (HWND)m_hWnd;
    ShowWindow(hWnd, SW_HIDE);
#else///////////////////////////////////
    xcb_window_t win=(xcb_window_t)m_hWnd;
    xcb_unmap_window(g_xcbConn, win);
#endif//////////////////////////////////
}

void CSimpleWin::Destroy()
{
#ifdef _WIN32/////////////////////////////////
    HWND hWnd = (HWND)m_hWnd;
    if(IsWindow(hWnd))
    {
        DestroyWindow(hWnd);
        UnregisterClass(g_wcName, g_wc.hInstance);
    }
    m_hWnd=0;
#else/////////////////////////////////////////
    if(g_xcbConn){
        xcb_disconnect(g_xcbConn);
        g_xcbConn=NULL;  
    }
    m_hWnd=0;
#endif////////////////////////////////////////
}
