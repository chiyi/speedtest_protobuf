#!/bin/bash

SCFULLNAME=`realpath $0`
SCPATH=`dirname $SCFULLNAME`
USERNAME=$(id -u -n)

cd $SCPATH

docker run \
 --rm \
 -w "/work-dir" \
 -it docker_protobuf \
 /bin/bash
