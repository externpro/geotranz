// progress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Progress dialog

class Progress : public CDialog
{
// Construction
public:
	Progress(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(Progress)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(Progress)
	afx_msg void OnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
