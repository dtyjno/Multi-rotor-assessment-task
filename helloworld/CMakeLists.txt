#指定运行此配置文件所需的 CMake 的最低版本。
cmake_minimum_required(VERSION 3.0.0)
#设置项目的名称，同时会自动生成 PROJECT_NAME 变量，
#使用 ${PROJECT_NAME} 即可访问到 hello_cmake。
project(hello_cmake)

#设置c++标准为c++11
set(CMAKE_CXX_STANDARD 11)

#include(CTest)
# 启用测试
#enable_testing()

# 构建一个 CPack 安装包
#include (InstallRequiredSystemLibraries)
#set (CPACK_RESOURCE_FILE_LICENSE
#  "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
#set (CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
#set (CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
#include(CPack)

#-----------------------------------

# 查找目录下的所有源文件,并将名称保存到 DIR_SRCS 变量
#aux_source_directory(. DIR_SRCS)
#--
#set(DIR_SRCS
#    usehello.cpp
#    libHelloWorld.cpp
#)

#=======================
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
#aux_source_directory(. DIR_LIB_SRCS)

# 指定生成 MathFunctions 链接库
#add_library (printhello ${DIR_LIB_SRCS})
# 添加 hello 子目录
#add_subdirectory(hello)
#=======================

# 指定生成 MathFunctions 链接库
add_library (printhello libHelloWorld.cpp)

#一个参数是可执行文件名，第二个参数是要编译的源文件列表。这里将名为 main.cpp 的源文件编译成一个名称为 hello_cmake 的可执行文件。
add_executable(Demo useHello.cpp)
# 添加链接库
target_link_libraries(Demo printhello)

#------------------------------------
# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
#aux_source_directory(. DIR_SRCS)

# 指定生成目标
#add_executable(${PROJECT_NAME} ${DIR_SRCS})