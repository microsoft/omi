# Configure Kerberos Environment Known Issues

## kinit: KDC reply did not match expectations while getting initial credentials

When you meet this issue, you might run kinit myaccount@corp.example.com with lower char domain name.

Fix solution:
> Use upper char domain name: kinit myaccount@CORP.EXAMPLE.COM

## kinit: Credentials cache keyring 'persistent:0:0' not found

When you meet this issue, you might need to refresh your credential.

Fix solution:
> Run kinit again: kinit myaccount@CORP.EXAMPLE.COM, or you can run with long expired duration: kinit -l 100h myaccount@CORP.EXAMPLE.COM

## kinit: Cannot find KDC for requested realm while getting initial credentials

When you meet this issue, you might meet dns issue for kdc server.

Fix solution:
> Edit /etc/krb5.conf, change "dns_lookup_kdc = false" to "dns_lookup_kdc = true"

## Kerberos log: Key version number for principal in key table is incorrect

When you meet this issue with enabling Kerberos log:export KRB5_TRACE=/krb5.txt, you might meet knvo inconsistent issue.

Fix solution:

Run below commands:
```
kdestory or rm -rf /etc/krb5.keytab
net ads keytab add HTTP -U Administrator
klist -k
```

## Kerberos log: KDC reply did not match expectations

When you meet this issue with enabling Kerberos log:export KRB5_TRACE=/krb5.txt, you might meet incorrect krb5.conf setting issue.

Fix solution:
> Edit /etc/krb5.conf, change lower domain name "corp.example.com" to upper domain name "CORP.EXAMPLE.COM"

## Kerberos log: Server not found in Kerberos database

When you meet this issue with enabling Kerberos log:export KRB5_TRACE=/krb5.txt, you might meet keytab setting issue.

Fix solution:

1. Run following 2 commands:
```
net ads keytab add HTTP -U Administrator 
realm --verbose join CONTOSO.COM -U Administrator
```

2. Check /etc/hosts, your content might like below(make sure '127.0.1.1       hostname' is correct and hostname is same with your host name, e.g. 'omi-ub14x64-b1'.):

```
root@omi-ub14x64-b1  # cat /etc/hosts
127.0.0.1       localhost
127.0.1.1       omi-ub14x64-b1

# The following lines are desirable for IPv6 capable hosts
::1     localhost ip6-localhost ip6-loopback
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters
```