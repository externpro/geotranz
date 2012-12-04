# Microsoft Developer Studio Project File - Name="geotrans_dll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=geotrans_dll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "geotrans_dll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "geotrans_dll.mak" CFG="geotrans_dll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "geotrans_dll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "geotrans_dll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "geotrans_dll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./Release"
# PROP Intermediate_Dir "./Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GEOTRANS_DLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /Od /I "..\..\dt_cc\gars" /I "..\..\dt_cc\usng" /I "..\..\dt_cc\threads" /I "..\..\dt_cc\albers" /I "..\..\dt_cc\azeq" /I "..\..\dt_cc\bng" /I "..\..\dt_cc\bonne" /I "..\..\dt_cc\cassini" /I "..\..\dt_cc\cyleqa" /I "..\..\dt_cc\datum" /I "..\..\dt_cc\eckert4" /I "..\..\dt_cc\eckert6" /I "..\..\dt_cc\ellipse" /I "..\..\dt_cc\eqdcyl" /I "..\..\dt_cc\geocent" /I "..\..\dt_cc\geoid" /I "..\..\dt_cc\georef" /I "..\..\dt_cc\gnomonic" /I "..\..\dt_cc\grinten" /I "..\..\dt_cc\lambert_2" /I "..\..\dt_cc\lambert_1" /I "..\..\dt_cc\loccart" /I "..\..\dt_cc\mercator" /I "..\..\dt_cc\mgrs" /I "..\..\dt_cc\miller" /I "..\..\dt_cc\mollweid" /I "..\..\dt_cc\neys" /I "..\..\dt_cc\nzmg" /I "..\..\dt_cc\orthogr" /I "..\..\dt_cc\polarst" /I "..\..\dt_cc\polycon" /I "..\..\dt_cc\sinusoid" /I "..\..\dt_cc\stereogr" /I "..\..\dt_cc\tranmerc" /I "..\..\dt_cc\trcyleqa" /I "..\..\dt_cc\ups" /I "..\..\dt_cc\utm" /I "..\..\engine\src" /I "..\..\dt_cc\omerc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GEOTRANS_DLL_EXPORTS" /D "LITTLE_ENDIAN" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x20000000 " /dll /machine:I386 /out:"./Release/geotrans2.dll"

!ELSEIF  "$(CFG)" == "geotrans_dll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "."
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GEOTRANS_DLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /I "..\..\dt_cc\gars" /I "..\..\dt_cc\usng" /I "..\..\dt_cc\threads" /I "..\..\dt_cc\albers" /I "..\..\dt_cc\azeq" /I "..\..\dt_cc\bng" /I "..\..\dt_cc\bonne" /I "..\..\dt_cc\cassini" /I "..\..\dt_cc\cyleqa" /I "..\..\dt_cc\datum" /I "..\..\dt_cc\eckert4" /I "..\..\dt_cc\eckert6" /I "..\..\dt_cc\ellipse" /I "..\..\dt_cc\eqdcyl" /I "..\..\dt_cc\geocent" /I "..\..\dt_cc\geoid" /I "..\..\dt_cc\georef" /I "..\..\dt_cc\gnomonic" /I "..\..\dt_cc\grinten" /I "..\..\dt_cc\lambert_2" /I "..\..\dt_cc\lambert_1" /I "..\..\dt_cc\loccart" /I "..\..\dt_cc\mercator" /I "..\..\dt_cc\mgrs" /I "..\..\dt_cc\miller" /I "..\..\dt_cc\mollweid" /I "..\..\dt_cc\neys" /I "..\..\dt_cc\nzmg" /I "..\..\dt_cc\orthogr" /I "..\..\dt_cc\polarst" /I "..\..\dt_cc\polycon" /I "..\..\dt_cc\sinusoid" /I "..\..\dt_cc\stereogr" /I "..\..\dt_cc\tranmerc" /I "..\..\dt_cc\trcyleqa" /I "..\..\dt_cc\ups" /I "..\..\dt_cc\utm" /I "..\..\engine\src" /I "..\..\dt_cc\omerc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GEOTRANS_DLL_EXPORTS" /D "LITTLE_ENDIAN" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x20000000 " /dll /incremental:no /debug /machine:I386 /out:"./geotrans2.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "geotrans_dll - Win32 Release"
# Name "geotrans_dll - Win32 Debug"
# Begin Group "dtcc"

# PROP Default_Filter ""
# Begin Group "dtcc Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dt_cc\albers\albers.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\azeq\azeq.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\bng\bng.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\bonne\bonne.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\cassini\cassini.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\cyleqa\cyleqa.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\datum\datum.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\eckert4\eckert4.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\eckert6\eckert6.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\ellipse\ellipse.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\eqdcyl\eqdcyl.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\gars\gars.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\geocent\geocent.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\geoid\geoid.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\georef\georef.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\gnomonic\gnomonic.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\grinten\grinten.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\lambert_1\lambert_1.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\lambert_2\lambert_2.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\loccart\loccart.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\mercator\mercator.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\mgrs\mgrs.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\miller\miller.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\mollweid\mollweid.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\neys\neys.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\nzmg\nzmg.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\omerc\omerc.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\orthogr\orthogr.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\polarst\polarst.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\polycon\polycon.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\sinusoid\sinusoid.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\stereogr\stereogr.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\threads\threads.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\tranmerc\tranmerc.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\trcyleqa\trcyleqa.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\ups\ups.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\usng\usng.c
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\utm\utm.c
# End Source File
# End Group
# Begin Group "dtcc Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\dt_cc\albers\albers.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\azeq\azeq.h
# End Source File
# Begin Source File

SOURCE=\geotrans\geotrans2.2\dt_cc\bng\bng.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\bonne\bonne.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\cassini\cassini.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\cyleqa\cyleqa.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\datum\datum.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\eckert4\eckert4.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\eckert6\eckert6.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\ellipse\ellipse.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\eqdcyl\eqdcyl.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\geocent\geocent.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\geoid\geoid.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\georef\georef.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\gnomonic\gnomonic.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\grinten\grinten.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\lambert_1\lambert_1.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\lambert_2\lambert_2.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\loccart\loccart.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\mercator\mercator.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\mgrs\mgrs.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\miller\miller.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\mollweid\mollweid.h
# End Source File
# Begin Source File

SOURCE=\geotrans\geotrans2.2\dt_cc\neys\neys.h
# End Source File
# Begin Source File

SOURCE=\geotrans\geotrans2.2\dt_cc\nzmg\nzmg.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\omerc\omerc.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\orthogr\orthogr.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\polarst\polarst.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\polycon\polycon.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\sinusoid\sinusoid.h
# End Source File
# Begin Source File

SOURCE=\geotrans\geotrans2.2\dt_cc\stereogr\stereogr.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\threads\threads.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\tranmerc\tranmerc.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\trcyleqa\trcyleqa.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\ups\ups.h
# End Source File
# Begin Source File

SOURCE=..\..\dt_cc\utm\utm.h
# End Source File
# End Group
# End Group
# Begin Group "engine"

# PROP Default_Filter ""
# Begin Group "engine Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\engine\src\engine.c
# End Source File
# End Group
# Begin Group "engine Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\engine\src\engine.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\geotrans2.def
# End Source File
# End Target
# End Project
