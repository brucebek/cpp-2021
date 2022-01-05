#!/usr/bin/env bash

# Makes the bash script to print out every command before it is executed except echo
trap '[[ $BASH_COMMAND != echo* ]] && echo $BASH_COMMAND' DEBUG

cd "$LAB_INDEX"                                                              || exit $?

cd 'build'                                                                   || exit $?

cmake --version                                                              || exit $?
make --version                                                               || exit $?

echo
echo '================================== BUILD Debug ==================================='
cmake -E rm -rf 'debug'                                                      || exit $?
echo $VCPKG_ROOT || exit $?
cmake -G 'Ninja' -D 'CMAKE_BUILD_TYPE=Release' -D "CMAKE_TOOLCHAIN_FILE=${GITHUB_WORKSPACE}/vcpkg/scripts/buildsystems/vcpkg.cmake" -B 'release' -S '..' || exit $?
echo
cmake --build 'debug'                                                        || exit $?

echo
echo 'Debug configuration has been built successfully.'
echo '=================================================================================='

echo
echo

echo '================================== BUILD Release ================================='
cmake -E rm -rf 'release'                                                    || exit $?
cmake -G 'Ninja' -D 'CMAKE_BUILD_TYPE=Release' -D "CMAKE_TOOLCHAIN_FILE=${GITHUB_WORKSPACE}/vcpkg/scripts/buildsystems/vcpkg.cmake" -B 'release' -S '..' || exit $?
echo
cmake --build 'release'                                                      || exit $?

echo
echo 'Release configuration has been built successfully.'
echo '=================================================================================='

echo
echo

echo 'Passed.'