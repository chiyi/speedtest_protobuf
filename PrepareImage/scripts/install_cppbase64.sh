#!/bin/bash

DIR_EXT="/extapps"
DIR_BASE64="${DIR_EXT}/cpp-base64"

cd ${DIR_EXT}
git clone https://github.com/ReneNyffenegger/cpp-base64

cd ${DIR_BASE64}
./compile-and-run-test
