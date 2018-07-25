#if !defined(AFX_MYFLOATWIN_H__EF8AD7AC_1A66_4A67_BE7D_ED19D1AC366E__INCLUDED_)
#define AFX_MYFLOATWIN_H__EF8AD7AC_1A66_4A67_BE7D_ED19D1AC366E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFloatWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyFloatWin window

class CMyFloatWin : public CWnd
{
// Construction
public:
	CMyFloatWin();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFloatWin)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyFloatWin();
    BOOL Create(CWnd* pParentWnd);
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyFloatWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFLOATWIN_H__EF8AD7AC_1A66_4A67_BE7D_ED19D1AC366E__INCLUDED_)
