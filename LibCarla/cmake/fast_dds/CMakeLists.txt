cmake_minimum_required(VERSION 3.5.1)
project(libcarla_fastdds)

# Install headers.

# 安装头文件
# 使用file(GLOB)命令收集指定路径下的所有.h文件
file(GLOB libcarla_carla_fastdds_headers
  "${libcarla_source_path}/carla/ros2/publishers/*.h"
  "${libcarla_source_path}/carla/ros2/subscribers/*.h"
  "${libcarla_source_path}/carla/ros2/listeners/*.h"
  "${libcarla_source_path}/carla/ros2/types/*.h"
  )
  # 将收集到的头文件安装到指定目录下
install(FILES ${libcarla_carla_fastdds_headers} DESTINATION include/carla/ros2)

# 收集Fast DDS库文件
# 使用file(GLOB)命令收集指定路径下的所有.so文件（动态链接库）
file(GLOB fast_dds_dependencies "${FASTDDS_LIB_PATH}/*.so*")
# 将收集到的Fast DDS库文件安装到指定目录下
install(FILES ${fast_dds_dependencies} DESTINATION lib)


file(GLOB libcarla_fastdds_sources
  "${libcarla_source_path}/carla/ros2/publishers/*.cpp"
  "${libcarla_source_path}/carla/ros2/subscribers/*.cpp"
  "${libcarla_source_path}/carla/ros2/listeners/*.cpp"
  "${libcarla_source_path}/carla/ros2/types/*.cpp")

set(FASTDDS_CPP_STD_INCLUDES "/usr/include/c++/7")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fPIC -D_GLIBCXX_USE_CXX11_ABI=0 -I${FASTDDS_CPP_STD_INCLUDES}" CACHE STRING "" FORCE)

# ==============================================================================
# Create targets for debug and release in the same build type.
# ==============================================================================

# 如果启用了发布构建模式
if (LIBCARLA_BUILD_RELEASE)
# 添加静态库 carla_fastdds
  add_library(carla_fastdds STATIC ${libcarla_fastdds_sources})

# 包含Boost和RPCLib的头文件目录
  target_include_directories(carla_fastdds SYSTEM PRIVATE
      "${BOOST_INCLUDE_PATH}"
      "${RPCLIB_INCLUDE_PATH}")

# 包含Fast DDS和libcarla_ros2的头文件目录
  target_include_directories(carla_fastdds PRIVATE "${FASTDDS_INCLUDE_PATH}")
  target_include_directories(carla_fastdds PRIVATE "${libcarla_source_path}/carla/ros2")
  # 链接Fast DDS库
  target_link_libraries(carla_fastdds fastrtps fastcdr "${FAST_DDS_LIBRARIES}")
  # 安装静态库到 lib 目录
  install(TARGETS carla_fastdds DESTINATION lib)
  # 设置编译标志为发布模式
  set_target_properties(carla_fastdds PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}")

endif()

# 如果启用了调试构建模式
if (LIBCARLA_BUILD_DEBUG)

# 添加静态库 carla_fastdds_debug
  add_library(carla_fastdds_debug STATIC ${libcarla_fastdds_sources})
  # 包含Boost和RPCLib的头文件目录
 target_include_directories(carla_fastdds_debug SYSTEM PRIVATE
      "${BOOST_INCLUDE_PATH}"
      "${RPCLIB_INCLUDE_PATH}")
      # 安装静态库到 lib 目录
  install(TARGETS carla_fastdds_debug DESTINATION lib)
  # 设置编译标志为调试模式
  set_target_properties(carla_fastdds_debug PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")
  # 添加调试宏定义
  target_compile_definitions(carla_fastdds_debug PUBLIC -DBOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

endif()
