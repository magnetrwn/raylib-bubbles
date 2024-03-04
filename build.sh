#!/usr/bin/sh
set -e

BUILD_FILENAME="bubbles_build$(date +%s).zip"

mkdir -p build
rsync -a static/ build/
cd build
[ -f bubbles ] && rm bubbles
cmake ..
make
zip -dcr9 "$BUILD_FILENAME" bubbles
cp compile_commands.json ../
cd ..
zip -dcr9 build/"$BUILD_FILENAME" static
mv build/"$BUILD_FILENAME" .

LSAN_OPTIONS="verbosity=1:log_threads=1" build/bubbles
