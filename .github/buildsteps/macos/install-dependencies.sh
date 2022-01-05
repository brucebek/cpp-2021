#!/usr/bin/env bash

# Makes the bash script to print out every command before it is executed except echo
trap '[[ $BASH_COMMAND != echo* ]] && echo $BASH_COMMAND' DEBUG

cd "$LAB_INDEX" || exit $?

vcpkg --version || exit $?

which vcpkg || exit $?

cat  /usr/local/bin/vcpkg/scripts/buildsystems/vcpkg.cmake
