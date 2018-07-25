// winPlayerDlg.h : header file
//

#if !defined(AFX_WINPLAYERDLG_H__188455BE_843C_49EA_8C65_790030BDCD4B__INCLUDED_)
#define AFX_WINPLAYERDLG_H__188455BE_843C_49EA_8C65_790030BDCD4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\MyPlayer.h"
#include "..\\SimpleWin.h"

/////////////////////////////////////////////////////////////////////////////
// CWinPlayerDlg dialog

class CWinPlayerDlg : public CDialog
{
// Construction
public:
	CWinPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinPlayerDlg)
	enum { IDD = IDD_WINPLAYER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnBindwnd();
	afx_msg void OnPlayother();
	afx_msg void OnMisc();
	afx_msg void OnFloat();
	afx_msg void OnBtnDestroywin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    CMyPlayer m_player;
    CSimpleWin* m_pWndFloat;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINPLAYERDLG_H__188455BE_843C_49EA_8C65_790030BDCD4B__INCLUDED_)
