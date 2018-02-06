cmake_minimum_required (VERSION 2.8.11)

project("SplineEditor")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# set(CMAKE_EXE_LINKER_FLAGS "-static")
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -O3 ")
endif()

set (SRC src)
set (lib_src ${SRC}/knot.cpp
            ${SRC}/mainwindow.cpp
            ${SRC}/model.cpp
            ${SRC}/polylinearea.cpp
            ${SRC}/polylineeditor.cpp
            ${SRC}/utils.cpp
            ${SRC}/Mark.cpp
            ${SRC}/Line.cpp
)

set (lib_hdr ${SRC}/knot.h
            ${SRC}/mainwindow.h
            ${SRC}/model.h
            ${SRC}/polylinearea.h
            ${SRC}/polylineeditor.h
            ${SRC}/utils.h
            ${SRC}/Mark.hpp
            ${SRC}/Line.hpp
            ${SRC}/SplineMark.hpp
            ${SRC}/Spline.hpp
            ${SRC}/SplineSegment.hpp
)

set (lib_ui  ${SRC}/mainwindow.ui)
set (bin_src ${SRC}/main.cpp)

find_package (Qt5Widgets REQUIRED)
find_package (Qt5OpenGL  REQUIRED)
find_package (glRender 0.10.4 REQUIRED)

qt5_wrap_cpp(lib_hdr_moc ${lib_hdr})
qt5_wrap_ui (lib_ui_moc  ${lib_ui})

include_directories (
    ${SRC}
    ${GLRENDER_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_library (Lib SHARED
    ${lib_src}
    ${lib_hdr_moc}
    ${lib_ui_moc})

target_link_libraries (Lib
    Qt5::Widgets
    Qt5::OpenGL
    ${GLRENDER_LIBRARIES}
    gcc_s
    gcc
)

set_target_properties(Lib
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs"
)

add_executable(SplineEditor ${bin_src})
target_link_libraries (SplineEditor Lib)

add_custom_command(TARGET SplineEditor 
    PRE_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/libs/"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different $<TARGET_FILE:Qt5::OpenGL>  "${CMAKE_CURRENT_BINARY_DIR}/libs/"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different $<TARGET_FILE:Qt5::Widgets> "${CMAKE_CURRENT_BINARY_DIR}/libs/"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different $<TARGET_FILE:Qt5::Gui>  "${CMAKE_CURRENT_BINARY_DIR}/libs/"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different $<TARGET_FILE:Qt5::Core>  "${CMAKE_CURRENT_BINARY_DIR}/libs/"
)

file(COPY "data"       DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "bin/run.sh" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")