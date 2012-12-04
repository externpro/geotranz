// geotrvw.h : interface of the CGeotransView class
//
/////////////////////////////////////////////////////////////////////////////

class CGeotransView : public CFormView
{

protected: // create from serialization only
	CGeotransView();
	DECLARE_DYNCREATE(CGeotransView)

public:
	//{{AFX_DATA(CGeotransView)
	enum{ IDD = IDD_GEOTRANS_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CGeotransDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CGeotransView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Generated message map functions
protected:
	//{{AFX_MSG(CGeotransView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in geotrvw.cpp
inline CGeotransDoc* CGeotransView::GetDocument()
   { return (CGeotransDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
