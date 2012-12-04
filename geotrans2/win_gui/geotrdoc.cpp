// geotrdoc.cpp : implementation of the CGeotransDoc class
//

#include "stdafx.h"
#include "geotrans.h"
#include "geotrdoc.h"
#include "mastervw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeotransDoc

IMPLEMENT_DYNCREATE(CGeotransDoc, CDocument)

BEGIN_MESSAGE_MAP(CGeotransDoc, CDocument)
	//{{AFX_MSG_MAP(CGeotransDoc)
	ON_COMMAND(ID_EDIT_CLEARALL, OnEditClearall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARALL, OnUpdateEditClearall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeotransDoc construction/destruction

CGeotransDoc::CGeotransDoc()
{

}

CGeotransDoc::~CGeotransDoc()
{
}

BOOL CGeotransDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGeotransDoc serialization

void CGeotransDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGeotransDoc diagnostics

#ifdef _DEBUG
void CGeotransDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGeotransDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGeotransDoc commands

void CGeotransDoc::OnEditClearall()
{
	// TODO: Add your command handler code here
	UpdateAllViews(NULL);
}


void CGeotransDoc::OnUpdateEditClearall(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}
