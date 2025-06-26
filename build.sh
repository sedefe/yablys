#!/bin/bash

set -e

cmake -S . -B build -DCMAKE_BUILD_TYPE=RELEASE
# cmake -S . -B build -DCMAKE_BUILD_TYPE=DEBUG
cmake --build build
