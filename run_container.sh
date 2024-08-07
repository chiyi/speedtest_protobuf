#!/bin/bash

SCFULLNAME=`realpath $0`
SCPATH=`dirname $SCFULLNAME`
USERNAME=$(id -u -n)

cd $SCPATH

docker run \
 --rm \
 -w "/work-dir" \
 -u ${UID}:$(id -g) \
 -v ${PWD}/workdir:/work-dir \
 -v ${PWD}/CreateFakeData:/work-dir/CreateFakeData \
 -v ${PWD}/Test_NaiveParsing:/work-dir/Test_NaiveParsing \
 -v ${PWD}/Test_SimAnaTable:/work-dir/Test_SimAnaTable \
 -v ${PWD}/fakedata:/data \
 -it docker_protobuf_${USERNAME} \
 /bin/bash
