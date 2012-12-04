#if !defined(AFX_ELETELLIPVW_H__3DA70A41_27DD_11D4_BCEB_0000E20FD521__INCLUDED_)
#define AFX_ELETELLIPVW_H__3DA70A41_27DD_11D4_BCEB_0000E20FD521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// eletellipvw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeleteEllipsoid dialog

class CDeleteEllipsoid : public CDialog
{
// Construction
public:
	CDeleteEllipsoid(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
private:
	//{{AFX_DATA(CDeleteEllipsoid)
	enum { IDD = IDD_DELETE_ELLIPSOID_DIALOG };
	int		m_ellipsoid_index;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteEllipsoid)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void FillListBox();

protected:
    BOOL OnInitDialog(void);

	// Generated message map functions
	//{{AFX_MSG(CDeleteEllipsoid)
	virtual void OnOK();
	afx_msg void OnSelchangeDeleteEllipsoidCombobox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELETELLIPVW_H__3DA70A41_27DD_11D4_BCEB_0000E20FD521__INCLUDED_)
