FROM ubuntu:16.04

LABEL maintainer="Jumping Yang <yzpcreate@qq.com>"
LABEL readme.md="https://github.com/Microsoft/omi/blob/master/docker/README.md"
LABEL description="This Dockerfile will install the latest release of OMI."


SHELL ["/bin/bash", "-c"] 
RUN apt-get update -y
RUN apt-get install -y rpm libpam0g-dev libkrb5-dev wget openssl;
RUN wget http://packages.microsoft.com/config/ubuntu/16.04/packages-microsoft-prod.deb
RUN dpkg -i packages-microsoft-prod.deb
RUN apt-get install -y omi
RUN /opt/omi/bin/omiconfigeditor httpport -a 5985 < /etc/opt/omi/conf/omiserver.conf>tmp.conf && mv -f tmp.conf /etc/opt/omi/conf/omiserver.conf
RUN /opt/omi/bin/omiconfigeditor httpsport -a 5986 < /etc/opt/omi/conf/omiserver.conf>tmp.conf && mv -f tmp.conf /etc/opt/omi/conf/omiserver.conf
EXPOSE 5985 5986
ENTRYPOINT /opt/omi/bin/omiserver -d && echo 'Started omi inner docker' && tail -f /var/opt/omi/log/omiserver.log
