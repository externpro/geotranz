#if !defined(AFX_FILEVW_H__E43668C9_A251_436F_908C_93714741B651__INCLUDED_)
#define AFX_FILEVW_H__E43668C9_A251_436F_908C_93714741B651__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// filevw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileProcDlg dialog

class CFileProcDlg : public CDialog
{
// Construction
public:
	CFileProcDlg(CWnd* pParent = NULL);   // standard constructor
  BOOL OnInitDialog(void);
  void Set_Current_Directory(char* dir);
  void SetFormat(bool, bool, bool);

private:
    void FillDatumListBox(void);
    void FillHeightList(void);
    void FillSystemListBox(void);

// Dialog Data
private:
	//{{AFX_DATA(CFileProcDlg)
	enum { IDD = IDD_FILE_DIALOG };
	CComboBox	m_file_height_combobox;
  CString m_input_datum;
  CString m_input_ellipsoid;
  CString m_input_label;
  CString m_input_edit1;
  CString m_input_edit2;
  CString m_input_edit3;
  CString m_input_static1;
  CString m_input_static2;
  CString m_input_static3;
  CString m_output_edit1;
  CString m_output_edit2;
  CString m_output_edit3;
  CString m_output_static1;
  CString m_output_static2;
  CString m_output_static3;
  CString m_ellipsoid;
  CString m_datum;
  CString m_zone;
  CString m_input_edit5;
  CString m_input_static5;
  CString m_input_static21;
  CString m_input_static22;
  CString m_input_static23;
  CString m_input_static24;
  CString m_input_static25;
  CString m_input_static26;
  CString m_input_static27;
  CString m_input_static28;
  CString m_output_static21;
  CString m_output_static22;
  CString m_output_static23;
  CString m_output_static24;
  CString m_output_static25;
  CString m_output_static26;
  CString m_output_static27;
  CString m_output_static28;
  CString m_output_edit5;
  CString m_output_static5;
  CString m_input_height_type;
	CString	m_input_edit21;
	CString	m_input_edit22;
	CString	m_input_edit23;
	CString	m_input_edit24;
	CString	m_input_edit25;
	CString	m_input_edit26;
	CString	m_input_edit27;
	CString	m_input_edit28;
	CString	m_output_edit21;
	CString	m_output_edit22;
	CString	m_output_edit23;
	CString	m_output_edit24;
	CString	m_output_edit25;
	CString	m_output_edit26;
	CString	m_output_edit27;
	CString	m_output_edit28;
	//}}AFX_DATA

  Coordinate_Type input_type;
  Coordinate_Type output_type;
  char current_dir[256];
  bool use_Minutes;
  bool use_Seconds;
  bool use_NSEW;
  BOOL m_set_zone_button;
  int  m_std_parallel1;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileProcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileProcDlg)
    afx_msg void OnSelchangeOutputDatumCombobox();
    afx_msg void OnSelchangeOutputSystemCombobox();
    afx_msg void OnDlgUtmButton();
    afx_msg void OnChangeDlgUtmZoneEdit();
	  virtual void OnOK();
	  afx_msg void OnHelpButton();
	  afx_msg void OnFileOutputStdParallel71();
	  afx_msg void OnFileOutputStdParallel74();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEVW_H__E43668C9_A251_436F_908C_93714741B651__INCLUDED_)
