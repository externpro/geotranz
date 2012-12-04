// convertvw.cpp : implementation file
//
#include "stdafx.h"
#include "geotrans.h"
#include "engine.h"
#include "mastervw.h"
#include "convertvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConvertView 

IMPLEMENT_DYNCREATE(CConvertView, CFormView)

CConvertView::CConvertView()
: CFormView(CConvertView::IDD)
{
  //{{AFX_DATA_INIT(CConvertView)
	//}}AFX_DATA_INIT
  c_convert_to_upper_button = new CColorButton();
  c_convert_to_lower_button = new CColorButton();
}

CConvertView::~CConvertView()
{
}

void CConvertView::DoDataExchange(CDataExchange* pDX)
{
  CFormView::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CConvertView)
	DDX_Control(pDX, IDC_CONVERT_TO_UPPER_BUTTON, *c_convert_to_upper_button);
	DDX_Control(pDX, IDC_CONVERT_TO_LOWER_BUTTON, *c_convert_to_lower_button);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConvertView, CFormView)
//{{AFX_MSG_MAP(CConvertView)
ON_BN_CLICKED(IDC_CONVERT_TO_LOWER_BUTTON, OnConvertUppertoLower)
ON_BN_CLICKED(IDC_CONVERT_TO_UPPER_BUTTON, OnConvertLowertoUpper)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvertView diagnostics

#ifdef _DEBUG
    void CConvertView::AssertValid() const
{
  CFormView::AssertValid();
}

void CConvertView::Dump(CDumpContext& dc) const
{
  CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CConvertView message handlers

void CConvertView::OnConvertUppertoLower() 
{
  if (p_upper_view->f16GRS)
    Set_Coordinate_System( Interactive, Input, MGRS );
  else
    Set_Coordinate_System( Interactive, Input, p_upper_view->type );
  if (p_lower_view->f16GRS)
    Set_Coordinate_System( Interactive, Output, MGRS );
  else
    Set_Coordinate_System( Interactive, Output, p_lower_view->type );
  
  if (Set_Datum( Interactive, Input, p_upper_view->datum_index ) == 0)
  {
    if (Set_Datum( Interactive, Output, p_lower_view->datum_index ) == 0)
    {
      if (p_upper_view->GetParams( Input ) == 0)
      {
        if (p_upper_view->GetCoords( Input ) == 0)
        {
          p_upper_view->SetAccuracy();
          if (p_lower_view->GetParams( Output ) == 0)
          {
            long error_code = Convert(Interactive);   //  Convert !!
            if (!error_code)
            {
  	          p_lower_view->SetCoords( Output );
  	          p_lower_view->ReportAccuracy(); // set output form error values.
            }
            else
            {
              if (error_code & ENGINE_INPUT_ERROR)
              {
                char err_str[256];
                char temp_err_str[256];
                sprintf(err_str,"Error:\n");
                Get_Conversion_Status_String(Interactive,Input,"\n",temp_err_str);
                strcat(err_str, temp_err_str);
                AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
              }
              else if (error_code & ENGINE_INPUT_WARNING)
              {
                char err_str[256];
                char temp_err_str[256];
                sprintf(err_str,"Warning:\n");
                Get_Conversion_Status_String(Interactive,Input,"\n",temp_err_str);
                strcat(err_str, temp_err_str);
                AfxMessageBox(err_str,MB_OK | MB_ICONEXCLAMATION);
  
                if (!(error_code & ENGINE_OUTPUT_ERROR))
                {
                  p_lower_view->SetCoords( Output );
  	              p_lower_view->ReportAccuracy();
                }
              }
              if (error_code & ENGINE_OUTPUT_ERROR)
              {
                char err_str[256];
                char temp_err_str[256];
                sprintf(err_str,"Error:\n");
                Get_Conversion_Status_String(Interactive,Output,"\n",temp_err_str);
                strcat(err_str, temp_err_str);
                AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
              }
              else if (error_code & ENGINE_OUTPUT_WARNING)
              {
                char err_str[256];
                char temp_err_str[256];
                sprintf(err_str,"Warning:\n");
                Get_Conversion_Status_String(Interactive,Output,"\n",temp_err_str);
                strcat(err_str, temp_err_str);
                AfxMessageBox(err_str,MB_OK | MB_ICONEXCLAMATION);
                p_lower_view->SetCoords( Output );
                p_lower_view->ReportAccuracy(); 
              }
            }//end of else
          }
        }
      }
    }
    else
      AfxMessageBox("Error setting output datum",MB_OK | MB_ICONSTOP);
  }
  else
    AfxMessageBox("Error setting input datum",MB_OK | MB_ICONSTOP);

}

void CConvertView::OnConvertLowertoUpper() 
{
  if (p_lower_view->f16GRS)
    Set_Coordinate_System( Interactive, Input, MGRS );
  else
    Set_Coordinate_System( Interactive, Input, p_lower_view->type );
  if (p_upper_view->f16GRS)
    Set_Coordinate_System( Interactive, Output, MGRS );
  else
    Set_Coordinate_System( Interactive, Output, p_upper_view->type );

  if (Set_Datum( Interactive, Input, p_lower_view->datum_index ) == 0)
  {
    if (Set_Datum( Interactive, Output, p_upper_view->datum_index ) == 0)
    {
      if (p_lower_view->GetParams( Input ) == 0)
      {
        if (p_lower_view->GetCoords( Input ) == 0)
        {
          p_lower_view->SetAccuracy();
          if (p_upper_view->GetParams( Output ) == 0)
          {
            long error_code = Convert(Interactive);   //  Convert !!
            if (!error_code)
            {
              p_upper_view->SetCoords( Output );
              p_upper_view->ReportAccuracy(); // set output form error values.
            }
            else
            {
              if (error_code & ENGINE_INPUT_ERROR)
              {
                char err_str[256];
                char temp_err_str[256];
                sprintf(err_str,"Error:\n");
                Get_Conversion_Status_String(Interactive,Input,"\n",temp_err_str);
                strcat(err_str, temp_err_str);
                AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
              }
              else if (error_code & ENGINE_INPUT_WARNING)
              {
                char err_str[256];
                char temp_err_str[256];
                sprintf(err_str,"Warning:\n");
                Get_Conversion_Status_String(Interactive,Input,"\n",temp_err_str);
                strcat(err_str, temp_err_str);
                AfxMessageBox(err_str,MB_OK | MB_ICONEXCLAMATION);
        
                if (!(error_code & ENGINE_OUTPUT_ERROR))
                {
  	              p_upper_view->SetCoords( Output );
                  p_upper_view->ReportAccuracy();
                }
              }
              if (error_code & ENGINE_OUTPUT_ERROR)
              {
                char err_str[256];
                char temp_err_str[256];
                sprintf(err_str,"Error:\n");
                Get_Conversion_Status_String(Interactive,Output,"\n",temp_err_str);
                strcat(err_str, temp_err_str);
                AfxMessageBox(err_str,MB_OK | MB_ICONSTOP);
              }
              else if (error_code & ENGINE_OUTPUT_WARNING)
              {
                char err_str[256];
                char temp_err_str[256];
                sprintf(err_str,"Warning:\n");
                Get_Conversion_Status_String(Interactive,Output,"\n",temp_err_str);
                strcat(err_str, temp_err_str);
                AfxMessageBox(err_str,MB_OK | MB_ICONEXCLAMATION);
                p_upper_view->SetCoords( Output );
                p_upper_view->ReportAccuracy();
              }
            }
          }
        }
      }
    }
    else
      AfxMessageBox("Error setting output datum",MB_OK | MB_ICONSTOP);
  }
  else
    AfxMessageBox("Error setting input datum",MB_OK | MB_ICONSTOP);
}

void CConvertView::SetUpperPointer(CMasterView* p_view1)
{
  p_upper_view = p_view1;
}

void CConvertView::SetLowerPointer(CMasterView* p_view2)
{
  p_lower_view = p_view2;
}


void CConvertView::SetButtonColor(int red, int green, int blue)
{
  if( c_convert_to_upper_button && c_convert_to_lower_button )
  {
    c_convert_to_upper_button->SetColor(RGB(red, green, blue));
    c_convert_to_lower_button->SetColor(RGB(red, green, blue));
//    c_convert_to_upper_button->SetColors(RGB(0, 0, 0),RGB(red, green, blue),RGB(red, green, blue),RGB(red, green, blue));
 //   c_convert_to_lower_button->SetColors(RGB(0, 0, 0),RGB(red, green, blue),RGB(red, green, blue),RGB(red, green, blue));
  }
}

