#!/bin/bash
set -e

DIR_EXT="/extapps"
DIR_BASE64="${DIR_EXT}/Turbo-Base64"

cd ${DIR_EXT}
git clone https://github.com/powturbo/Turbo-Base64.git

cd ${DIR_BASE64}
make
