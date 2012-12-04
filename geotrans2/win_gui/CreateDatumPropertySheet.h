#if !defined(AFX_CREATEDATUMPROPERTYSHEET_H__4FD23B74_72D4_4309_96F1_BB51C097DEFC__INCLUDED_)
#define AFX_CREATEDATUMPROPERTYSHEET_H__4FD23B74_72D4_4309_96F1_BB51C097DEFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateDatumPropertySheet.h : header file
//

class C3ParamPropertyPage;
class C7ParamPropertyPage;
class CMasterView;

/////////////////////////////////////////////////////////////////////////////
// CCreateDatumPropertySheet

class CCreateDatumPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CCreateDatumPropertySheet)

// Construction
public:
	CCreateDatumPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCreateDatumPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

  void setViews( CMasterView* _upperView, CMasterView* _lowerView );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateDatumPropertySheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCreateDatumPropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCreateDatumPropertySheet)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  C3ParamPropertyPage* _3ParamPropertyPage;
  C7ParamPropertyPage* _7ParamPropertyPage;
  CMasterView* upperView;
  CMasterView* lowerView;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEDATUMPROPERTYSHEET_H__4FD23B74_72D4_4309_96F1_BB51C097DEFC__INCLUDED_)
