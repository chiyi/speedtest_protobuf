#!/bin/bash

SCFULLNAME=$(realpath $0)
SCPATH=$(dirname $SCFULLNAME)
WORKPATH=$(realpath $SCPATH/..)
PATH_PROTOCLASS="src/src_py/proto_class"

# Generate python classes from proto files
cd "${WORKPATH}"
protoc -I proto --python_out="${PATH_PROTOCLASS}" proto/*.proto

