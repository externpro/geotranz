// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "geotrans.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorButton

CColorButton::CColorButton()
{
  button_color =::GetSysColor( COLOR_3DFACE );
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers

void CColorButton::SetColor( COLORREF color )
{
  button_color = color;
  c_brush.DeleteObject();
  c_brush.CreateSolidBrush( button_color );
}


// Draw the button in the given color
void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
  CDC* pDC   = CDC::FromHandle( lpDrawItemStruct->hDC );
  CRect rect = lpDrawItemStruct->rcItem;      // Button size
  UINT state = lpDrawItemStruct->itemState;   // Button state

  // If button is selected, need to draw it pushed
  if ( state & ODS_SELECTED )
    pDC->DrawFrameControl( rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED );
  else
    pDC->DrawFrameControl( rect, DFC_BUTTON, DFCS_BUTTONPUSH );

  // Draw the button deflated
  rect.DeflateRect( CSize( GetSystemMetrics( SM_CXEDGE ), GetSystemMetrics( SM_CYEDGE ) ) );

  // Fill the button with the given color
  pDC->FillSolidRect( rect, button_color );

  // Draw the button text
  CString button_text;
  GetWindowText( button_text );

  if ( !button_text.IsEmpty() )
  {
    // Get the dimensions of the button text
    CSize text_extent = pDC->GetTextExtent( button_text );
    // Find the location of the button text centered in the button
    CPoint pt( rect.CenterPoint().x - text_extent.cx/2, rect.CenterPoint().y - text_extent.cy/2 );

    // Write the button text in black
    pDC->SetTextColor( RGB( 0, 0, 0 ) );
    // Center the button text in the button
    pDC->TextOut( pt.x, pt.y, button_text );
  }
}
