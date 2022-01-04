cmake_minimum_required(VERSION 3.20)

project(Calculator CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(calculator
        main.cpp
        commands.h
        commands.cpp
        Stack.h
        Stack.cpp
        Calculator.h
        Calculator.cpp
        exceptions.h
        exceptions.cpp
        )

if (MSVC)
    target_compile_options(calculator
            PRIVATE /W4          # warnings level
            PRIVATE /WX          # treat all warnings as errors
            )
else()
    target_compile_options(calculator
            PRIVATE -Wall        # basic set of warnings
            PRIVATE -pedantic    # modern C++ inspections
            PRIVATE -Werror      # treat all warnings as errors
            )
endif()
