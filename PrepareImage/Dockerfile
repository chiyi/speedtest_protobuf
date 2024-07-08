FROM rootproject/root:6.32.02-ubuntu24.04

MAINTAINER kaiyi

RUN apt update -y && apt install -y python3-numpy python3-scipy python3-pandas vim net-tools g++ git
RUN mkdir /extapps
ADD scripts /extapps/scripts
ADD protobuf-source-v27.2.tar.gz /extapps/
RUN /extapps/scripts/install_bazel.sh
ADD abseil-cpp-source-20240116.2.tar.gz /extapps/
COPY abseil_examples /extapps/abseil_examples
RUN /extapps/scripts/install_abseil.sh

ADD googletest-v1.14.0.tar.gz /extapps/
ADD jsoncpp-1.9.5.tar.gz /extapps/
RUN /extapps/scripts/install_protobuf.sh

RUN mkdir /work-dir

