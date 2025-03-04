cmake_minimum_required(VERSION 3.10)
project(RpiWaylandEglTest C)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(BINNAME rpi-wayland-egl-test)

# Add the source file
add_executable(${BINNAME} rpi-wayland-egl-test.c)

# Find the required packages
find_package(Wayland REQUIRED)
find_package(EGL REQUIRED)
find_package(OpenGL REQUIRED)

# Include directories and link libraries
include_directories(${WAYLAND_INCLUDE_DIRS} ${EGL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${BINNAME} ${WAYLAND_LIBRARIES} ${EGL_LIBRARIES} ${OPENGL_LIBRARIES})
