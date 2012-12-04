// geotrvw.cpp : implementation of the CGeotransView class
//

#include "stdafx.h"
#include "geotrans.h"
#include "geotrdoc.h"
#include "geotrvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeotransView

IMPLEMENT_DYNCREATE(CGeotransView, CFormView)

BEGIN_MESSAGE_MAP(CGeotransView, CFormView)
//{{AFX_MSG_MAP(CGeotransView)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeotransView construction/destruction

CGeotransView::CGeotransView()
: CFormView(CGeotransView::IDD)
{
  //{{AFX_DATA_INIT(CGeotransView)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  // TODO: add construction code here
}

CGeotransView::~CGeotransView()
{
}

void CGeotransView::DoDataExchange(CDataExchange* pDX)
{
  CFormView::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CGeotransView)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGeotransView diagnostics

#ifdef _DEBUG
void CGeotransView::AssertValid() const
{
  CFormView::AssertValid();
}

void CGeotransView::Dump(CDumpContext& dc) const
{
  CFormView::Dump(dc);
}

CGeotransDoc* CGeotransView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeotransDoc)));
  return (CGeotransDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGeotransView message handlers
