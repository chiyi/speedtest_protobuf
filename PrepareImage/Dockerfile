FROM rootproject/root:6.32.02-ubuntu24.04 as BASE

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
RUN /extapps/scripts/install_dotnet8.sh 2>&1 | tee /extapps/scripts/install_dotnet8.log
RUN /extapps/scripts/install_turbobase64.sh

RUN mkdir /work-dir


FROM BASE as USER
RUN echo "USER PART"
ARG USERNAME
ARG GROUPNAME
ARG UID
ARG GID

RUN echo ${USERNAME}:${GROUPNAME} , ${UID}:${GID}
RUN /extapps/scripts/set_user.sh ${USERNAME}:${GROUPNAME} ${UID}:${GID}

