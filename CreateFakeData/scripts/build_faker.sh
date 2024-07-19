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
echo "JobsHandler.h"
c++ -g -S -Wall -I${DIR_PROTOOBJS} ${CFLAG_COMPILE_ROOT} src/JobsHandler.h ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF} -lz
echo "job.h job.cpp"
c++ -g -S -Wall -I${DIR_PROTOOBJS} ${CFLAG_COMPILE_ROOT} src/job.h src/job.cpp ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF} -lz
echo "job_fakedata.h job_fakedata.cpp"
c++ -g -S -Wall -I${DIR_PROTOOBJS} ${CFLAG_COMPILE_ROOT} src/job_fakedata.h src/job_fakedata.cpp ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF} -lz
echo "jobs_scheduler.h jobs_scheduler.cpp"
c++ -g -S -Wall -I${DIR_PROTOOBJS} ${CFLAG_COMPILE_ROOT} src/jobs_scheduler.h src/jobs_scheduler.cpp ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF} -lz

echo "Build"
c++ -g -I${DIR_PROTOOBJS} ${CFLAG_COMPILE_ROOT} src/create_fakedata.cc ${DIR_PROTOOBJS}/*.pb.o -o create_fakedata ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF} -lz

