#wersja cmake
cmake_minimum_required(VERSION 3.28)

project(algorSortowanie) #Poj name

#wersja c++
set(CMAKE_CXX_STANDARD 17)

# // Source - https://stackoverflow.com/q/41361631
# // Posted by marmistrz, modified by community. See post 'Timeline' for change history
# // Retrieved 2026-05-10, License - CC BY-SA 3.0

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#optymalizacja -O0, -O1, -O2, -O3
set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

# // end Source


#wszystko w src
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
# add_compile_options()

#dodaj inc do headers
target_include_directories(${PROJECT_NAME} PRIVATE inc )