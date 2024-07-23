#!/bin/bash
set -e

SCFULLNAME=$(realpath $0)
SCPATH=$(dirname $SCFULLNAME)
PROJPATH=$(realpath $SCPATH/..)
DIR_PROTOOBJS="/work-dir/src/src_cpp/proto_class"
CFLAG_COMPILE_ROOT=$(root-config --cflags)
LIBS_COMPILE_ROOT=$(root-config --cflags --glibs)
CFLAG_COMPILE_PROTOBUF=$(pkg-config --cflags protobuf)
LIBS_COMPILE_PROTOBUF=$(pkg-config --libs protobuf)
#DIR_CPPBASE64="/extapps/cpp-base64"
LOGFILE="${PROJPATH}/test_cpp_naiveparsing.log"


cd ${PROJPATH}
echo "building..."
#c++ -g -I${DIR_PROTOOBJS} ${CFLAG_COMPILE_ROOT} src/src_cpp/test_naiveparsing.cpp ${DIR_PROTOOBJS}/*.pb.o -o test_cpp_naiveparsing ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF} -lz
c++ -g -O3 -I${DIR_PROTOOBJS} ${CFLAG_COMPILE_ROOT} src/src_cpp/test_naiveparsing.cpp ${DIR_PROTOOBJS}/*.pb.o -o test_cpp_naiveparsing ${LIBS_COMPILE_ROOT} ${LIBS_COMPILE_PROTOBUF} -lz

echo "testing..."
(time ./test_cpp_naiveparsing "/data/fakedata_*.txt.gz" > ${LOGFILE} 2>&1 ) &>> ${LOGFILE}
(time ./test_cpp_naiveparsing "/data/fakedata_*.txt.gz" >> ${LOGFILE} 2>&1 ) &>> ${LOGFILE}
(time ./test_cpp_naiveparsing "/data/fakedata_*.txt.gz" >> ${LOGFILE} 2>&1 ) &>> ${LOGFILE}

cat ${LOGFILE} | grep  "^real" -C4

