# cpp-2021
## How to run?
### 1. Git clone && Generate a Project Buildsystem
`$ git submodule init`
`$git clone --recurse-submodules {{THIS_REPOSITORY}}`
`cmake -S {{PATH_TO_CMakeLists.txt}} -B {{PATH_TO_DIR_WITH_BIN}} -D CMAKE_TOOLCHAIN_FILE={{VCPKG_PATH}}/scripts/buildsystems/vcpkg.cmake`
### 2. Build a Project
`cmake --build {{PATH_TO_DIR_WITH_BIN}}`
### 3. Run Calculator
`$ cd {{PATH_TO_DIR_WITH_BIN}}`
#### 3.1. Via cin
`$ ./calculator`
#### 3.1. Via file
`$ ./calculator {{PATH_TO_FILE}}`
### Calculator commands:


