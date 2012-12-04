# Microsoft Developer Studio Project File - Name="dtcc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dtcc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dtcc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dtcc.mak" CFG="dtcc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dtcc - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "dtcc - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dtcc - Win32 Release"

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
# ADD CPP /nologo /MT /W2 /GX /O2 /I "..\usng" /I "..\threads" /I "..\lambert_2" /I "..\lambert_1" /I "..\ellipse" /I "..\ups" /I "..\utm" /I "..\loccart" /I "..\polarst" /I "..\sinusoid" /I "..\tranmerc" /I "..\geocent" /I "..\datum" /D "WIN32" /D "NDEBUG" /D "_LIB" /D "LITTLE_ENDIAN" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "dtcc - Win32 Debug"

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
# ADD CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /I "..\usng" /I "..\threads" /I "..\lambert_2" /I "..\lambert_1" /I "..\ellipse" /I "..\ups" /I "..\utm" /I "..\loccart" /I "..\polarst" /I "..\sinusoid" /I "..\tranmerc" /I "..\geocent" /I "..\datum" /D "WIN32" /D "_DEBUG" /D "_LIB" /D "LITTLE_ENDIAN" /FR /YX /FD /GZ /c
# SUBTRACT CPP /Gf /Gy
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"dtcc.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"dtcc.lib"

!ENDIF 

# Begin Target

# Name "dtcc - Win32 Release"
# Name "dtcc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\albers\albers.c
# End Source File
# Begin Source File

SOURCE=..\azeq\azeq.c
# End Source File
# Begin Source File

SOURCE=..\bng\bng.c
# End Source File
# Begin Source File

SOURCE=..\bonne\bonne.c
# End Source File
# Begin Source File

SOURCE=..\cassini\cassini.c
# End Source File
# Begin Source File

SOURCE=..\cyleqa\cyleqa.c
# End Source File
# Begin Source File

SOURCE=..\datum\datum.c
# End Source File
# Begin Source File

SOURCE=..\eckert4\eckert4.c
# End Source File
# Begin Source File

SOURCE=..\eckert6\eckert6.c
# End Source File
# Begin Source File

SOURCE=..\ellipse\ellipse.c
# End Source File
# Begin Source File

SOURCE=..\eqdcyl\eqdcyl.c
# End Source File
# Begin Source File

SOURCE=..\gars\gars.c
# End Source File
# Begin Source File

SOURCE=..\geocent\geocent.c
# End Source File
# Begin Source File

SOURCE=..\geoid\geoid.c
# End Source File
# Begin Source File

SOURCE=..\georef\georef.c
# End Source File
# Begin Source File

SOURCE=..\gnomonic\gnomonic.c
# End Source File
# Begin Source File

SOURCE=..\grinten\grinten.c
# End Source File
# Begin Source File

SOURCE=..\lambert_1\lambert_1.c
# End Source File
# Begin Source File

SOURCE=..\lambert_2\lambert_2.c
# End Source File
# Begin Source File

SOURCE=..\loccart\loccart.c
# End Source File
# Begin Source File

SOURCE=..\mercator\mercator.c
# End Source File
# Begin Source File

SOURCE=..\mgrs\mgrs.c
# End Source File
# Begin Source File

SOURCE=..\miller\miller.c
# End Source File
# Begin Source File

SOURCE=..\mollweid\mollweid.c
# End Source File
# Begin Source File

SOURCE=..\neys\neys.c
# End Source File
# Begin Source File

SOURCE=..\nzmg\nzmg.c
# End Source File
# Begin Source File

SOURCE=..\omerc\omerc.c
# End Source File
# Begin Source File

SOURCE=..\orthogr\orthogr.c
# End Source File
# Begin Source File

SOURCE=..\polarst\polarst.c
# End Source File
# Begin Source File

SOURCE=..\polycon\polycon.c
# End Source File
# Begin Source File

SOURCE=..\sinusoid\sinusoid.c
# End Source File
# Begin Source File

SOURCE=..\stereogr\stereogr.c
# End Source File
# Begin Source File

SOURCE=..\threads\threads.c
# End Source File
# Begin Source File

SOURCE=..\tranmerc\tranmerc.c
# End Source File
# Begin Source File

SOURCE=..\trcyleqa\trcyleqa.c
# End Source File
# Begin Source File

SOURCE=..\ups\ups.c
# End Source File
# Begin Source File

SOURCE=..\usng\usng.c
# End Source File
# Begin Source File

SOURCE=..\utm\utm.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\albers\albers.h
# End Source File
# Begin Source File

SOURCE=..\azeq\azeq.h
# End Source File
# Begin Source File

SOURCE=..\bng\bng.h
# End Source File
# Begin Source File

SOURCE=..\bonne\bonne.h
# End Source File
# Begin Source File

SOURCE=..\cassini\cassini.h

!IF  "$(CFG)" == "dtcc - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "dtcc - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\cyleqa\cyleqa.h
# End Source File
# Begin Source File

SOURCE=..\datum\datum.h
# End Source File
# Begin Source File

SOURCE=..\eckert4\eckert4.h
# End Source File
# Begin Source File

SOURCE=..\eckert6\eckert6.h
# End Source File
# Begin Source File

SOURCE=..\ellipse\ellipse.h
# End Source File
# Begin Source File

SOURCE=..\eqdcyl\eqdcyl.h
# End Source File
# Begin Source File

SOURCE=..\gars\gars.h
# End Source File
# Begin Source File

SOURCE=..\geocent\geocent.h
# End Source File
# Begin Source File

SOURCE=..\geoid\geoid.h
# End Source File
# Begin Source File

SOURCE=..\georef\georef.h
# End Source File
# Begin Source File

SOURCE=..\gnomonic\gnomonic.h
# End Source File
# Begin Source File

SOURCE=..\grinten\grinten.h
# End Source File
# Begin Source File

SOURCE=..\lambert_1\lambert_1.h
# End Source File
# Begin Source File

SOURCE=..\lambert_2\lambert_2.h
# End Source File
# Begin Source File

SOURCE=..\loccart\loccart.h
# End Source File
# Begin Source File

SOURCE=..\mercator\mercator.h
# End Source File
# Begin Source File

SOURCE=..\mgrs\mgrs.h
# End Source File
# Begin Source File

SOURCE=..\miller\miller.h
# End Source File
# Begin Source File

SOURCE=..\mollweid\mollweid.h
# End Source File
# Begin Source File

SOURCE=..\neys\neys.h
# End Source File
# Begin Source File

SOURCE=..\nzmg\nzmg.h
# End Source File
# Begin Source File

SOURCE=..\omerc\omerc.h
# End Source File
# Begin Source File

SOURCE=..\orthogr\orthogr.h
# End Source File
# Begin Source File

SOURCE=..\polarst\polarst.h
# End Source File
# Begin Source File

SOURCE=..\polycon\polycon.h
# End Source File
# Begin Source File

SOURCE=..\sinusoid\sinusoid.h
# End Source File
# Begin Source File

SOURCE=..\stereogr\stereogr.h
# End Source File
# Begin Source File

SOURCE=..\threads\threads.h
# End Source File
# Begin Source File

SOURCE=..\tranmerc\tranmerc.h
# End Source File
# Begin Source File

SOURCE=..\trcyleqa\trcyleqa.h
# End Source File
# Begin Source File

SOURCE=..\ups\ups.h
# End Source File
# Begin Source File

SOURCE=..\usng\usng.h
# End Source File
# Begin Source File

SOURCE=..\utm\utm.h
# End Source File
# End Group
# End Target
# End Project
