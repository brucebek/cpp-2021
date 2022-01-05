cmake_minimum_required(VERSION 3.20)

project(Calculator CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest CONFIG REQUIRED)

find_path(SAFEINT_INCLUDE_DIRS "SafeInt.hpp")

add_library(calculator
        src/commands.h
        src/commands.cpp
        src/Stack.h
        src/Stack.cpp
        src/Calculator.h
        src/Calculator.cpp
        src/exceptions.h
        src/exceptions.cpp
)

add_executable(main
        src/main.cpp
        )

add_executable(tests
        tests/tests_of_calculator.cpp
        )

target_include_directories(calculator PRIVATE ${SAFEINT_INCLUDE_DIRS})
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(tests GTest::gtest GTest::gtest_main calculator)
target_link_libraries(main calculator)


if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(calculator
            PRIVATE /W4          # warnings level
            )
else()
    target_compile_options(calculator
            PRIVATE -Wall        # basic set of warnings
            PRIVATE -pedantic    # modern C++ inspections
            )
endif()

enable_testing()
include(GoogleTest)
gtest_discover_tests(tests)