#if !defined(AFX_MASTERVW_H__9771A103_98A2_4824_AE4A_243D9D2C6508__INCLUDED_)
#define AFX_MASTERVW_H__9771A103_98A2_4824_AE4A_243D9D2C6508__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// mastervw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMasterView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "engine.h"

class CGeotransDoc;

class CMasterView : public CFormView
{
protected:
	CMasterView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMasterView)

private:
  int format, hemiFlag;
  bool _3dConversion;
  bool use_Minutes;
  bool use_Seconds;
  bool use_NSEW;
  int geo_height;
  int hemisphere_type;
  int std_parallel1;
  bool tog_check;// for UTM Zone
  bool usePrevAccuracies;

  void Initialize_Form(void);

public:
  Coordinate_Type type;
  long datum_index;
  bool f16GRS;

	void FillHeightList();
  void FillProjectionList( Coordinate_Type type );
  void FillListBox();
  void FillSourcesListBox();
  void SetFormat(int format);
  void SetHemiFlag(int hFlag);
  int GetParams( Input_Output dir );
  int GetCoords( Input_Output dir );
  void SetCoords( Input_Output dir );
  void SetAccuracy();
  void ReportAccuracy(); // set output errors
  int getGeodeticHeight();
  void setGeodeticHeight(int type);
  void UpdateSrcErrors(bool _3dConv);

  void getDatumCode( char* code );
  void getProjectionCode( char* code );
  double get3ParamCentralMeridian();
  double getFalseEasting();
  double getFalseNorthing();
  double get4ParamCentralMeridian();
  double get4ParamOriginLatitude();
  double get5ParamCentralMeridian();
  double get5ParamOriginLatitude();
  double get5ParamScaleFactor();
  double get6ParamCentralMeridian();
  double get6ParamOriginLatitude();
  double get6ParamStandardParallel1();
  double get6ParamStandardParallel2();
  double getOriginLongitude();
  double getOriginLatitude();
  double getOriginHeight();
  double getOrientation();
  double getNeysStandardParallel1();
  double getOmercOriginLatitude();
  double getOmercScaleFactor();
  double getOmercLongitude1();
  double getOmercLatitude1();
  double getOmercLongitude2();
  double getOmercLatitude2();
  double getOmercFalseEasting();
  double getOmercFalseNorthing();
  int getOverride();
  long getZone();

  void setDatum( int datumIndex );
  void setProjection( int projectionIndex );
  void set3ParamCentralMeridian( double centralMeridian );
  void setFalseEasting( double false_easting );
  void setFalseNorthing( double false_northing );
  void set4ParamCentralMeridian( double central_meridian );
  void set4ParamOriginLatitude( double origin_latitude );
  void set5ParamCentralMeridian( double central_meridian );
  void set5ParamOriginLatitude( double origin_latitude );
  void set5ParamScaleFactor( double scale_factor );
  void set6ParamCentralMeridian( double central_meridian );
  void set6ParamOriginLatitude( double origin_latitude );
  void set6ParamStandardParallel1( double standard_parallel_1 );
  void set6ParamStandardParallel2( double standard_parallel_2 );
  void setOriginLongitude( double origin_longitude );
  void setOriginLatitude( double origin_latitude );
  void setOriginHeight( double origin_height );
  void setOrientation( double orientation );
  void setNeysStandardParallel1( double standard_parallel_1 );
  void setOmercOriginLatitude( double origin_latitude );
  void setOmercScaleFactor( double scale_factor );
  void setOmercLongitude1( double longitude1 );
  void setOmercLatitude1( double latitude1 );
  void setOmercLongitude2( double longitude2 );
  void setOmercLatitude2( double latitude2 );
  void setOmercFalseEasting( double false_easting );
  void setOmercFalseNorthing( double false_northing );
  void setOverride( int override );
  void setZone( long zone );


// Form Data
public:
	//{{AFX_DATA(CMasterView)
	enum { IDD = IDD_MASTER_FORM };
	CComboBox	m_height_combobox;
  CString m_datum_combobox;
  CString m_edit1_str;
  CString m_edit2_str;
  CString m_edit3_str;
  CString m_edit5_str;
  CString m_edit7_str;
  CString m_edit8_str;
  CString m_edit9_str;
  CString m_edit21_str;
  CString m_edit22_str;
  CString m_edit23_str;
  CString m_edit24_str;
  CString m_edit25_str;
  CString m_edit26_str;
  CString m_edit27_str;
  CString m_edit28_str;
  CString m_edit29_str;
  CString m_edit30_str;
  CString m_static1_str;
  CString m_static2_str;
  CString m_static3_str;
  CString m_static5_str;
  CString m_static7_str;
  CString m_static8_str;
  CString m_static9_str;
  CString m_static21_str;
  CString m_static22_str;
  CString m_static23_str;
  CString m_static24_str;
  CString m_static25_str;
  CString m_static26_str;
  CString m_static27_str;
  CString m_static28_str;
  CString m_static29_str;
  CString m_static30_str;
  CString m_ellipsoid_edit;
  CString m_errsrc;
  int   m_ups_hemi_n;
  CString m_zone_edit_str;
  CString m_ce90_str;
  CString m_le90_str;
  CString m_se90_str;
  CString m_edit_coord_str;
  CString m_static_coord_str;
	//}}AFX_DATA

// Attributes
public:


// Operations
public:

  CGeotransDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMasterView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMasterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMasterView)
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg void OnSelchangeCombobox();
  afx_msg void OnSelchangeSelectProjection();
  afx_msg void OnSelchangeDatumCombobox();
    afx_msg void OnSelchangeErrsrc();
  afx_msg void OnMslHeight();
  afx_msg void OnNoHeight();
  afx_msg void OnEllipsoidHeight();
  afx_msg void OnHemiN();
  afx_msg void OnHemiS();
  afx_msg void OnSetUtmZone();
  afx_msg void OnStdParallel71();
  afx_msg void OnStdParallel74();
	afx_msg void OnChangeCE90();
	afx_msg void OnChangeLE90();
	afx_msg void OnChangeSE90();
	afx_msg void OnSelchangeHeightCombobox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in geotrvw.cpp
inline CGeotransDoc* CMasterView::GetDocument()
{ return (CGeotransDoc*)m_pDocument;}
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASTERVW_H__9771A103_98A2_4824_AE4A_243D9D2C6508__INCLUDED_)
