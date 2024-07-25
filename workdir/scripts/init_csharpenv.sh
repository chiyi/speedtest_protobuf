#!/bin/bash
## This script should only be run once
#
#SCFULLNAME=$(realpath $0)
#SCPATH=$(dirname $SCFULLNAME)
#WORKPATH=$(realpath $SCPATH/..)
#DIR_CSHARPSLN="${WORKPATH}/src/src_csharp_sln"
#
#cd $DIR_CSHARPPROJ
#cd ${WORKPATH}/src
#dotnet new sln -n src_csharp_sln -o src_csharp_sln
#cd ${DIR_CSHARPSLN}
#dotnet new classlib -n proto_class
#dotnet sln add proto_class/proto_class.csproj
#dotnet new .gitignore
#dotnet new .gitignore -o proto_class --project proto_class
#
#
#echo "This script should only be run once"
