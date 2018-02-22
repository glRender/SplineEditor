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
set (lib_headers ${SRC}/View/forms/mainwindow.h
                 ${SRC}/View/polylinearea.h
                 ${SRC}/View/CameraControl.hpp
                 ${SRC}/View/LineView.hpp
                 ${SRC}/View/SplineMarkView.hpp
                 ${SRC}/View/SplineView.hpp
                 ${SRC}/View/SplineSegmentView.hpp
                 ${SRC}/Model/EditorModeMachine.hpp
                 ${SRC}/Model/utils.h
                 ${SRC}/Model/SplineModel.hpp
                 ${SRC}/Model/KnotModel.hpp
                 ${SRC}/Model/Result.hpp
                 ${SRC}/polylineeditor.h
)

set (lib_sources ${SRC}/View/forms/mainwindow.cpp
                 ${SRC}/View/polylinearea.cpp
                 ${SRC}/View/SplineMarkView.cpp
                 ${SRC}/View/CameraControl.cpp
                 ${SRC}/View/LineView.cpp
                 ${SRC}/Model/EditorModeMachine.cpp
                 ${SRC}/Model/utils.cpp
                 ${SRC}/Model/KnotModel.cpp
                 ${SRC}/Model/SplineModel.cpp
                 ${SRC}/polylineeditor.cpp
)

set (lib_ui  ${SRC}/View/forms/mainwindow.ui)
set (bin_src ${SRC}/main.cpp)

set (RESOURCES
    resources/resources.qrc
)

find_package (Qt5Widgets REQUIRED)
find_package (Qt5OpenGL  REQUIRED)
find_package (glRender 0.10.4 REQUIRED)

qt5_add_resources(lib_resources ${RESOURCES})
qt5_wrap_cpp(lib_headers_moc ${lib_headers})
qt5_wrap_ui (lib_ui_moc  ${lib_ui})

include_directories (
    ${SRC}
    ${SRC}/Model
    ${SRC}/View
    ${SRC}/View/forms
    ${GLRENDER_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_library (Lib SHARED
    ${lib_headers}
    ${lib_sources}
    ${lib_headers_moc}
    ${lib_ui_moc}
    ${lib_resources}
)

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
