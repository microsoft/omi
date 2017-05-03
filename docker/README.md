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
docker build --build-arg rootpassword=newpassword -t "microsoft/omi:ubuntu16.04" release/ubuntu16.04/
docker build --build-arg rootpassword=newpassword -t "microsoft/omi:ubuntu14.04" release/ubuntu14.04/
docker build --build-arg rootpassword=newpassword -t "microsoft/omi:centos7" release/centos7/
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
  
* `rootpassword`: container's root password to be set in nightly or release builds (default: `newpassword`)
  * Set `rootpassword=Pa$$word` after --build-arg to set `Pa$$word` as container's root password

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
