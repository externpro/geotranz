# Microsoft Developer Studio Project File - Name="engine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=engine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "engine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "engine.mak" CFG="engine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "engine - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "engine - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "engine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./Release"
# PROP Intermediate_Dir "./Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W2 /GX /O2 /I "..\..\dt_cc\gars" /I "..\..\dt_cc\usng" /I "..\..\dt_cc\nzmg" /I "..\..\dt_cc\bng" /I "..\..\dt_cc\neys" /I "..\..\dt_cc\albers" /I "..\..\dt_cc\azeq" /I "..\..\dt_cc\bonne" /I "..\..\dt_cc\cassini" /I "..\..\dt_cc\cyleqa" /I "..\..\dt_cc\datum" /I "..\..\dt_cc\eckert4" /I "..\..\dt_cc\eckert6" /I "..\..\dt_cc\ellipse" /I "..\..\dt_cc\eqdcyl" /I "..\..\dt_cc\geocent" /I "..\..\dt_cc\geoid" /I "..\..\dt_cc\georef" /I "..\..\dt_cc\gnomonic" /I "..\..\dt_cc\grinten" /I "..\..\dt_cc\lambert_2" /I "..\..\dt_cc\lambert_1" /I "..\..\dt_cc\loccart" /I "..\..\dt_cc\mercator" /I "..\..\dt_cc\miller" /I "..\..\dt_cc\mollweid" /I "..\..\dt_cc\mgrs" /I "..\..\dt_cc\omerc" /I "..\..\dt_cc\orthogr" /I "..\..\dt_cc\polarst" /I "..\..\dt_cc\polycon" /I "..\..\dt_cc\sinusoid" /I "..\..\dt_cc\stereogr" /I "..\..\dt_cc\tranmerc" /I "..\..\dt_cc\trcyleqa" /I "..\..\dt_cc\ups" /I "..\..\dt_cc\utm" /D "WIN32" /D "NDEBUG" /D "_LIB" /YX /FD " " " " /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "engine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "."
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /Zi /Od /I "..\..\dt_cc\gars" /I "..\..\dt_cc\usng" /I "..\..\dt_cc\nzmg" /I "..\..\dt_cc\bng" /I "..\..\dt_cc\neys" /I "..\..\dt_cc\albers" /I "..\..\dt_cc\azeq" /I "..\..\dt_cc\bonne" /I "..\..\dt_cc\cassini" /I "..\..\dt_cc\cyleqa" /I "..\..\dt_cc\datum" /I "..\..\dt_cc\eckert4" /I "..\..\dt_cc\eckert6" /I "..\..\dt_cc\ellipse" /I "..\..\dt_cc\eqdcyl" /I "..\..\dt_cc\geocent" /I "..\..\dt_cc\geoid" /I "..\..\dt_cc\georef" /I "..\..\dt_cc\gnomonic" /I "..\..\dt_cc\grinten" /I "..\..\dt_cc\lambert_2" /I "..\..\dt_cc\lambert_1" /I "..\..\dt_cc\loccart" /I "..\..\dt_cc\mercator" /I "..\..\dt_cc\miller" /I "..\..\dt_cc\mollweid" /I "..\..\dt_cc\mgrs" /I "..\..\dt_cc\omerc" /I "..\..\dt_cc\orthogr" /I "..\..\dt_cc\polarst" /I "..\..\dt_cc\polycon" /I "..\..\dt_cc\sinusoid" /I "..\..\dt_cc\stereogr" /I "..\..\dt_cc\tranmerc" /I "..\..\dt_cc\trcyleqa" /I "..\..\dt_cc\ups" /I "..\..\dt_cc\utm" /D "WIN32" /D "_DEBUG" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"engine.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"engine.lib"

!ENDIF 

# Begin Target

# Name "engine - Win32 Release"
# Name "engine - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\engine.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\engine.h
# End Source File
# End Group
# End Target
# End Project
