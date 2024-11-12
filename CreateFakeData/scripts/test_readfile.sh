#!/bin/bash

SCFULLNAME=$(realpath $0)
SCPATH=$(dirname $SCFULLNAME)
PROJPATH=$(realpath $SCPATH/..)
DIR_PROTOOBJS="/work-dir/src/src_cpp/proto_class"
DIR_TURBOBASE64="/extapps/Turbo-Base64"
LIBS_TURBOBASE64="${DIR_TURBOBASE64}/turbo*.o"
CFLAG_COMPILE_ROOT=$(root-config --cflags)
LIBS_COMPILE_ROOT=$(root-config --cflags --glibs)
CFLAG_COMPILE_PROTOBUF=$(pkg-config --cflags protobuf)
LIBS_COMPILE_PROTOBUF=$(pkg-config --libs protobuf)


cd ${PROJPATH}
c++ -g -O3 -I${DIR_PROTOOBJS} -I${DIR_TURBOBASE64} ${CFLAG_COMPILE_ROOT} src/read_file.cc ${DIR_PROTOOBJS}/*.pb.o ${LIBS_TURBOBASE64} -o read_file ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF} -lz

./read_file "/data/fakedata_1.txt.gz"
#./read_file "/data/fakedata_*.txt.gz"
