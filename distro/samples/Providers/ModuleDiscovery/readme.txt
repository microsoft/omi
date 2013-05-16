
1) Create directory /omi/etc/TorSwitchManagement

2) Copy all files from ./TorSwitchManagement to /omi/etc/TorSwitchManagement/

3) build the provider (make)

4) /opt/omi-1.0.0/bin/omireg -n root/cimv2 <provider name>.so

5) following request should works
     /opt/omi-1.0.0/bin/omicli ei root/cimv2 PS_Module
     /opt/omi-1.0.0/bin/omicli ei root/cimv2 PS_ModuleFile
     /opt/omi-1.0.0/bin/omicli a root/cimv2 { ps_module InstanceID "/omi/etc/TorSwitchManagement" }
