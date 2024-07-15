#!/bin/bash

SCFULLNAME=$(realpath $0)
SCPATH=$(dirname $SCFULLNAME)
WORKPATH=$(realpath $SCPATH/..)
PATH_PROTOCLASS="src/src_cpp/proto_class"
export LD_LIBRARY_PATH=/usr/local/lib

# Root-config flags
CFLAG_COMPILE_ROOT=$(root-config --cflags)
LIBS_COMPILE_ROOT=$(root-config --cflags --glibs)
# Protobuf flags
CFLAG_COMPILE_PROTOBUF=$(pkg-config --cflags protobuf)
LIBS_COMPILE_PROTOBUF=$(pkg-config --libs protobuf)

# Generate C++ classes from proto files
cd "${WORKPATH}"
protoc -I proto --cpp_out="${PATH_PROTOCLASS}" proto/*.proto

# Compile protoclasses
cd "$WORKPATH/$PATH_PROTOCLASS"
for file in *.pb.cc
do
 c++ -g -c -Wall ${CFLAG_COMPILE_PROTOBUF} ${file} -o "${file%.cc}.o" ${LIBS_COMPILE_PROTOBUF}
done

# Compile and test objects
c++ -g ${CFLAG_COMPILE_ROOT} test_objs.cc *.pb.o -o test_objs ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF}
./test_objs


cd "${WORKPATH}"
