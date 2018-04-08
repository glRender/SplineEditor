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
set (lib_headers_with_qt
                 ${SRC}/Views/forms/ViewSplineEditor.hpp
                 ${SRC}/Views/forms/KnotParamsWidget.h
                 ${SRC}/Models/ModelSpline.hpp
                 ${SRC}/Models/ModelKnot.hpp
                 ${SRC}/Views/ViewSplineArea.hpp
                 ${SRC}/Models/ModelSplineEditor.hpp)

set (lib_headers
                 ${SRC}/Views/ViewKnot.hpp
                 ${SRC}/Views/ViewSpline.hpp
                 ${SRC}/Views/ViewSegment.hpp
                 ${SRC}/Views/CameraControl.hpp
                 ${SRC}/Views/ViewLine.hpp
                 ${SRC}/Utils/utils.h
                 ${SRC}/Utils/Result.hpp)

set (lib_sources ${SRC}/Views/forms/ViewSplineEditor.cpp
                 ${SRC}/Views/forms/KnotParamsWidget.cpp
                 ${SRC}/Views/ViewSplineArea.cpp
                 ${SRC}/Views/ViewKnot.cpp
                 ${SRC}/Views/ViewSpline.cpp
                 ${SRC}/Views/ViewSegment.cpp
                 ${SRC}/Views/CameraControl.cpp
                 ${SRC}/Views/ViewLine.cpp
                 ${SRC}/Models/ModelKnot.cpp
                 ${SRC}/Models/ModelSpline.cpp
                 ${SRC}/Models/ModelSplineEditor.cpp
                 ${SRC}/Utils/utils.cpp
)

set (lib_ui
                 ${SRC}/Views/forms/ViewSplineEditor.ui
                 ${SRC}/Views/forms/KnotParamsWidget.ui
)

set (bin_src ${SRC}/main.cpp)

set (RESOURCES
    resources/resources.qrc
)

find_package (Qt5Widgets REQUIRED)
find_package (Qt5OpenGL  REQUIRED)
find_package (glRender 0.10.4 REQUIRED)

qt5_add_resources(lib_resources ${RESOURCES})
qt5_wrap_cpp(lib_headers_moc ${lib_headers_with_qt})
qt5_wrap_ui (lib_ui_moc  ${lib_ui})

include_directories (
    ${SRC}
    ${SRC}/Utils
    ${SRC}/Models
    ${SRC}/Views
    ${SRC}/Controllers
    ${SRC}/Views/forms
    ${GLRENDER_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_library (Lib SHARED
    ${lib_headers}
    ${lib_headers_with_qt}
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
