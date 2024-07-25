#!/bin/bash
set -e

SCFULLNAME=$(realpath $0)
SCPATH=$(dirname $SCFULLNAME)
PROJPATH=$(realpath $SCPATH/..)
DIR_PROTOCLASSES="/work-dir/src/src_csharp_sln/proto_class"
DIR_CSHARPPROJ="${PROJPATH}/src/src_csharp_sln/Test_NaiveParsing"
LOGFILE="${PROJPATH}/test_csharp_naiveparsing.log"


cd ${DIR_CSHARPPROJ}
echo "building..."
dotnet add reference ${DIR_PROTOCLASSES}
dotnet build -f net8.0 -r linux-x64 -p:LargeAddressAware=true
dotnet publish -c Release -r linux-x64 --self-contained
built_file=$(find bin/Release -name "Test_NaiveParsing" | grep publish | head -1)
echo built_file = $built_file
cp ${built_file} ${PROJPATH}/test_csharp_naiveparsing

cd ${PROJPATH}
echo "testing..."
(time ./test_csharp_naiveparsing "/data" "fakedata_*.txt.gz" > ${LOGFILE} 2>&1) &>> ${LOGFILE}
(time ./test_csharp_naiveparsing "/data" "fakedata_*.txt.gz" >> ${LOGFILE} 2>&1) &>> ${LOGFILE}
(time ./test_csharp_naiveparsing "/data" "fakedata_*.txt.gz" >> ${LOGFILE} 2>&1) &>> ${LOGFILE}

cat ${LOGFILE} | grep  "^real" -C4

