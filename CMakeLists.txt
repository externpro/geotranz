cmake_minimum_required(VERSION 3.31)
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES .devcontainer/cmake/xproinc.cmake)
project(geotrans)
include(GNUInstallDirs)
include(xpflags)
set(lib_name ${PROJECT_NAME})
#######################################
set(lib_srcs
  dt_cc/albers/albers.c
  dt_cc/azeq/azeq.c
  dt_cc/bng/bng.c
  dt_cc/bonne/bonne.c
  dt_cc/cassini/cassini.c
  dt_cc/cyleqa/cyleqa.c
  dt_cc/datum/datum.c
  dt_cc/eckert4/eckert4.c
  dt_cc/eckert6/eckert6.c
  dt_cc/ellipse/ellipse.c
  dt_cc/eqdcyl/eqdcyl.c
  dt_cc/gars/gars.c
  dt_cc/geocent/geocent.c
  dt_cc/geoid/geoid.c
  dt_cc/georef/georef.c
  dt_cc/gnomonic/gnomonic.c
  dt_cc/grinten/grinten.c
  dt_cc/lambert_1/lambert_1.c
  dt_cc/lambert_2/lambert_2.c
  dt_cc/loccart/loccart.c
  dt_cc/mercator/mercator.c
  dt_cc/mgrs/mgrs.c
  dt_cc/miller/miller.c
  dt_cc/mollweid/mollweid.c
  dt_cc/neys/neys.c
  dt_cc/nzmg/nzmg.c
  dt_cc/omerc/omerc.c
  dt_cc/orthogr/orthogr.c
  dt_cc/polarst/polarst.c
  dt_cc/polycon/polycon.c
  dt_cc/sinusoid/sinusoid.c
  dt_cc/stereogr/stereogr.c
  dt_cc/threads/threads.c
  dt_cc/tranmerc/tranmerc.c
  dt_cc/trcyleqa/trcyleqa.c
  dt_cc/ups/ups.c
  dt_cc/usng/usng.c
  dt_cc/utm/utm.c
  engine/src/engine.c
  geotrans2/src/strndup.c
  geotrans2/src/strtoval.c
  )
set(lib_hdrs
  dt_cc/albers/albers.h
  dt_cc/azeq/azeq.h
  dt_cc/bng/bng.h
  dt_cc/bonne/bonne.h
  dt_cc/cassini/cassini.h
  dt_cc/cyleqa/cyleqa.h
  dt_cc/datum/datum.h
  dt_cc/eckert4/eckert4.h
  dt_cc/eckert6/eckert6.h
  dt_cc/ellipse/ellipse.h
  dt_cc/eqdcyl/eqdcyl.h
  dt_cc/gars/gars.h
  dt_cc/geocent/geocent.h
  dt_cc/geoid/geoid.h
  dt_cc/georef/georef.h
  dt_cc/gnomonic/gnomonic.h
  dt_cc/grinten/grinten.h
  dt_cc/lambert_1/lambert_1.h
  dt_cc/lambert_2/lambert_2.h
  dt_cc/loccart/loccart.h
  dt_cc/mercator/mercator.h
  dt_cc/mgrs/mgrs.h
  dt_cc/miller/miller.h
  dt_cc/mollweid/mollweid.h
  dt_cc/neys/neys.h
  dt_cc/nzmg/nzmg.h
  dt_cc/omerc/omerc.h
  dt_cc/orthogr/orthogr.h
  dt_cc/polarst/polarst.h
  dt_cc/polycon/polycon.h
  dt_cc/sinusoid/sinusoid.h
  dt_cc/stereogr/stereogr.h
  dt_cc/threads/threads.h
  dt_cc/tranmerc/tranmerc.h
  dt_cc/trcyleqa/trcyleqa.h
  dt_cc/ups/ups.h
  dt_cc/usng/usng.h
  dt_cc/utm/utm.h
  engine/src/engine.h
  geotrans2/src/comphack.h
  geotrans2/src/strndup.h
  geotrans2/src/strtoval.h
  )
set(geotrans2_data
  geotrans2/data/3_param.dat
  geotrans2/data/7_param.dat
  geotrans2/data/egm84.grd
  geotrans2/data/egm96.grd
  geotrans2/data/ellips.dat
  )
#######################################
add_library(${lib_name} STATIC ${lib_srcs})
target_include_directories(${lib_name} PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE dt_cc/albers dt_cc/azeq dt_cc/bng dt_cc/bonne dt_cc/cassini dt_cc/cyleqa
  dt_cc/datum dt_cc/eckert4 dt_cc/eckert6 dt_cc/ellipse dt_cc/eqdcyl
  dt_cc/gars dt_cc/geocent dt_cc/geoid dt_cc/georef dt_cc/gnomonic dt_cc/grinten
  dt_cc/lambert_1 dt_cc/lambert_2 dt_cc/loccart
  dt_cc/mercator dt_cc/mgrs dt_cc/miller dt_cc/mollweid
  dt_cc/neys dt_cc/nzmg dt_cc/omerc dt_cc/orthogr dt_cc/polarst dt_cc/polycon
  dt_cc/sinusoid dt_cc/stereogr dt_cc/threads dt_cc/tranmerc dt_cc/trcyleqa
  dt_cc/ups dt_cc/usng dt_cc/utm engine/src
  )
include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(NOT ${IS_BIG_ENDIAN})
  target_compile_definitions(${lib_name} PRIVATE LITTLE_ENDIAN)
endif()
if(MSVC)
  target_compile_definitions(${lib_name} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
#######################################
# install
set(targetsFile ${PROJECT_NAME}-targets)
install(TARGETS ${lib_name} EXPORT ${targetsFile}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
install(FILES ${${lib_name}_libhdrs} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
if(DEFINED CSV_DIR)
  file(GLOB csvFiles ${CSV_DIR}/*.csv ${CSV_DIR}/README)
endif()
install(FILES ${${lib_name}_data} ${csvFiles} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/data)
if(DEFINED XP_NAMESPACE)
  set(nameSpace NAMESPACE ${XP_NAMESPACE}::)
endif()
if(NOT DEFINED XP_INSTALL_CMAKEDIR)
  set(XP_INSTALL_CMAKEDIR ${CMAKE_INSTALL_DATADIR}/cmake)
endif()
install(EXPORT ${targetsFile} DESTINATION ${XP_INSTALL_CMAKEDIR} ${nameSpace})
