# Microsoft Developer Studio Project File - Name="geotrans2d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=geotrans2d - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "geotrans2d.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "geotrans2d.mak" CFG="geotrans2d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "geotrans2d - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "geotrans2d - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "geotrans2d - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./Release"
# PROP Intermediate_Dir "./Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W2 /GX /O2 /I "..\..\engine\src" /I "..\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ./geotrans2.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes /debug /nodefaultlib

!ELSEIF  "$(CFG)" == "geotrans2d - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "."
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /I "..\..\engine\src" /I "..\src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /LD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /fo"./geotransd.res" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ./geotrans2.lib /nologo /subsystem:windows /incremental:no /pdb:"geotrans2d.pdb" /debug /machine:I386 /pdbtype:sept /VERBOSE:LIB
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "geotrans2d - Win32 Release"
# Name "geotrans2d - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\win_gui\3ParamPropertyPage.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\7ParamPropertyPage.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\ColorButton.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\convertvw.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\CreateDatumPropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\defaults.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\deldatumvw.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\delellipvw.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\ellipsevw.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\filevw.cpp
# End Source File
# Begin Source File

SOURCE=..\src\fiomeths.c
# End Source File
# Begin Source File

SOURCE=..\win_gui\geotrans.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\geotrans.rc
# End Source File
# Begin Source File

SOURCE=..\win_gui\geotrdoc.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\geotrvw.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\mainfrm.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\mastervw.cpp
# End Source File
# Begin Source File

SOURCE=..\win_gui\progress.cpp
# End Source File
# Begin Source File

SOURCE=..\src\source.c
# End Source File
# Begin Source File

SOURCE=..\win_gui\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=..\src\strndup.c
# End Source File
# Begin Source File

SOURCE=..\src\strtoval.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\win_gui\3ParamPropertyPage.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\7ParamPropertyPage.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\ColorButton.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\convertvw.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\deldatumvw.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\delellipvw.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\ellipsevw.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\filevw.h
# End Source File
# Begin Source File

SOURCE=..\src\fiomeths.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\geotrans.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\geotrdoc.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\geotrvw.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\mainfrm.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\mastervw.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\progress.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\resource.h
# End Source File
# Begin Source File

SOURCE=..\src\Source.h
# End Source File
# Begin Source File

SOURCE=..\win_gui\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\src\strndup.h
# End Source File
# Begin Source File

SOURCE=..\src\strtoval.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\win_gui\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=..\win_gui\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=..\win_gui\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=..\win_gui\res\geotrans.ico
# End Source File
# Begin Source File

SOURCE=..\win_gui\res\geotrans.rc2
# End Source File
# Begin Source File

SOURCE=..\win_gui\res\icon1.ico
# End Source File
# End Group
# End Target
# End Project
