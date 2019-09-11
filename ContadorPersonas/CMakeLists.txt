cmake_minimum_required(VERSION 2.8)

project(ContadorPersonas)
set(SOURCES funciones.cpp funciones.h global.h)

add_executable(${PROJECT_NAME} "main.cpp" ${SOURCES})

find_package( OpenCV REQUIRED )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

