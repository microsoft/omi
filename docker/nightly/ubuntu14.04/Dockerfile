FROM ubuntu:14.04

LABEL maintainer="Jumping Yang <yzpcreate@qq.com>"
LABEL readme.md="https://github.com/Microsoft/omi/blob/master/docker/README.md"
LABEL description="This Dockerfile will install the latest code of OMI."

ARG fork=Microsoft
ARG branch=master

SHELL ["/bin/bash", "-c"] 
RUN apt-get update -y
RUN apt-get install -y git pkg-config make g++ rpm librpm-dev libpam0g-dev libssl-dev libkrb5-dev openssl;
RUN git clone https://github.com/$fork/omi.git -b $branch; \
    cd omi; \
    pushd Unix; \
    ./configure; \
    make -j; \
    make install; \
    popd;
EXPOSE 5985 5986
ENTRYPOINT /opt/omi-1.0.8/bin/omiserver -d && echo 'Started omi inner docker' && tail -f /opt/omi-1.0.8/var/log/omiserver.log
