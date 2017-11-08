cmake_minimum_required(VERSION 3.0)
project(geotrans)
include(flags OPTIONAL)
set(lib_name ${PROJECT_NAME})
#######################################
# preprocessor
include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(NOT ${IS_BIG_ENDIAN})
  add_definitions(-DLITTLE_ENDIAN)
endif()
if(MSVC)
  add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
    )
endif()
#######################################
# include directories
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/albers
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/azeq
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/bng
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/bonne
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/cassini
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/cyleqa
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/datum
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/eckert4
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/eckert6
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/ellipse
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/eqdcyl
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/gars
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/geocent
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/geoid
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/georef
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/gnomonic
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/grinten
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/lambert_1
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/lambert_2
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/loccart
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/mercator
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/mgrs
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/miller
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/mollweid
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/neys
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/nzmg
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/omerc
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/orthogr
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/polarst
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/polycon
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/sinusoid
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/stereogr
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/threads
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/tranmerc
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/trcyleqa
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/ups
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/usng
  ${CMAKE_CURRENT_SOURCE_DIR}/dt_cc/utm
  ${CMAKE_CURRENT_SOURCE_DIR}/engine/src
  )
#######################################
# library sources
set(${lib_name}_libsrcs
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
set(${lib_name}_libhdrs
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
set(${lib_name}_data
  geotrans2/data/3_param.dat
  geotrans2/data/7_param.dat
  geotrans2/data/egm84.grd
  geotrans2/data/egm96.grd
  geotrans2/data/ellips.dat
  )
#######################################
# version
if(DEFINED GEOTRANS_VER)
  set(ver _${GEOTRANS_VER})
  set(verDir /${PROJECT_NAME}${ver})
endif()
#######################################
# library
add_library(${lib_name} STATIC ${${lib_name}_libsrcs})
set_target_properties(${lib_name} PROPERTIES OUTPUT_NAME ${lib_name}${ver})
#######################################
# install
set(targetsFile ${PROJECT_NAME}${ver}-targets)
install(TARGETS ${lib_name} EXPORT ${targetsFile}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
install(FILES ${${lib_name}_libhdrs} DESTINATION include${verDir}/${PROJECT_NAME})
if(DEFINED CSV_DIR)
  file(GLOB csvFiles ${CSV_DIR}/*.csv ${CSV_DIR}/README)
endif()
install(FILES ${${lib_name}_data} ${csvFiles} DESTINATION include${verDir}/${PROJECT_NAME}/data)
install(EXPORT ${targetsFile} DESTINATION lib/cmake)
