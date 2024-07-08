#!/bin/bash

DIR_ABSEIL=`find /extapps -maxdepth 1 -type d -name '*abseil-cpp*'`

cd ${DIR_ABSEIL}
mkdir build
cd build
cmake -DABSL_BUILD_TESTING=ON -DABSL_USE_GOOGLETEST_HEAD=ON -DABSL_PROPAGATE_CXX_STD=ON -DCMAKE_CXX_STANDARD=20 ..
cmake --build . --target all
ctest

echo "test abseil hello_word"
cd /extapps/abseil_examples/build
cp -r ${DIR_ABSEIL} ../abseil-cpp
cmake -DABSL_PROPAGATE_CXX_STD=ON ..
cmake --build . --target hello_world
./hello_world
