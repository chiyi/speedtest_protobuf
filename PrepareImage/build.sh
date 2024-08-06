#!/bin/bash

username=${USER-$(id -u -n)}
groupname=$(id -g -n)
userid=${UID-$(id -u)}
groupid=$(id -g)

docker build -t docker_protobuf --target BASE .

docker build \
 --build-arg USERNAME=${username} \
 --build-arg GROUPNAME=${groupname} \
 --build-arg UID=${userid} \
 --build-arg GID=${groupid} \
 -t docker_protobuf_${username} \
 --target USER \
 .
