cmake_minimum_required(VERSION 2.8.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/libmodplug-master/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/sqlite/CMakeLists.txt)

project(ModExtractor)

include_directories(AFTER
  libmodplug-master/src
  libmodplug-master/src/cppwrap
  ) 

add_executable(ModExtractor
	ModExtractor.cpp
  )
  
target_link_libraries(ModExtractor modplug)