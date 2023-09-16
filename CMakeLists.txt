cmake_minimum_required(VERSION 3.26)
project(cpp_study)

set(CMAKE_CXX_STANDARD 17)


## 这里没使用安装的方式，因此注释掉，为了完整性，添加到这里
##include_directories(/home/ubuntu/work/usr/include)
##link_directories(/home/ubuntu/work/usr/lib)# 查找opencv的path
#set(OpenCV_DIR "F:/Program Files/opencv/build" CACHE PATH "OPENCV directory override" FORCE)
##D:/opencv/build目录包含OpenCVConfig.cmake
## 寻找OpenCV库
#find_package(OpenCV REQUIRED)
## 打印opencv的相关信息
##message(STATUS "OpenCV library status:")
##message(STATUS "    version: ${OpenCV_VERSION}")
##message(STATUS "    libraries: ${OpenCV_LIBS}")
##message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")# 添加子目录，该目录为库目录,会调用子目录的cmake文件，进行构建库
#add_subdirectory(src)
## 构建可执行文件
##add_executable(main main.cpp)# 添加链接库
#add_executable(cpp_study main.cpp)
#
## 把子目录src的编译成的动态库文件链接到这里
#target_link_libraries(main mylib ${OpenCV_LIBS})
## 把子目录src编译成的静态库链接到这里
## target_link_libraries(main libmylib.a)
## target_link_libraries(main PRIVATE ${OpenCV_LIBS})
## target_link_libraries(main PRIVATE ${OpenCV_LIBS})


#set(OpenCV_DIR "F:/Program Files/opencv/build" CACHE PATH "OPENCV directory override" FORCE)
##D:/opencv/build目录包含OpenCVConfig.cmake
## 寻找OpenCV库
#find_package(OpenCV REQUIRED)
#target_link_libraries(
#        PRIVATE ${OpenCV_LIBS}
#)
#
## 添加头文件
#include_directories(${OpenCV_INCLUDE_DIRS})
#
##.exe下的可执行文件包含使用到的dll
#
##file(COPY "${OpenCV_DIR}/bin/debug/opencv_world460d.dll" DESTINATION "${PROJECT_OUTPUT_DIR}/debug")
##file(COPY "${OpenCV_DIR}/bin/debug/opencv_world460d.dll" DESTINATION "${PROJECT_OUTPUT_DIR}/release")
##file(COPY "${OpenCV_DIR}/bin/debug/opencv_core460d.dll" DESTINATION "${PROJECT_OUTPUT_DIR}/debug")
##file(COPY "${OpenCV_DIR}/bin/debug/opencv_core460d.dll" DESTINATION "${PROJECT_OUTPUT_DIR}/release")
##file(COPY "${OpenCV_DIR}/bin/debug/opencv_imgproc460d.dll" DESTINATION "${PROJECT_OUTPUT_DIR}/debug")
##file(COPY "${OpenCV_DIR}/bin/debug/opencv_imgproc460d.dll" DESTINATION "${PROJECT_OUTPUT_DIR}/release")
##file(COPY "${OpenCV_DIR}/bin/debug/opencv_imgcodecs460d.dll" DESTINATION "${PROJECT_OUTPUT_DIR}/debug")
##file(COPY "${OpenCV_DIR}/bin/debug/opencv_imgcodecs460d.dll" DESTINATION "${PROJECT_OUTPUT_DIR}/release")
##file(COPY "${OpenCV_DIR}/bin/debug/opencv_videoio460d.dll" DESTINATION "${PROJECT_OUTPUT_DIR}/debug")
##file(COPY "${OpenCV_DIR}/bin/debug/opencv_videoio460d.dll" DESTINATION "${PROJECT_OUTPUT_DIR}/release")

#add_executable(cpp_study main.cpp)



#
##set(OpenCV_DIR "F:\\Program Files\\opencv\\build")
#set(OpenCV_DIR "F:\\Program Files\\opencv\\build\\x64\\vc15\\lib")
##设置链接库路径
#set(LINK_DIR "F:\\Program Files\\opencv\\build\\x64\\vc15\\bin")
##引入库文件
#link_directories(${LINK_DIR})
#
##find_package(OpenCV REQUIRED core imgproc highgui)
#find_package(OpenCV)
#
#
##add_executable(your_target_name your_source_files.cpp)
#add_executable(cpp_study main.cpp)
#
#
## 打印opencv的相关信息
#message(STATUS "OpenCV library status:")
#message(STATUS "    config: ${OpenCV_DIR}")
#message(STATUS "    version: ${OpenCV_VERSION}")
#message(STATUS "    libraries: ${OpenCV_LIBS}")
#message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")# 添加子目录，该目录为库目录,会调用子目录的cmake文件，进行构建库
#
#message(STATUS "Torch library status:")
#message(STATUS " include_path: ${TORCH_INCLUDE_DIRS}")
#message(STATUS " TORCHLIB: ${TORCH_LIBRARIES}")
#
#include_directories(${OpenCV_INCLUDE_DIRS})
##target_link_libraries(
##        PRIVATE ${OpenCV_LIBS}
##)
#target_link_libraries(cpp_study ${OpenCV_LIBS})
#target_link_libraries(cpp_study opencv_world460 opencv_world460d)



#设置头文件路径
set(INC_DIR ./include)
#设置链接库路径
set(LINK_DIR ./lib)
#引入头文件
include_directories(${INC_DIR})
#引入库文件
link_directories(${LINK_DIR})


add_executable(cpp_study main.cpp)


#将第三方库连接在一起
target_link_libraries(cpp_study libleveldb.a)

