FROM centos:latest

LABEL maintainer="Jumping Yang <yzpcreate@qq.com>"
LABEL readme.md="https://github.com/Microsoft/omi/blob/master/docker/README.md"
LABEL description="This Dockerfile will install the latest code of OMI."

ARG fork=Microsoft
ARG branch=master
ARG rootpassword=newpassword

SHELL ["/bin/bash", "-c"] 
RUN echo $rootpassword |passwd root --stdin
RUN yum update -y; \
    yum install -y git bind-utils gcc-c++ rpm-devel pam-devel openssl-devel rpm-build krb5-devel redhat-lsb-core openssl which;
RUN git clone https://github.com/$fork/omi.git -b $branch; \
    cd omi; \
    pushd Unix; \
    ./configure; \
    make -j; \
    make install; \
    popd;
EXPOSE 5985 5986
ENTRYPOINT /opt/omi-1.0.8/bin/omiserver -d && echo 'Started omi inner docker' && tail -f /opt/omi-1.0.8/var/log/omiserver.log