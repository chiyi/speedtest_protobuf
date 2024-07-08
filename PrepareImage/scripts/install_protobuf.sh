#!/bin/bash

DIR_EXT="/extapps"

DIR_PROTOBUF=`find /extapps -maxdepth 1 -type d -name '*protobuf*'`
DIR_ABSEIL=`find /extapps -maxdepth 1 -type d -name '*abseil-cpp*'`
DIR_GOOGLETEST=`find /extapps -maxdepth 1 -type d -name '*googletest*'`
DIR_JSONCPP=`find /extapps -maxdepth 1 -type d -name '*jsoncpp*'`

cd ${DIR_PROTOBUF}/third_party
rmdir abseil-cpp
ln -s ${DIR_ABSEIL} abseil-cpp
rmdir googletest
ln -s ${DIR_GOOGLETEST} googletest
rmdir jsoncpp
ln -s ${DIR_JSONCPP} jsoncpp

cd ${DIR_PROTOBUF}
cmake -DABSL_PROPAGATE_CXX_STD=ON .
cmake --build . --parallel 10
ctest --verbose
cmake --install .

