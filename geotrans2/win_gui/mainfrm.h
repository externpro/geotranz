// mainfrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMasterView;
class Defaults;
class CCreateDatumPropertySheet;

class CMainFrame : public CFrameWnd
{
private:
    CSplitterWnd* m_pSplitter;
    CStatusBar  m_wndStatusBar;

    HBRUSH background_brush;
    COLORREF background_color;
    COLORREF text_color;

    int geodetic_format;
    int geodetic_hemiFlag;

    int leading_zeros;

    Precision precis;
    char current_dir[256];

    bool engine_initialized;

    char* data_dir_path_name;
    Defaults* defaults;

    CCreateDatumPropertySheet* createDatumPropertySheet;

protected: // create from serialization only
    CMainFrame();
    DECLARE_DYNCREATE(CMainFrame)
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// Attributes
public:
    HBRUSH GetBackgroundBrush();
    COLORREF GetBackgroundColor();
    COLORREF GetTextColor();
    
// Operations
public:
    void Check_3D_Conversion( void );
    void Check_Valid_Conversion();

    int getUnits();
    char* getUnitsString();
    int getSeparatorIndex();
    char getSeparator();
    int getSignHemi();
    char* getSignHemiString();
    int getRange();
    char* getRangeString();
    int getPrecision();
    char* getPrecisionString();
    char* getLeadingZeros();

    void setUnits( int units );
    void setSeparator( int separator );
    void setSignHemi( int signHemi );
    void setLongitudeRange( int longitudeRange );
    void setPrecision( int precision );
    void setLeadingZeros( char* leadingZeros );


// Implementation
public:
    virtual ~CMainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
private:
    //{{AFX_MSG(CMainFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnHelpHelp();
    afx_msg void OnOptionsColorsBackground();
    afx_msg void OnOptionsColorsText();
    afx_msg void OnOptionsGeodeticformatSignhemisphereNsew();
    afx_msg void OnOptionsGeodeticformatSignhemispherePlusMinus();
    afx_msg void OnOptionsGeodeticformatUnitsDegreesminutesseconds();
    afx_msg void OnOptionsGeodeticformatUnitsDegreesminutes();
    afx_msg void OnOptionsGeodeticformatUnitsDegree();
    afx_msg void OnUpdateOptionsGeodeticformatSignhemisphereNsew(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsGeodeticformatSignhemispherePlusMinus(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsGeodeticformatUnitsDegree(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsGeodeticformatUnitsDegreesminutes(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsGeodeticformatUnitsDegreesminutesseconds(CCmdUI* pCmdUI);
    afx_msg void OnFileOpen();
    afx_msg void OnOptionsPrecision100000m();
    afx_msg void OnOptionsPrecision10000m();
    afx_msg void OnOptionsPrecision1000m();
    afx_msg void OnOptionsPrecision100m();
    afx_msg void OnOptionsPrecision10m();
    afx_msg void OnOptionsPrecision1m();
    afx_msg void OnOptionsPrecisionPnt1m();
    afx_msg void OnUpdateOptionsPrecision100000m(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsPrecision10000m(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsPrecision1000m(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsPrecision100m(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsPrecision10m(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsPrecision1m(CCmdUI* pCmdUI);
    afx_msg void OnUpdateOptionsPrecisionPnt1m(CCmdUI* pCmdUI);
	  afx_msg void OnOptionsGeodeticformatSeparatorBlankspace();
	  afx_msg void OnUpdateOptionsGeodeticformatSeparatorBlankspace(CCmdUI* pCmdUI);
	  afx_msg void OnUpdateOptionsGeodeticformatSeparatorSlash(CCmdUI* pCmdUI);
	  afx_msg void OnOptionsGeodeticformatSeparatorSlash();
	  afx_msg void OnOptionsGeodeticformatSeparatorColon();
	  afx_msg void OnUpdateOptionsGeodeticformatSeparatorColon(CCmdUI* pCmdUI);
	  afx_msg void OnUpdateOptionsGeodeticformatLongituderange180180(CCmdUI* pCmdUI);
	  afx_msg void OnOptionsGeodeticformatLongituderange180180();
	  afx_msg void OnOptionsGeodeticformatLongituderange0360();
	  afx_msg void OnUpdateOptionsGeodeticformatLongituderange0360(CCmdUI* pCmdUI);
	  afx_msg void OnChangeAccuracy();
	  afx_msg void OnOptionsPrecision1cm();
	  afx_msg void OnUpdateOptionsPrecision1cm(CCmdUI* pCmdUI);
	  afx_msg void OnOptionsPrecision1mm();
	  afx_msg void OnUpdateOptionsPrecision1mm(CCmdUI* pCmdUI);
	  afx_msg void OnOptionsLeadingZeros();
	  afx_msg void OnUpdateOptionsLeadingZeros(CCmdUI* pCmdUI);
	  afx_msg void OnDatumCreate();
	  afx_msg void OnDatumDelete();
	  afx_msg void OnEllipsoidCreate();
	  afx_msg void OnEllipsoidDelete();
	  afx_msg void OnConvertUppertoLower();
	  afx_msg void OnConvertLowertoUpper();
	  afx_msg void OnCreateHeader();
	afx_msg void OnSaveAsDefault();
	afx_msg void OnRestoreDefault();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
