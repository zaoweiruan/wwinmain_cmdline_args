cmake_minimum_required (VERSION 3.30)
set(CMAKE_VERBOSE_MAKEFILEON ON)

project (wwinmain_cmdline_args)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

add_library(boost_algorithm_lib INTERFACE)
# 添加头文件所在目录（相对路径或绝对路径）
target_include_directories(boost_algorithm_lib INTERFACE
    "D:/boost_1_88_0"  # 库的头文件所在目录
)

#add_definitions(-D_MSC_VER)
#add_definitions(-DBOOST_ALL_STATIC_LINK)

find_package(Boost  CONFIG REQUIRED  program_options )
add_executable(search_excel)


set_target_properties(search_excel PROPERTIES SOURCES "${PROJECT_SOURCE_DIR}/src/wwinmain_cmdline_args.cpp")
set_target_properties(search_excel PROPERTIES OUTPUT_NAME "win_program_options")

set_target_properties(search_excel PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
target_link_libraries(search_excel   Boost::program_options user32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -std=c++17 -g -Wall  -O2 -mconsole -municode ")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -std=c++17 -g -Wall  -O2 -mwindows -municode ")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -std=c++17 -g -Wall  -O2 ")
