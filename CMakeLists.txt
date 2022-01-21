# Cmake minimum required version
cmake_minimum_required (VERSION 3.15)

# Project name
project (adsb-sim)

# Required C++ Standard
set (CMAKE_CXX_STANDARD 17)

find_package (Threads REQUIRED)

# set sources
file (GLOB_RECURSE SOURCES "src/*.cpp")

# set header files
file (GLOB_RECURSE HEADERS "src/*.h")

#Copy resources
file(COPY "${PROJECT_SOURCE_DIR}/res/"
     DESTINATION "${CMAKE_BINARY_DIR}/res/")

# Executable to be build and source files required
add_executable (${PROJECT_NAME} ${SOURCES} ${HEADERS})
# target_include_directories (${PROJECT_NAME} PRIVATE ${FCGI_SIGNS_INCLUDES})
target_link_libraries (${PROJECT_NAME} Threads::Threads)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
