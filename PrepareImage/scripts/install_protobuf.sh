#!/bin/bash

DIR_EXT="/extapps"
DIR_PROTOBUF="${DIR_EXT}/protobuf"
DIR_ABSEIL="${DIR_PROTOBUF}/third_party/abseil-cpp"
DIR_ABSEIL_EXAMPLE="${DIR_EXT}/abseil_examples/build"
export PYTHONPATH="$(${DIR_EXT}/scripts/get_pypath.py)"
echo PYTHONPATH=$PYTHONPATH


cd ${DIR_EXT}
git clone --branch v27.2 https://github.com/protocolbuffers/protobuf.git
cd protobuf
git submodule update --init --recursive

cd ${DIR_ABSEIL}
mkdir build
cd build
cmake -DABSL_BUILD_TESTING=ON -DABSL_USE_GOOGLETEST_HEAD=ON -DABSL_PROPAGATE_CXX_STD=ON .. 2>&1 | tee build_absl_configure.log
cmake --build . --parallel 10 --target all 2>&1 | tee build_absl.log
ctest --parallel 10

echo "test abseil hello_word"
cd ${DIR_ABSEIL_EXAMPLE}
cp -r ${DIR_ABSEIL} ../abseil-cpp
cmake -DABSL_PROPAGATE_CXX_STD=ON ..
cmake --build . --parallel 10 --target hello_world
./hello_world

cd ${DIR_PROTOBUF}
cmake . 2>&1 | tee build_configure_protobuf.log
cmake --build . --parallel 10 2>&1 | tee build_protobuf.log
ctest --verbose --parallel 10
cmake --install .

