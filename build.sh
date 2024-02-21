#!/usr/bin/sh
# NOTE: you probably should comment out clearing CMake cache files if you need to compile multiple times.

set -e

cd build
[ -f bubbles ] && rm bubbles
cmake ..
make
rm ../bubbles_build*.zip 2> /dev/null || true
rm -r CMakeFiles cmake_install.cmake CMakeCache.txt Makefile 2> /dev/null || true
mv compile_commands.json ../
cd ..
zip -dc -r "bubbles_build$(date +%s).zip" build

LSAN_OPTIONS="verbosity=1:log_threads=1" build/bubbles
