Docker for OMI
======

These DockerFiles enable building and running omi in a container for some Linux distribution we support.
There are two sets: release and nightly.

This requires an up-to-date version of Docker, such as 1.12.
It also expects you to be able to run Docker without `sudo`.
Please follow [Docker's official instructions][install] to install `docker` correctly.

[install]: https://docs.docker.com/engine/installation/

Build Release OMI docker
-------

The release containers derive from the official distribution image,
such as `centos:7`, then install dependencies,
and finally install the omi package from Microsoft Repo, the command to build nightly omi docker show as follow:

```
git clone https://github.com/Microsoft/omi
cd omi/docker
docker build -t "microsoft/omi:ubuntu16.04" release/ubuntu16.04/
docker build -t "microsoft/omi:ubuntu14.04" release/ubuntu14.04/
docker build -t "microsoft/omi:centos7" release/centos7/
```

Build Nightly OMI docker
-------

The nightly containers derive from the official distribution image,
such as `centos:7`, then install dependencies,
and finally build latest omi code and install it, the command to build nightly omi docker show as follow:

```
git clone https://github.com/Microsoft/omi
cd omi/docker
docker build --build-arg fork=Microsoft --build-arg branch=master --build-arg rootpassword=newpassword -t "microsoft/omi:ubuntu16.04" nightly/ubuntu16.04/
docker build --build-arg fork=Microsoft --build-arg branch=master --build-arg rootpassword=newpassword -t "microsoft/omi:ubuntu14.04" nightly/ubuntu14.04/
docker build --build-arg fork=Microsoft --build-arg branch=master --build-arg rootpassword=newpassword -t "microsoft/omi:centos7" nightly/centos7/
```

Build Command Usage
-------

Variable following with --build-arg:
* `fork`: the fork to clone in nightly builds (default: `Microsoft`)
  * Set `fork=JumpingYang001` after --build-arg to clone https://github.com/JumpingYang001/omi`

* `branch`: the branch to checkout in nightly builds (default: `master`)
  * Set `branch=feature-A` after --build-arg to checkout the `feature-A` branch

Variable following with -t:
* `microsoft/omi:ubuntu16.04`: the image tag you want to build out for the omi docker
* `microsoft/omi:ubuntu14.04`: the image tag you want to build out for the omi docker
* `microsoft/omi:centos7`: the image tag you want to build out for the omi docker

Run OMI docker
-------

You can run below commands to start up a omi docker container:

```
docker run -p 1001:5985 -p 1002:5986 microsoft/omi:ubuntu16.04
docker run -p 1003:5985 -p 1004:5986 microsoft/omi:ubuntu14.04
docker run -p 1005:5985 -p 1006:5986 microsoft/omi:centos7
```

Enter docker container to check any issues
-------

```
docker exec -it <container_id|container_name> /bin/bash
```

How to Collect Docker Container Performance Metrics using OMI/OMI provider inside Docker Container
-------

- To collect containers’ performance metrics (including or not including the container runs OMI/OMI provider), you can use [ContainerStatisticsProvider], or you can implement a similar provider. If you wish to use [ContainerStatisticsProvider], this ships with [OMS]. You can either install [OMS] itself, or you can extract [ContainerStatisticsProvider] from the [OMS] bundle and install that provider independently.
- To write your own OMI docker provider, you can use either pseudo-files or the docker API. For details about docker API, you can refer to [Docker API]. For the different options for collecting docker performance metrics, you can refer to [How to collect docker metrics].
- OMI/OMI provider can collect containers’ (including or not including the container runs OMI/OMI provider) performance metrics inside a normal container or a privileged container depending on your host platform. If your host platform is RHEL or CentOS, you need to run OMI/OMI provider in a privileged container. If you use docker API, you need to run a privileged container with --privileged=true, or you need to mount /cgroup with --volume=/cgroup:/cgroup:ro if you use pseudo-files. For other host platforms, you can run OMI/OMI provider in a normal container to collect all containers’ performance metrics.
- Multiple OMI instances can run in different containers if they are mapped to different ports on the host system.

[OMS]: https://github.com/Microsoft/OMS-Agent-for-Linux
[Docker API]: https://docs.docker.com/engine/api/get-started/
[How to collect docker metrics]:https://www.datadoghq.com/blog/how-to-collect-docker-metrics
[ContainerStatisticsProvider]: https://github.com/Microsoft/Docker-Provider/blob/master/source/code/providers/Container_ContainerStatistics_Class_Provider.cpp

How to Collect Virtual Machine Host Performance Metrics using OMI/OMI provider inside Docker Container
-------

- OMI/OMI provider can collect virtual machine host's performance metrics inside a normal container.
- To be able to collect host performance metrics, you can use [SCXProvider], or you can implement a similar provider. If you wish to use [SCXProvider], this ships with [OMS]. You can either install [OMS] itself, or you can extract [SCXProvider] from the [OMS] bundle and install that provider independently.

[OMS]: https://github.com/Microsoft/OMS-Agent-for-Linux
[SCXProvider]: https://github.com/Microsoft/SCXcore

