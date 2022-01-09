cmake_minimum_required(VERSION 3.20)

project(Calculator CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest CONFIG REQUIRED)

add_executable(tests tests.cpp LinkedList.h)

target_link_libraries(tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)


if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(tests
            PRIVATE /W4          # warnings level
            )
else()
    target_compile_options(tests
            PRIVATE -Wall        # basic set of warnings
            PRIVATE -pedantic    # modern C++ inspections
            )
endif()

enable_testing()
include(GoogleTest)
gtest_discover_tests(tests)