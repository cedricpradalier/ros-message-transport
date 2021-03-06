cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()
rosbuild_include(templated_transports templated_transports)


#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_library(LOG4CXX_LIBRARY log4cxx)

generate_plugin_description(SRC default_plugins_template.m4 OUTPUT default_plugins.xml)

rosbuild_add_boost_directories()
rosbuild_add_library(${PROJECT_NAME} src/decimated_publisher.cpp src/manifest.cpp)
rosbuild_link_boost(${PROJECT_NAME} system)

rosbuild_add_executable(list_transports src/list_transports.cpp)
target_link_libraries(list_transports ${PROJECT_NAME})

rosbuild_add_executable(test_publisher test/publisher.cpp)
target_link_libraries(test_publisher ${PROJECT_NAME} ${LOG4CXX_LIBRARY})

rosbuild_add_executable(test_receiver test/receiver.cpp)
target_link_libraries(test_receiver ${PROJECT_NAME} ${LOG4CXX_LIBRARY})

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})
