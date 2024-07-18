cmake_minimum_required(VERSION 3.13)
project(FrogSockLib)

set(FrogSocketLib_VERSION_MAJOR 1)
set(FrogSocketLib_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(FrogSockLib SHARED
    src/Socket.cpp
    # Sources to cpp files
)

target_include_directories(FrogSockLib PUBLIC ${PROJECT_SOURCE_DIR}/include)

#install(TARGETS FrogSockLib DESTINATION lib)
#install(DIRECTORY include/ DESTINATINO include)
