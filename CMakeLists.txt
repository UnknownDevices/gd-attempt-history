cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)

# TODO: set intermediary output directories too??
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin/min_size_rel)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin/min_size_rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin/min_size_rel)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin/rel_with_deb_info)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin/rel_with_deb_info)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin/rel_with_deb_info) 

project(gd-attempt-history)

list(APPEND GDAT_C_FILES
  #*.cpp
  src/level.cpp
  src/player.cpp
  src/session.cpp
  src/dllmain.cpp
)

add_library(${PROJECT_NAME} SHARED ${GDAT_C_FILES})

# this is so stupid
set(CMAKE_SIZEOF_VOID_P 4)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  # ensure 32 bit on clang
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target i386-pc-windows-msvc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target i386-pc-windows-msvc")
  add_definitions("--target=i386-pc-windows-msvc")
endif()

target_precompile_headers(${PROJECT_NAME}
  PRIVATE
  src/pch.hpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  vendor/minhook/include
  vendor/gd.h/include
  vendor/gd.h/
  vendor/flatbuffers/include
  src
)

# EXCLUDE_FROM_ALL flag used so target is excluded from installation
add_subdirectory(vendor/minhook EXCLUDE_FROM_ALL)
add_subdirectory(vendor/cocos-headers)
add_subdirectory(vendor/flatbuffers
                 ${CMAKE_CURRENT_BINARY_DIR}/flatbuffers-build
                 EXCLUDE_FROM_ALL)
 
target_link_libraries(${PROJECT_NAME} PRIVATE minhook cocos2d flatbuffers)

install(TARGETS "${PROJECT_NAME}"
  DESTINATION "C:/Program Files (x86)/Steam/steamapps/common/Geometry Dash/mods" 
  CONFIGURATIONS RELEASE)