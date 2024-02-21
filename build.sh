#!/usr/bin/sh
# Probably should comment out clearing CMake cache files if you need to compile multiple times.

set -e

cd build
[ -f bubbles ] && rm bubbles
cmake ..
make
rm ../bubbles_build*.zip 2> /dev/null || true
rm -r CMakeFiles cmake_install.cmake CMakeCache.txt Makefile 2> /dev/null || true

zip -r "bubbles_build$(date +%s).zip" .
mv bubbles_build*.zip ../
mv compile_commands.json ../

LSAN_OPTIONS="verbosity=1:log_threads=1" ./bubbles
