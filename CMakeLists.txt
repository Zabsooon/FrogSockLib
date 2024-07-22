cmake_minimum_required(VERSION 3.13)
project(FrogSockLib)

set(FrogSocketLib_VERSION_MAJOR 1)
set(FrogSocketLib_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(FrogSockLib SHARED
    src/Socket.cpp
    src/Address.cpp
    # Add other sources if necessary
)

target_include_directories(FrogSockLib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Helper function to add all example projects
function(add_example_project example_dir)
    file(GLOB_RECURSE EXAMPLE_SOURCES "${example_dir}/*.cpp")
    get_filename_component(EXAMPLE_NAME ${example_dir} NAME)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCES})
    target_link_libraries(${EXAMPLE_NAME} FrogSockLib)
    set_target_properties(${EXAMPLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/example/${EXAMPLE_NAME})
endfunction()

# Find all subdirectories in the example directory
file(GLOB EXAMPLE_DIRS "example/*")
foreach(EXAMPLE_DIR ${EXAMPLE_DIRS})
    if(IS_DIRECTORY ${EXAMPLE_DIR})
        add_example_project(${EXAMPLE_DIR})
    endif()
endforeach()

# Google Test
add_subdirectory(googletest)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add test executable
file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(runTests ${TEST_SOURCES})
target_link_libraries(runTests gtest gtest_main FrogSockLib)

add_test(NAME runTests COMMAND runTests)

# Uncomment these if you want to install the library
# install(TARGETS FrogSockLib DESTINATION lib)
# install(DIRECTORY include/ DESTINATION include)
