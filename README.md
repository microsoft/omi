Open Management Infrastructure [![Build Status](https://travis-ci.com/PowerShell/omi.svg?token=31YifM4jfyVpBmEGitCm&branch=master)](https://travis-ci.com/PowerShell/omi)
==============================

[Waffle.io scrum board](https://waffle.io/PowerShell/omi)

Building
--------

Build in developer mode:

```sh
pushd Unix
./configure --dev
make -j
popd
```

Run regression tests

```sh
pushd Unix
./regress
popd
```
