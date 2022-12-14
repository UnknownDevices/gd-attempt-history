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

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "vcpkg toolchain file")

set(SPDLOG_USE_STD_FORMAT ON)
set(SPDLOG_DISABLE_DEFAULT_LOGGER ON)

project(gd-attempt-history)

find_package(magic_enum CONFIG REQUIRED)
find_package(flatbuffers CONFIG REQUIRED)

list(APPEND GDAT_C_FILES
  #*.cpp
  src/level.cpp
  src/player.cpp
  src/session.cpp
  src/dllmain.cpp
)

list(APPEND GDAT_H_FILES
  #*.hpp
)

add_library(${PROJECT_NAME} SHARED ${GDAT_C_FILES} ${GDAT_H_FILES})

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
  vendor/gd.h/include
  vendor/minhook/include
  vendor/spdlog/include/spdlog
  vendor/gd.h
  src
)

add_subdirectory(vendor/cocos-headers)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/minhook EXCLUDE_FROM_ALL)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog minhook magic_enum::magic_enum cocos2d     
  flatbuffers::flatbuffers)

install(TARGETS "${PROJECT_NAME}"
  DESTINATION "C:/Program Files (x86)/Steam/steamapps/common/Geometry Dash/mods" 
  CONFIGURATIONS RELEASE)