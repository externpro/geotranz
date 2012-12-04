#if !defined(AFX_DELDATUMVW_H__3DA70A42_27DD_11D4_BCEB_0000E20FD521__INCLUDED_)
#define AFX_DELDATUMVW_H__3DA70A42_27DD_11D4_BCEB_0000E20FD521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// deldatumvw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeleteDatumView dialog

class CDeleteDatumView : public CDialog
{
// Construction
public:
	CDeleteDatumView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
private:
	//{{AFX_DATA(CDeleteDatumView)
	enum { IDD = IDD_DELETE_DATUM_DIALOG };
	int		m_datum_index;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteDatumView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
   void FillListBox();

protected:
   BOOL OnInitDialog(void);

	// Generated message map functions
	//{{AFX_MSG(CDeleteDatumView)
	afx_msg void OnSelchangeDeleteDatumCombobox();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELDATUMVW_H__3DA70A42_27DD_11D4_BCEB_0000E20FD521__INCLUDED_)
