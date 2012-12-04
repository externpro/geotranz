// geotrdoc.h : interface of the CGeotransDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CGeotransDoc : public CDocument
{

protected: // create from serialization only
	CGeotransDoc();
	DECLARE_DYNCREATE(CGeotransDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
	virtual ~CGeotransDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CGeotransDoc)
	afx_msg void OnEditClearall();
	afx_msg void OnUpdateEditClearall(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
