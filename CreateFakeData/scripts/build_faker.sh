#!/bin/bash

SCFULLNAME=$(realpath $0)
SCPATH=$(dirname $SCFULLNAME)
PROJPATH=$(realpath $SCPATH/..)
DIR_PROTOOBJS="/work-dir/src/src_cpp/proto_class"
DIR_CPPBASE64="/extapps/cpp-base64"
CFLAG_COMPILE_ROOT=$(root-config --cflags)
LIBS_COMPILE_ROOT=$(root-config --glibs)
CFLAG_COMPILE_PROTOBUF=$(pkg-config --cflags protobuf)
LIBS_COMPILE_PROTOBUF=$(pkg-config --libs protobuf)



cd ${PROJPATH}

echo "Naive checks"
for file in JobsHandler.cpp job.cpp gen_block_common.cc gen_event_common.cc gen_blockx.cc gen_blocky.cc gen_blockz.cc gen_event_blockz.cc gen_fakeanadata.cc job_fakedata.cpp;
do
 echo ${file}
 OBJNAME=$(echo $file | awk -F "." '{print $1}')
 c++ -g -c -O3 -Wall -I${DIR_PROTOOBJS} ${CFLAG_COMPILE_ROOT} src/$file -o src/${OBJNAME}.o ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF} -lz
done

echo "Build"
c++ -g -O3 -I${DIR_PROTOOBJS} ${CFLAG_COMPILE_ROOT} src/create_fakedata.cc ${DIR_PROTOOBJS}/*.pb.o src/*.o src/jobs_scheduler.cpp -o create_fakedata ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF} -lz

