// winPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winPlayer.h"
#include "winPlayerDlg.h"
#include "MyFloatWin.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinPlayerDlg dialog

CWinPlayerDlg::CWinPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinPlayerDlg::IDD, pParent)
    , m_pWndFloat(NULL)
{
	//{{AFX_DATA_INIT(CWinPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinPlayerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CWinPlayerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_BINDWND, OnBindwnd)
	ON_BN_CLICKED(IDC_PLAYOTHER, OnPlayother)
	ON_BN_CLICKED(IDC_MISC, OnMisc)
	ON_BN_CLICKED(IDC_FLOAT, OnFloat)
	ON_BN_CLICKED(IDC_BTN_DESTROYWIN, OnBtnDestroywin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinPlayerDlg message handlers

BOOL CWinPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinPlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWinPlayerDlg::OnOK() 
{
	//test play
    m_player.init();
    const char* pstrFile = "d:\\media\\china.mp4";
    bool bLoad = m_player.loadFromFile(pstrFile);
    ASSERT(bLoad);
}

void CWinPlayerDlg::OnPlay() 
{
	m_player.play();
	
}

void CWinPlayerDlg::OnStop() 
{
	m_player.stop();
	
}

void CWinPlayerDlg::OnBindwnd() 
{
    CWnd* pWndPlay = GetDlgItem(IDC_PLAYER);
    ASSERT(pWndPlay);
    m_player.setWindowHwnd((MY_WIN)pWndPlay->m_hWnd);	
    TRACE1("last err: %s\n", libvlc_errmsg());
}

void CWinPlayerDlg::OnPlayother() 
{
	const char* pstrFile = "d:\\media\\beautiful.flv";
    m_player.setMediaFromFile(pstrFile);
	
}

void CWinPlayerDlg::OnMisc() 
{
	libvlc_media_t* pmd = m_player.getMedia();
    ASSERT(pmd);
    
    libvlc_event_manager_t* peventMan = m_player.getEventManager();
    ASSERT(peventMan);

    float fps = m_player.getMediafps();
    ASSERT(fps >0.0);

    libvlc_time_t nMediaLen = m_player.getMediaLength();
    ASSERT(nMediaLen > 0);

    float pos = m_player.getMediaPosition();
	ASSERT(pos >0.0);

    libvlc_time_t nMediaTime = m_player.getMediaTime();
    ASSERT(nMediaTime > 0);

    float playRate = m_player.getPlayRate();
    libvlc_state_t playState = m_player.getPlayState();
    
    int nVol = m_player.getPlayVolume();
    ASSERT(nVol > 0);

    int nVideoOut = m_player.getVideoOuts();
    float fVideoScale = m_player.getVideoScale();

    unsigned int px,py;
    px=py=0;
    bool bGet = m_player.getVideoSize(0, &px, &py);
    ASSERT(bGet);
}


void CWinPlayerDlg::OnFloat() 
{
	if(!m_pWndFloat)
    {
        m_pWndFloat = new CSimpleWin;
        bool bOk = m_pWndFloat->Create(100, 100, 500, 400, NULL/*(MY_WIN)this->GetSafeHwnd()*/);
        ASSERT(bOk);
        m_pWndFloat->Show();
    }
    m_player.setWindowHwnd((MY_WIN)m_pWndFloat->m_hWnd);

}

void CWinPlayerDlg::OnBtnDestroywin() 
{
	if(m_pWndFloat)
    {
        m_pWndFloat->Destroy();
        delete m_pWndFloat;
        m_pWndFloat=NULL;
    }	
}
