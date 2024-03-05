#!/usr/bin/sh
set -e

BUILD_FILENAME="bubbles_build$(date +%s).zip"

mkdir -p build dist
rsync -a static/ build/

cd build
[ -f bubbles ] && rm bubbles
cmake ..
make
zip -dc -r -9 "$BUILD_FILENAME" bubbles
mv "$BUILD_FILENAME" ../dist
cp compile_commands.json ../

cd ../static
zip -dc -r -9 ../dist/"$BUILD_FILENAME" ./*

cd ..
LSAN_OPTIONS="verbosity=1:log_threads=1" build/bubbles
