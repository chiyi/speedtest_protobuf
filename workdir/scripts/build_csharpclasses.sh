#!/bin/bash

SCFULLNAME=$(realpath $0)
SCPATH=$(dirname $SCFULLNAME)
WORKPATH=$(realpath $SCPATH/..)
PATH_PROTOCLASS="src/src_csharp_sln/proto_class"

# Generate python classes from proto files
cd "${WORKPATH}"
protoc -I proto --csharp_out="${PATH_PROTOCLASS}" proto/*.proto

cd ${PATH_PROTOCLASS}
rm Class1.cs || echo "removing Class1.cs"
dotnet add package Google.Protobuf -v 3.27.2
dotnet build -f net8.0 -r linux-x64
dotnet publish -c Release -r linux-x64

