FROM rootproject/root:6.32.02-ubuntu24.04

MAINTAINER kaiyi

RUN apt update -y && apt install -y python3-numpy python3-scipy python3-pandas vim net-tools g++ git pip

RUN mkdir /extapps
ADD scripts /extapps/scripts
RUN /extapps/scripts/install_bazel.sh 2>&1 | tee /extapps/scripts/install_bazel.log
COPY abseil_examples /extapps/abseil_examples
RUN /extapps/scripts/install_protobuf.sh 2>&1 | tee /extapps/scripts/install_protobuf.log
RUN ldconfig
RUN /extapps/scripts/install_protobuf_python.sh 2>&1 | tee /extapps/scripts/install_protobuf_python.log
RUN /extapps/scripts/install_cppbase64.sh


RUN mkdir /work-dir

