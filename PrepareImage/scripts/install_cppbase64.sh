#!/bin/bash
set -e

DIR_EXT="/extapps"
DIR_BASE64="${DIR_EXT}/cpp-base64"

cd ${DIR_EXT}
git clone https://github.com/ReneNyffenegger/cpp-base64

cd ${DIR_BASE64}
make
./compile-and-run-test
