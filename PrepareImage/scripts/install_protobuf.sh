#!/bin/bash

DIR_EXT="/extapps"
DIR_PROTOBUF="${DIR_EXT}/protobuf"
DIR_ABSEIL="${DIR_PROTOBUF}/third_party/abseil-cpp"
DIR_ABSEIL_EXAMPLE="${DIR_EXT}/abseil_examples/build"
export PYTHONPATH="$(${DIR_EXT}/scripts/get_pypath.py)"
echo PYTHONPATH=$PYTHONPATH


cd ${DIR_EXT}
git clone --branch v20.2 https://github.com/protocolbuffers/protobuf.git
cd protobuf
git submodule update --init --recursive

cd ${DIR_PROTOBUF}
./autogen.sh
./configure 2>&1 | tee build_configure_protobuf.log
make -j 10 2>&1 | tee build_protobuf.log
make check
make install

