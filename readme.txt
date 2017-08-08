                                   UNCLASSIFIED

MSP GEOTRANS 3.0

The MSP GEOTRANS 3.0 software was developed and tested on Windows XP, Solaris 8, Red Hat Linux Enterprise 4, and should function correctly on more recent versions of those operating systems.

There are eight different MSP GEOTRANS 3.0 distribution files - four for Windows, in zip format, and four for Solaris/Linux, in tar/gzip format:
The Windows packages omit the Solaris/Linux-specific directories, while the Solaris/Linux packages omit the Windows-specific directories.

win_user.zip - Windows end-user package
win_dev.zip - Windows developer package
master.zip - master package (everything)
mgrs.zip - MGRS & supporting projections package

unix_user.tgz - Solaris/Linux end-user package
unix_dev.tgz - Solaris/Linux developer package
master.tgz - master package (everything)
mgrs.tgz - MGRS & supporting projections package

The end-user packages contain only executables, DLLs or shared object libraries, documentation, and supporting data.

The developer packages also include source code, as well as makefiles, MS Visual C++ solution and project files, and everything else necessary to build the libraries and executables.  

The master packages can be considered to be cross-platform developer packages.  The Windows and UNIX packages contain the union of the Windows and Solaris/Linux developer packages.  Only their format is different (.zip vs .tgz).  

The MGRS packages contain only the source code for the MGRS, UTM, UPS, Transverse Mercator, and Polar Stereographic conversion modules, and are intended for developers who only want to do MGRS conversions.  The Windows and UNIX packages are identical.  Only their format is different (.zip vs .tgz).

You should only need to copy one of these packages, depending on your platform and your intended usage.

GEOTRANS Terms of Use:

1. The GEOTRANS source code ("the software") is provided free of charge by the National Geospatial-Intelligence Agency (NGA) of the United States Department of Defense. Although NGA makes no copyright claim under Title 17 U.S.C., NGA claims copyrights in the source code under other legal regimes. NGA hereby grants to each user of the software a license to use and distribute the software, and develop derivative works.

2. NGA requests that products developed using the software credit the source of the software with the following statement, "The product was developed using GEOTRANS, a product of the National Geospatial-Intelligence Agency (NGA) and U.S. Army Engineering Research and Development Center."  Do not use the name GEOTRANS for any derived work.

3. Warranty Disclaimer: The software was developed to meet only the internal requirements of the National Geospatial-Intelligence Agency (NGA). The software is provided "as is," and no warranty, express or implied, including but not limited to the implied warranties of merchantability and fitness for particular purpose or arising by statute or otherwise in law or from a course of dealing or usage in trade, is made by NGA as to the accuracy and functioning of the software.

4. NGA and its personnel are not required to provide technical support or general assistance with respect to public use of the software.  Government customers may contact NGA.

5. Neither NGA nor its personnel will be liable for any claims, losses, or damages arising from or connected with the use of the software. The user agrees to hold harmless the United States National Geospatial-Intelligence Agency (NGA). The user's sole and exclusive remedy is to stop using the software.

6. Please be advised that pursuant to the United States Code, 10 U.S.C. 425, the name of the National Geospatial-Intelligence Agency, the initials "NGA", the seal of the National Geospatial-Intelligence Agency, or any colorable imitation thereof shall not be used to imply approval, endorsement, or authorization of a product without prior written permission from United States Secretary of Defense.  Do not create the impression that NGA, the Secretary of Defense or the Director of National Intelligence has endorsed any product derived from GEOTRANS.

                                   UNCLASSIFIED

