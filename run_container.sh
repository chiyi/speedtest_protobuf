#!/bin/bash

SCFULLNAME=`realpath $0`
SCPATH=`dirname $SCFULLNAME`
USERNAME=$(id -u -n)

cd $SCPATH

docker run \
 --rm \
 -w "/work-dir" \
 -v ${PWD}/workdir:/work-dir \
 -v ${PWD}/CreateFakeData:/work-dir/CreateFakeData \
 -v ${PWD}/fakedata:/data \
 -it docker_protobuf \
 /bin/bash
