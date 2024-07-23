#!/bin/bash

DIR_EXT="/extapps"
DIR_PROTOBUF="${DIR_EXT}/protobuf"
DIR_PROTOBUF_PYTHON="${DIR_PROTOBUF}/python"
export PYTHONPATH="$(${DIR_EXT}/scripts/get_pypath.py)"
echo PYTHONPATH=$PYTHONPATH


cd ${DIR_PROTOBUF_PYTHON}
bazel build //python/dist:source_wheel 2>&1 | tee source_wheel.log
bazel build //python/dist:binary_wheel 2>&1 | tee binary_wheel.log

cat source_wheel.log | grep Target
cat binary_wheel.log | grep Target

BINARY_WHL=$(ls ${DIR_PROTOBUF}/bazel-bin/python/dist/*.whl | grep "/protobuf" | head -1)
DIR_BAZELWHL=$(dirname ${BINARY_WHL})
FILENAME_WHL=$(basename ${BINARY_WHL})
cd ${DIR_BAZELWHL}
pip install "$FILENAME_WHL" --break-system-packages

