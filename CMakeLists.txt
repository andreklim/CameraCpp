cmake_minimum_required(VERSION 2.8)
project( CameraRodina )
find_package( OpenCV REQUIRED )
add_executable( CameraRodina CameraRodina.cpp )
target_link_libraries( CameraRodina ${OpenCV_LIBS} )
