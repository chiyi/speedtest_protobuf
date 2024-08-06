#!/bin/bash

SCFULLNAME=$(realpath $0)
SCPATH=$(dirname $SCFULLNAME)

CFLAG_COMPILE_ROOT=$(root-config --cflags)
LIBS_COMPILE_ROOT=$(root-config --cflags --glibs)
CFLAG_COMPILE_PROTOBUF=$(pkg-config --cflags protobuf)
LIBS_COMPILE_PROTOBUF=$(pkg-config --libs protobuf)


cd ${SCPATH}

# Compile protoclasses
for file in *.pb.cc; do
 c++ -g -c -O3 -Wall ${CFLAG_COMPILE_PROTOBUF} $file -o ${file%.cc}.o ${LIBS_COMPILE_PROTOBUF}
done

c++ -g ${CFLAG_COMPILE_ROOT} test_objs.cc *.pb.o -o test_objs ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF}

