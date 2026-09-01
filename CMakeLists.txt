cmake_minimum_required(VERSION 4.3)
project(geotranz)
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
set(csvFile
  compd_cs.csv
  ellips_alias.csv
  ellipsoid.csv
  gdatum_alias.csv
  geod_datum.csv
  geod_trf.csv
  geoparms.csv
  horiz_cs.csv
  p_meridian.csv
  README
  trf_method.csv
  trf_nonpolynomial.csv
  trf_path.csv
  uom_an_alias.csv
  uom_angle.csv
  uom_le_alias.csv
  uom_length.csv
  uom_sc_alias.csv
  uom_scale.csv
  vert_cs.csv
  vert_datum.csv
  vert_offset.csv
  )
set(csvHash
  e864bcf77b50d496462752b7125917012dc42aa9e324b2f6ad75a3be1ecb8a23 # compd_cs.csv
  822718e72afda2997001df2682bf2a280ab2c903f2fac58ed3395eca053cc5d7 # ellips_alias.csv
  79c56197f845cde7b48439e6f6729bea226b7a4b79d1149ecad598c051f6e4c3 # ellipsoid.csv
  edd91c21ff1a9881ccbb3525a1364e4d9f5277db97b5db6b5e45cc088cdad4fd # gdatum_alias.csv
  fab5fbdb43ee8622c3b026fd09898a3fb2a1458e96175ffcc86b4c1101b17e62 # geod_datum.csv
  18b19ef2027976c342f3da7fe3dbddacbe428d1d51674c5b7f11940789d4eb3f # geod_trf.csv
  a2f2db84b5abe4a792b4067eb09769aaa161e53a902643ecdf8ec3447a4b3206 # geoparms.csv
  7ab954e37524841eaee5fff1f959828e866ce46e9fef63719a3676cff31a32c8 # horiz_cs.csv
  27d31bb09981885a2260a7b109f46ff2ef376bec2387c37be492ba7834356dbc # p_meridian.csv
  a505aa154f0b97894169f145758f0b83f411df54f4d6e780efb3165fe493d78f # README
  d93ba4b6698ae0bffcdf0e1764365c2cf6270248fafb77b922a305adef8d0650 # trf_method.csv
  d8bc9c824082005a87aec9c67200bc74a03c04ff23caf145563ca0f5cf706ec2 # trf_nonpolynomial.csv
  9b826a4473a8c5e113113471b7db46a663b996b30b0539442002e5b26841ec53 # trf_path.csv
  057b902f3deeb872a57afbca6735f1b568833b06cb4c8f4dd52624d4d331312c # uom_an_alias.csv
  fd512ecbd57849ac8861036f405e6ca260ff7cca52cb80f9bc3ab3da8abe89c4 # uom_angle.csv
  d8022e511e71e5fa0085c65ed9c5b662011885892fad8d11d9deb7e53474fb6c # uom_le_alias.csv
  f127eef53fa2a0c84ef14a011dc47d9dec39636a0b3fee5caacb56e13c8051ec # uom_length.csv
  754e73db5da4b9aeb9bbaf9302077aaef4c2be87b21f6400c9319e4ffd89a185 # uom_sc_alias.csv
  00c828023048202c5bea870e8cd7010acccd926e6c2783ca303482d52afb39bf # uom_scale.csv
  699aa9509859369e7ad751e244b6d434f3da962fd3933d5803e8d02cec3c1910 # vert_cs.csv
  a95621fccd7ae6241b923360d39f00aef12a504e319999b7014e3f623bcedc2e # vert_datum.csv
  e0484d12600fb9b497a4f94ad654f4e99c89f1f5f9a180749ad4d8dd9d5eedbc # vert_offset.csv
  )
set(csvUrl https://download.osgeo.org/geotiff/tables)
set(csvDir ${CMAKE_CURRENT_BINARY_DIR}/csv)
foreach(file hash IN ZIP_LISTS csvFile csvHash)
  file(DOWNLOAD ${csvUrl}/${file} ${csvDir}/${file} EXPECTED_HASH SHA256=${hash} SHOW_PROGRESS)
endforeach()
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
set(targetsFile ${PROJECT_NAME}-targets)
if(COMMAND xpExternPackage)
  string(TOUPPER ${PROJECT_NAME} PRJ)
  string(JOIN "\n" EXT3
    "get_target_property(incDir ${PROJECT_NAME}::${lib_name} INTERFACE_INCLUDE_DIRECTORIES)"
    "set(${PRJ}_DATA_DIR \${incDir}/${PROJECT_NAME}/data)"
    "list(APPEND reqVars ${PRJ}_DATA_DIR)"
    ""
    )
  xpExternPackage(TARGETS_FILE ${targetsFile}
    LIBRARIES ${lib_name} DEFAULT_TARGETS ${lib_name}
    BASE v2.4.2 XPDIFF "intro"
    WEB "https://earth-info.nga.mil"
    DESC "geographic translator (convert coordinates)"
    LICENSE "[LicenseRef-NGA-GEOTRANS-Terms-Of-Use](https://github.com/externpro/geotranz/blob/xpro/readme.txt 'GEOTRANS Terms of Use')"
    ATTRIBUTION "The product was developed using GEOTRANS, a product of the National Geospatial-Intelligence Agency (NGA) and U.S. Army Engineering Research and Development Center."
    )
elseif(NOT DEFINED CMAKE_INSTALL_CMAKEDIR)
  set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_DATADIR}/cmake)
endif()
install(TARGETS ${lib_name} EXPORT ${targetsFile}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
install(FILES ${lib_hdrs} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
list(TRANSFORM csvFile PREPEND ${csvDir}/)
install(FILES ${geotrans2_data} ${csvFile} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/data)
install(EXPORT ${targetsFile} DESTINATION ${CMAKE_INSTALL_CMAKEDIR} NAMESPACE ${PROJECT_NAME}::)
