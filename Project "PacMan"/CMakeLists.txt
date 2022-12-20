cmake_minimum_required(VERSION 3.17)
project(Please_God_work)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(Please_God_work Source.cpp)

set(SFML_DIR "C:\\msys64\\home\\User\\Please_God_work\\SFML\\include\\SFML")

target_link_libraries(Please_God_work sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)