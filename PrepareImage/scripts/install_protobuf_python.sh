#!/bin/bash

DIR_EXT="/extapps"
DIR_PROTOBUF="${DIR_EXT}/protobuf"
DIR_PROTOBUF_PYTHON="${DIR_PROTOBUF}/python"
export PYTHONPATH="$(${DIR_EXT}/scripts/get_pypath.py)"
echo PYTHONPATH=$PYTHONPATH


cd ${DIR_PROTOBUF_PYTHON}
python setup.py
python setup.py build
python setup.py test
python setup.py install

