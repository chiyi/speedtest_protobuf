#!/bin/bash
set -e

SCFULLNAME=$(realpath $0)
SCPATH=$(dirname $SCFULLNAME)
PROJPATH=$(realpath $SCPATH/..)
DIR_PROTOCLASSES="/work-dir/src/src_py/proto_class"
LOGFILE="${PROJPATH}/test_py_simanatable.log"
export PYTHONPATH="${DIR_PROTOCLASSES}:${PYTHONPATH}"
echo $PYTHONPATH


cd ${PROJPATH}
echo "testing..."

(time python src/src_py/test_simanatable.py "/data/fakedata_*.txt.gz" > ${LOGFILE} 2>&1) &>> ${LOGFILE}
#(time python src/src_py/test_simanatable.py "/data/fakedata_*.txt.gz" >> ${LOGFILE} 2>&1) &>> ${LOGFILE}
#(time python src/src_py/test_simanatable.py "/data/fakedata_*.txt.gz" >> ${LOGFILE} 2>&1) &>> ${LOGFILE}

cat ${LOGFILE} | grep  "^real" -C4

