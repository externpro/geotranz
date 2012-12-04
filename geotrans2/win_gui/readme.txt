========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : GEOTRANS
========================================================================

This file contains a summary of what you will find in each of the files that
make up your GEOTRANS application.

GEOTRANS.H
    This is the main include file for the application.  It includes other
    project specific includes (including RESOURCE.H) and declares the
    CGeotransApp application class.

GEOTRANS.CPP
    This is the main application source file that contains the application
    class CGeotransApp.

GEOTRANS.RC
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited with App Studio.

RES\GEOTRANS.ICO
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file GEOTRANS.RC.

RES\GEOTRANS.RC2
    This file contains resources that are not edited by App Studio.  Initially
    this contains a VERSIONINFO resource that you can customize for your
    application.  You should place other non-App Studio editable resources
    in this file.

GEOTRANS.DEF
    This file contains information about the application that must be
    provided to run with Microsoft Windows.  It defines parameters
    such as the name and description of the application, and the size
    of the initial local heap.  The numbers in this file are typical
    for applications developed with the Microsoft Foundation Class Library.
    The default stack size can be adjusted by editing the project file.

GEOTRANS.CLW
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to generate and edit message maps and dialog data
    maps and to generate prototype member functions.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MAINFRM.H, MAINFRM.CPP
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

GEOTRDOC.H, GEOTRDOC.CPP - the document
    These files contain your CGeotransDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CGeotransDoc::Serialize).

GEOTRVW.H, GEOTRVW.CPP - the view of the document
    These files contain your CGeotransView class.
    CGeotransView objects are used to view CGeotransDoc objects.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

STDAFX.H, STDAFX.CPP
    These files are used to build a precompiled header (PCH) file
    named STDAFX.PCH and a precompiled types (PCT) file named STDAFX.OBJ.

RESOURCE.H
    This is the standard header file, which defines new resource IDs.
    App Studio reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
