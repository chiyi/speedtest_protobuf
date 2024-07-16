#!/bin/bash

SCFULLNAME=$(realpath $0)
SCPATH=$(dirname $SCFULLNAME)
PROJPATH=$(realpath $SCPATH/..)
DIR_PROTOOBJS="/work-dir/src/src_cpp/proto_class"
DIR_CPPBASE64="/extapps/cpp-base64"
CFLAG_COMPILE_ROOT=$(root-config --cflags)
LIBS_COMPILE_ROOT=$(root-config --cflags --glibs)
CFLAG_COMPILE_PROTOBUF=$(pkg-config --cflags protobuf)
LIBS_COMPILE_PROTOBUF=$(pkg-config --libs protobuf)



cd ${PROJPATH}
c++ -g -I${DIR_PROTOOBJS} ${CFLAG_COMPILE_ROOT} src/create_fakedata.cc ${DIR_PROTOOBJS}/*.pb.o -o create_fakedata ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF}

