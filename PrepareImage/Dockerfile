FROM rootproject/root:6.32.02-ubuntu24.04

MAINTAINER kaiyi

RUN apt update -y && apt install -y python3-numpy python3-scipy python3-pandas vim net-tools g++ git

RUN mkdir /extapps
ADD scripts /extapps/scripts
COPY abseil_examples /extapps/abseil_examples
RUN /extapps/scripts/install_protobuf.sh 2>&1 | tee /extapps/scripts/install_protobuf.log
RUN ldconfig

RUN mkdir /work-dir

