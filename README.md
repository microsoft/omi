Open Management Infrastructure 
==============================
Open Management Infrastructure (OMI) is an open source project to further the development of a production quality implementation of the DMTF CIM/WBEM standards. The OMI CIMOM is also designed to be portable and highly modular. In order to attain its small footprint, it is coded in C, which also makes it a much more viable CIM Object Manager for embedded systems and other infrastructure components that have memory constraints for their management processor. OMI is also designed to be inherently portable. It builds and runs today on most UNIX® systems and Linux. In addition to OMI's small footprint, it also demonstrates very high performance.

Additional Resources
--------------------
- [https://collaboration.opengroup.org/omi/documents.php?action=show&dcat=&gdid=26457](https://collaboration.opengroup.org/omi/documents.php?action=show&dcat=&gdid=26457 "High Level Overview")
- [https://collaboration.opengroup.org/omi/documents.php?action=show&dcat=&gdid=26350](https://collaboration.opengroup.org/omi/documents.php?action=show&dcat=&gdid=26350 "Getting Started guide")

Get OMI
=======
RPM and DEB packages are provided for the installation of OMI on most enterprise Linux distributions. To install OMI, download the correct package for your Linux computer. Choose from:
- RPM or Debian package format
- OpenSSL version 0.9.8 or 1.0.x. (To determine your OpenSSL version, run: `openssl version`)

You can download and install OMI from following links:

| Platform     | Release           | SSL                 | Link                             |
|--------------|-------------------|---------------------|----------------------------------|
| Linux        | Debian            | 1.0.0               |[omi-1.1.0.ssl_100.x64.deb] |
| Linux        | Debian            | 0.9.8               |[omi-1.1.0.ssl_098.x64.deb] |
| Linux        | RPM               | 1.0.0               |[omi-1.1.0.ssl_100.x64.rpm] |
| Linux        | RPM               | 0.9.8               |[omi-1.1.0.ssl_098.x64.rpm] |

[omi-1.1.0.ssl_100.x64.deb]: https://github.com/Microsoft/omi/releases
[omi-1.1.0.ssl_098.x64.deb]: https://github.com/Microsoft/omi/releases
[omi-1.1.0.ssl_100.x64.rpm]: https://github.com/Microsoft/omi/releases
[omi-1.1.0.ssl_098.x64.rpm]: https://github.com/Microsoft/omi/releases

Supported Linux Operating Systems
---------------------------------
- CentOS Linux 5,6, and 7 (x64)
- Debian GNU/Linux 6, 7, and 8 (x64)
- Oracle Linux 5,6, and 7 (x64)
- Red Hat Enterprise Linux Server 5,6 and 7 (x64)
- SUSE Linux Enteprise Server 11 and 12 (x64)
- Ubuntu 12.04 LTS, 14.04 LTS, 15.04, 15.10, 16.04 LTS (x64)

Installation examples:
---------------------------------
- Ubuntu 14.04 or 16.04, x64:
`sudo dpkg -i ./omi-1.1.0.ssl_100.x64.deb`

- Red Hat Enterprise Linux, Oracle Linux, or CentOS 6/7, x64:
`sudo rpm -Uvh ./omi-1.1.0.ssl_100.x64.rpm`

Development Environment
=======================

Git Setup
---------
```sh
git clone https://github.com/Microsoft/omi.git
```

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

Running
=======
Installing OMI configures a daemon named "omid" which can be controlled with standard service controllers: `service` or `systemctl`. Additionally, a service_control script can be found at: `/opt/omi/bin/service_control`

Restarting OMI: `sudo /opt/omi/bin/service_control restart`

Testing OMI
-----------
To test that OMI is functional locally, the `omicli` command be used:
` sudo /opt/omi/bin/omicli ei root/omi OMI_Identify`
This command enumerates all instances of the *OMI_Identify* class in the *root/omi* namespace.

Configuring OMI Server
----------------------
OMI's server configuration is set in the file: `/etc/opt/omi/conf/omiserver.conf`.  Important configuration properties include:
- **httpsport** The HTTPs port(s) to listen on. The default is 5986. Multiple ports can be defined as a comma-seperated list. 
- **httpport** The HTTP port to listen on. It is recommended that HTTP remain disabled (httpport=0) to prevent unencrypted communication.
- **pemfile** The certificate to use for TLS/SSL communication
- **keyfile** The private key that corresponds to the TLS/SSL certificate'
- **NoSSLv2** When *true*, or not set, the SSLv2 protocol is disabled
- **NoSSLv3** When *true*, the SSLv3 protocol is disabled. If NoSSLv2 and NoSSLv3 are both set to *true*, only TLS encryption will be negotiated.
- **sslCipherSuite** The prioritized list of allowed SSL/TLS ciphers. For more information, see [OpenSSL's documentation](https://openssl.org/docs/manmaster/apps/ciphers.html "OpenSSL's documentation"). 
