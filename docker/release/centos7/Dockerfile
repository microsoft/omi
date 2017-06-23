FROM centos:latest

LABEL maintainer="Jumping Yang <yzpcreate@qq.com>"
LABEL readme.md="https://github.com/Microsoft/omi/blob/master/docker/README.md"
LABEL description="This Dockerfile will install the latest release of OMI."

ARG rootpassword=newpassword

SHELL ["/bin/bash", "-c"] 
RUN echo $rootpassword |passwd root --stdin
RUN yum update -y; \
    yum install -y rpm-devel pam-devel openssl which rpm-build krb5-devel redhat-lsb-core;
RUN rpm -Uvh http://packages.microsoft.com/config/rhel/7/packages-microsoft-prod.rpm
RUN yum install -y omi
RUN /opt/omi/bin/omiconfigeditor httpport -a 5985 < /etc/opt/omi/conf/omiserver.conf>tmp.conf && mv -f tmp.conf /etc/opt/omi/conf/omiserver.conf
RUN /opt/omi/bin/omiconfigeditor httpsport -a 5986 < /etc/opt/omi/conf/omiserver.conf>tmp.conf && mv -f tmp.conf /etc/opt/omi/conf/omiserver.conf
EXPOSE 5985 5986
ENTRYPOINT /opt/omi/bin/omiserver -d && echo 'Started omi inner docker' && tail -f /var/opt/omi/log/omiserver.log