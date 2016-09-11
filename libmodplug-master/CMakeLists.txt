cmake_minimum_required(VERSION 2.8.0)

project(libmodplug)
add_definitions(-DMODPLUG_BUILD)

include (CheckFunctionExists)

include_directories(AFTER
  libmodplug-master/src
  libmodplug-master/src/libmodplug
  ${PROJECT_BINARY_DIR}
  )

if (WIN32)
  add_definitions(-D_USE_MATH_DEFINES)
  add_definitions(-DNOMINMAX)
endif()

if (WIN32 AND NOT (MINGW OR MSYS))
  set(MSINTTYPES_PATH "$ENV{MSINTTYPES_PATH}" CACHE PATH "search path for inttypes.h and stdint.h")

  find_path(STDINT_INCLUDE_DIR
    stdint.h
    PATHS
    ${MSINTTYPES_PATH})

  if (STDINT_INCLUDE_DIR)
    add_definitions(-DHAVE_STDINT_H)
    include_directories(AFTER "${STDINT_INCLUDE_DIR}")
  endif()

  find_path(INTTYPES_INCLUDE_DIR
    inttypes.h
    PATHS
    ${MSINTTYPES_PATH})

  if (INTTYPES_INCLUDE_DIR)
    add_definitions(-DHAVE_INTTYPES_H)
    include_directories(AFTER "${INTTYPES_INCLUDE_DIR}")
  endif()

  if (NOT STDINT_INCLUDE_DIR OR NOT INTTYPES_INCLUDE_DIR)
    message(WARNING
      "Compilation may fail if inttypes.h is not natively supported by the compiler."
      "You can get inttypes.h from http://code.google.com/p/msinttypes/")
  endif()
endif()

check_function_exists("setenv" HAVE_SETENV)
check_function_exists("sinf" HAVE_SINF)

# Allow the developer to select if Dynamic or Static libraries are built
option(BUILD_SHARED_LIBS "Build Shared Library (DLL)" OFF)

# Set the LIB_TYPE variable to STATIC
set(LIB_TYPE STATIC)

if (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries,
  # so change the LIB_TYPE variable to CMake keyword 'SHARED'
  set (LIB_TYPE SHARED)
  add_definitions(-DDLL_EXPORT)
else (BUILD_SHARED_LIBS)
  add_definitions(-DMODPLUG_STATIC)
endif (BUILD_SHARED_LIBS)

add_library(modplug ${LIB_TYPE}
  libmodplug-master/src/libmodplug/it_defs.h
  libmodplug-master/src/libmodplug/sndfile.h
  libmodplug-master/src/libmodplug/stdafx.h

  libmodplug-master/src/fastmix.cpp
  libmodplug-master/src/load_669.cpp
  libmodplug-master/src/load_abc.cpp
  libmodplug-master/src/load_amf.cpp
  libmodplug-master/src/load_ams.cpp
  libmodplug-master/src/load_dbm.cpp
  libmodplug-master/src/load_dmf.cpp
  libmodplug-master/src/load_dsm.cpp
  libmodplug-master/src/load_far.cpp
  libmodplug-master/src/load_it.cpp
  libmodplug-master/src/load_j2b.cpp
  libmodplug-master/src/load_mdl.cpp
  libmodplug-master/src/load_med.cpp
  libmodplug-master/src/load_mid.cpp
  libmodplug-master/src/load_mod.cpp
  libmodplug-master/src/load_mt2.cpp
  libmodplug-master/src/load_mtm.cpp
  libmodplug-master/src/load_okt.cpp
  libmodplug-master/src/load_pat.cpp
  libmodplug-master/src/load_pat.h
  libmodplug-master/src/load_psm.cpp
  libmodplug-master/src/load_ptm.cpp
  libmodplug-master/src/load_s3m.cpp
  libmodplug-master/src/load_stm.cpp
  libmodplug-master/src/load_ult.cpp
  libmodplug-master/src/load_umx.cpp
  libmodplug-master/src/load_wav.cpp
  libmodplug-master/src/load_xm.cpp
  libmodplug-master/src/mmcmp.cpp
  libmodplug-master/src/modplug.cpp
  libmodplug-master/src/modplug.h
  libmodplug-master/src/snd_dsp.cpp
  libmodplug-master/src/snd_flt.cpp
  libmodplug-master/src/snd_fx.cpp
  libmodplug-master/src/sndfile.cpp
  libmodplug-master/src/sndmix.cpp
  libmodplug-master/src/tables.h
  
  libmodplug-master/src/cppWrap/Channel.h
  libmodplug-master/src/cppWrap/Channel.cpp
  libmodplug-master/src/cppWrap/Note.h
  libmodplug-master/src/cppWrap/Note.cpp
  libmodplug-master/src/cppWrap/Sample.h
  libmodplug-master/src/cppWrap/Sample.cpp
  libmodplug-master/src/cppWrap/SoundFile.h
  libmodplug-master/src/cppWrap/SoundFile.cpp
  libmodplug-master/src/cppWrap/Instrument.h
  libmodplug-master/src/cppWrap/Instrument.cpp
  )

# install the library:
install(TARGETS modplug DESTINATION lib)

# incstall the headers:
install(FILES
  libmodplug-master/src/libmodplug/it_defs.h
  libmodplug-master/src/libmodplug/sndfile.h
  libmodplug-master/src/libmodplug/stdafx.h
  libmodplug-master/src/modplug.h

  DESTINATION
  include/libmodplug
  )

set(VERSION "0.8.8.5")

if(HAVE_SETENV)
  add_definitions(-DHAVE_SETENV)
endif(HAVE_SETENV)
if(HAVE_SINF)
  add_definitions(-DHAVE_SINF)
endif(HAVE_SINF)

if (NOT WIN32)
  set(prefix "${CMAKE_INSTALL_PREFIX}")
  set(exec_prefix "${CMAKE_INSTALL_PREFIX}")
  set(libdir "${CMAKE_INSTALL_PREFIX}/lib")
  set(includedir "${CMAKE_INSTALL_PREFIX}/include")
  configure_file(libmodplug.pc.in libmodplug.pc)

  # install pkg-config file:
  install(FILES "${PROJECT_BINARY_DIR}/libmodplug.pc"
    DESTINATION lib/pkgconfig
  )
endif (NOT WIN32)
