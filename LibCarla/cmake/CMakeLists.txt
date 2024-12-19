cmake_minimum_required(VERSION 3.5.1)
project(libcarla)

# 设置构建选项
option(LIBCARLA_BUILD_DEBUG "Build debug configuration" ON)
option(LIBCARLA_BUILD_RELEASE "Build release configuration" ON)
option(LIBCARLA_BUILD_TEST "Build unit tests" ON)

# 输出构建选项的状态
message(STATUS "Build debug:   ${LIBCARLA_BUILD_DEBUG}")
message(STATUS "Build release: ${LIBCARLA_BUILD_RELEASE}")
message(STATUS "Build test:    ${LIBCARLA_BUILD_TEST}")

# 设置源代码路径
set(libcarla_source_path "${PROJECT_SOURCE_DIR}/../source")
set(libcarla_source_thirdparty_path "${libcarla_source_path}/third-party")

# 包含源代码目录和第三方库目录
include_directories(${libcarla_source_path})
include_directories(${libcarla_source_thirdparty_path})

# 如果定义了CARLA_VERSION，则配置版本文件
if (CARLA_VERSION)
  configure_file(${libcarla_source_path}/carla/Version.h.in ${libcarla_source_path}/carla/Version.h)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Client")
  add_subdirectory("client")
elseif (CMAKE_BUILD_TYPE STREQUAL "Server")
  add_subdirectory("server")
elseif (CMAKE_BUILD_TYPE STREQUAL "Pytorch")
add_subdirectory("pytorch")
elseif (CMAKE_BUILD_TYPE STREQUAL "ros2")
add_subdirectory("fast_dds")
else ()
  message(FATAL_ERROR "Unknown build type '${CMAKE_BUILD_TYPE}'")
endif ()

# GTest is not compiled on Windows.
if ((LIBCARLA_BUILD_TEST) AND (NOT WIN32) AND (NOT (CMAKE_BUILD_TYPE STREQUAL "Pytorch")) AND (NOT (CMAKE_BUILD_TYPE STREQUAL "ros2")))
  add_subdirectory("test")
endif()
