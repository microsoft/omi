# Diagnosing OMI Problems

At times, OMI itself may experience problems, or OMI providers may
experience problems. This documentation will help customers collect
sufficient information for us to either assist in diagnosing problems
or allow the customer to isolate problems to specific providers, thus
allowing support staff to quickly route problems to the appropriate
team for support/resolution.

Note that this document is broken into several sections. Depending on
the nature of your problem, some sections may not be appropriate for
you. However, debugging problems definitely has some common themes.
Thus, common themes are covered first, and we then dealve into
specific problems.

To help Microsoft diagnose an OMI problem, Microsoft will minimally
need the information documented in
[Required information when reporting problems](#required-information-when-reporting-problems).
Additional information may be needed depending on the exact nature of
the problem. See [Common scenarios for OMI problems](#common-scenarios-for-omi-problems)
for additional information that Microsoft may require.

- [Minimum OMI version](#minimum-omi-version)
- [Caviats](#caviats)
- [Required information when reporting problems](#required-information-when-reporting-problems)
- [Enabling logging in OMI](#enabling-logging-in-omi)
- [Log file entries of interest](#log-file-entries-of-interest)
- [Common scenarios for OMI problems](#common-scenarios-for-omi-problems)
  - [Diagnosing memory problems in OMI itself](#diagnosing-memory-problems-in-omi-itself)
  - [Diagnosing omiserver or omiengine crashes](#dignosing-omiserver-or-omigngine-crashes)
  - [Diagnosing OMI Provider Failures](#diagnosing-omi-provider-failures)
    - [Diagnosing OMI Provider Memory Leaks](#diagnosing-omi-provider-memory-leaks)
    - [Diagnosing Unexpected OMI Provider aborts](#diagnosing-unexpected-omi-provider-aborts)

## Minimum OMI Version

**NOTE: This document assumes OMI v1.4.1-0 or later.** If you have a
prior version of OMI, we suggest you update to the latest version of
OMI available on the
[OMI releases](https://github.com/Microsoft/omi/releases)
page. The latest version of OMI should be able to be installed on top
of your existing OMI version with no significant negative consequences.

If you are unsure of what version of OMI you are running, you can run
`/opt/omi/bin/omiserver -v`, as indicated below:

```
jeffcof:~> /opt/omi/bin/omiserver -v
/opt/omi/bin/omiserver: OMI-1.4.1-0 - Mon Nov 13 16:14:30 PST 2017
jeffcof:~>
```

## Caviats

OMI v1.4.1-0 has some issues logged against it regarding logging:

1. Issue #322 - "Leaky" OMI providers can be difficult to isolate
2. Issue #449 - OMI logs ERROR message (NTLM creds) in normal case
3. Issue #450 - OMI logs warnings during enumeration in non-error cases
4. Issue #451 - OMI server configuration file needs to be cleaned up
5. Issue #452 - OMI Logging: OMI log file is MUCH too chatty in INFO mode

Issue #322 means that this document is primarily written to isolate
providers that are crashing or abnormally terminating. Providers that
are not crashing, but have other ill effects (excessive memory growth,
for example) are still difficult to isolate.

The remaining issues noted above means that OMI log files will grow
more than necessary, perhaps requiring log file rotation of OMI's log
files (via `logrotate` or a similar facility). This will be resolved
in a future release.

Finally, be aware that `EventId` identifiers in OMI tend to change
from release to release. Thus, they are not a good way to isolate
specific log file entries. As a result, this document will use `grep`
commands searching for text of log file entries rather than specific
`EventId` identifiers.

## Required information when reporting problems

In general, for Microsoft to diagnose OMI or OMI provider problems, we need the
following pieces of information:

1. The OMI version. Show us output from the command `/opt/omibin/omiserver -v`,
2. An exact description of the problem you are experiencing,
3. All log files from `/var/opt/omi/log`, with logging set to INFO mode
   (or above), when the problem was replicated,
4. If possible, steps to reproduce the problem.

Execution of `/opt/omi/bin/omiserver -v` should result in output similar to:

```
jeffcof:~> /opt/omi/bin/omiserver -v
/opt/omi/bin/omiserver: OMI-1.4.1-0 - Mon Nov 13 16:14:30 PST 2017
jeffcof:~>
```

If the problem you are experiencing is with a specific provider, we need to
know the provider registration name for the failing provider. See
[Diagnosing OMI Provider Failures](#diagnosing-omi-provider-failures)
for additional information on diagnosing provider problems and for how to
get this information from OMI.

Incomplete information will require Microsoft Support to reach out to the
customer for additional information. This will delay problem resolution.

The following sections provide far more detail on exactly what Microsoft
will need for problem analysis, and how to provide us with that information.

## Enabling logging in OMI

Currently, OMI requires logging set to the `INFO` level or higher in
order to diagnose problems. Since OMI's
`/etc/opt/omi/conf/omiserver.conf` file doesn't currently have the
logging entry in the configuration file, add the following lines to
`/etc/opt/omi/conf/omiserver.conf`:

```
##
## loglevel -- set the logging options for MI server
##   Valid options are: ERROR, WARNING, INFO, DEBUG, VERBOSE (debug build)
##   If commented out, then default value is: WARNING
##
loglevel = INFO
```

Logging is then controlled by commenting or uncommenting the
`loglevel = INFO` line with a `#` at the beginning of the line.

**Note:** After making changes to `/etc/opt/omi/conf/omiserver.conf`,
you must restart omi service for the changes to take effect. This can
be done with a command like: `sudo /opt/omi/bin/service_control
restart`.

**Note:** OMI log files can grow over time. To reduce the size of the
log files and simplify diagnosis of problems, you may wish to delete
existing log files before diagnosing your problem. This can be achieved
with commands like:

```
sudo /opt/omi/bin/service_control stop
sudo rm /var/opt/omi/log/*.log
sudo /opt/omi/bin/service_control start
```

## Log file entries of interest

In general, we need to see OMI activity. This activity would include:

1. Request/Operation (1 message),
2. Instance posted (0 or more messages), and
3. Actual result (MI_RESULT_OK, MI_RESULT_FAILED, etc) (1 message)

Furthermore, if a provider actually aborts, we should see a message
indicating this.

OMI has two log files of interest:

1. `/var/opt/omi/log/omiserver.log` represents server or engine log
   messages, and
2. `/var/opt/omi/log/omiagent.*.log` represents agent messages
   generated by provider operations.

Be aware that the exact name of the `omiagent.*.log` file depends on
the account that the agent is running under, which is determined by
the agent's registration file and the account performing the OMI
operation.

A sample log entry for the request/operation is (found in omiagent log):

```
2017/11/21 15:44:01 [79169,79169] INFO: null(0): EventId=40039 Priority=INFO New request received: command=(EnumerateInstancesReq), namespace=(root/scx), class=(SCX_Agent)
```

Note that this is currently logged as an INFO message. Thus, you must
have logging set to INFO or higher to see this message.

Currently, the instances posted and the actual result don't log in an
easy to retrieve mechanism. This will be resolved in a future OMI
release. However, we do log the following message when a request is
completely processed:

```
2017/11/21 15:44:02 [79169,79169] INFO: null(0): EventId=40011 Priority=INFO done with receiving msg(0x151d218:4099:EnumerateInstancesReq:3)
```

If you don't see an entry like the above (note that PID is shown in
square brackets), that likely indicates a crash or abnormal abort of
the provider.

## Common scenarios for OMI problems

### Diagnosing memory problems in OMI itself

OMI does have some diagnostic aids to assist in detection of memory
leaks in OMI itself (these would be in either `omiserver` or `omiengine`
processes). However, use of these aids requires not only a debug version
of OMI, but engineering expertise in interpreting the results. Thus, if
you believe you have diagnosed a memory leak on OMI itself (**not** in
`omiagent`, but in `omiserver` or `omiengine`), you'll need to engage
with Microsoft Support to help pin down the problem.

Do be aware that the OMI server/engine can grow based on load put upon
it, and this growth is normal. A memory leak would thus be considered
*unbound* memory growth such that OMI grows over time, without bound,
based on time the OMI server was running and under load. Such growth
can generally be seen over several days, regardless of load level.

*More details on specifics of memory leak diagnosis will be provided
at a future time.*

### Diagnosing omiserver or omiengine crashes

If the `omiserver` or `omiengine` processes crash unexpectedly, we
will need a `core` file with symbols. A special OMI installation
package can be made available upon request for an OMI installer with
symbols. These packages are not available on
[OMI Releases](https://github.com/Microsoft/omi/releases)
primarily due to size considerations.

Note that obtaining a `core` file can very from distribution to
distribution, and is beyond the scope of this document to describe.
Information on obtaining core files can be obtained from your Linux
vendor, or you can examine the
[Linux CORE Man Page](http://man7.org/linux/man-pages/man5/core.5.html).

### Diagnosing OMI Provider Failures

At times, OMI providers may fail. Please note that provider problems
do NOT indicate a problem in OMI itself, but in an OMI provider. Different
engineering teams can supply different providers to provide capabilities.

Since multiple OMI providers can be serviced using a single `omiagent`
process, it can be difficult to diagnose the exact provider that is
causing the source of the problem. This documentation is intended to
help diagnose what provider is triggering failures, allowing support
staff to quickly route problems to the appropriate team for
support/resolution.

There are two types of problems that providers commonly experience:

1. [Memory leaks](#diagnosing-omi-provider-memory-leaks)
2. [Unexpected provider aborts](#diagnosing-unexpected-omi-provider-aborts)
   (generally a "core" file for `SEGV` fault).

#### Diagnosing OMI Provider Memory Leaks

*Memory leaks detection diagnostic details will be provided at a
future time. OMI issue #322 ("Leaky" OMI providers can be difficult to
isolate) must first be resolved before these sorts of problems can be
easily diagnosed.*

#### Diagnosing Unexpected OMI Provider aborts

In general, it's best to look in `/var/opt/omi/log/omiagent.*.log` for
most messages.  However, if a provider aborts, the agent is no longer
around to log appropriate messages. Thus, additional information can
be found in `/var/opt/omi/log/omiserver.log`.

If an OMI provider aborts unexpectedly, a termination message will be
logged to `/var/opt/omi/log/omiserver.log`:

```
jeffcof> grep terminated /var/opt/omi/log/omiserver.log
2017/11/21 15:44:02 [79134,79134] WARNING: null(0): EventId=30209 Priority=WARNING child process with PID=[79169] terminated abnormally
jeffcof>
```

Note that the "terminated abnormally" message refers to the PID,
`[79169]`, which is shown in the *New request received* message,
detailed in [Log file entries of interest](#log-file-entries-of-interest):

```
2017/11/21 15:44:01 [79169,79169] INFO: null(0): EventId=40039 Priority=INFO New request received: command=(EnumerateInstancesReq), namespace=(root/scx), class=(SCX_Agent)
```

The complete log file for `omiagent.*.log` file, when two enumerations
are done and one aborts, is as follows:

```
jeffcof:log> cat omiagent.root.root.log 
2017/11/21 15:44:01 [79169,79169] INFO: null(0): EventId=40032 Priority=INFO Selector_AddHandler: selector=0x5bb2b8, handler=0x14e8740, name=BINARY_FROM_SOCKET
2017/11/21 15:44:01 [79169,79169] INFO: null(0): EventId=40032 Priority=INFO Selector_AddHandler: selector=0x5bb2b8, handler=0x5bb220, name=PROVMGR_TIMEOUT_MANAGER
2017/11/21 15:44:01 [79169,79169] INFO: null(0): EventId=40003 Priority=INFO agent started; fd 9
2017/11/21 15:44:01 [79169,79169] INFO: null(0): EventId=40011 Priority=INFO done with receiving msg(0x14e9268:15:BinProtocolNotification:1)
2017/11/21 15:44:01 [79169,79169] INFO: null(0): EventId=40011 Priority=INFO done with receiving msg(0x14ea018:4099:EnumerateInstancesReq:2)
2017/11/21 15:44:01 [79169,79169] INFO: null(0): EventId=40039 Priority=INFO New request received: command=(EnumerateInstancesReq), namespace=(root/scx), class=(SCX_Agent)
2017/11/21 15:44:02 [79169,79169] INFO: null(0): EventId=40011 Priority=INFO done with receiving msg(0x151d218:4099:EnumerateInstancesReq:3)
2017/11/21 15:44:02 [79169,79169] INFO: null(0): EventId=40039 Priority=INFO New request received: command=(EnumerateInstancesReq), namespace=(root/scx), class=(SCX_Agent)
jeffcof:log> 
```

The last three lines are most interesting. They indicate a provider
enumeration start, completion, and start (with no further messages).
This is a strong indicating of a provider abnormal termination, which
is verified by perusing `omiserver.log`:

```
jeffcof> grep terminated /var/opt/omi/log/omiserver.log
2017/11/21 15:44:02 [79134,79134] WARNING: null(0): EventId=30209 Priority=WARNING child process with PID=[79169] terminated abnormally
jeffcof>
```

When a specific provider fails, it helps Microsoft if we know the
provider registration name for the failing provider. Note, in the *New
request* message, we receive the namespace and class:

```
2017/11/21 15:44:01 [79169,79169] INFO: null(0): EventId=40039 Priority=INFO New request received: command=(EnumerateInstancesReq), namespace=(root/scx), class=(SCX_Agent)
```

Using this information, we can retrieve the provider registration
name. In the above message, the namespace is `root/scx` and the class
is `SCX_Agent`. To retrive the provider registration name, replace `/`
with `-` in the namespace and issue the following `grep` command
(substitute `SCX_Agent` with your class and `root-scx` with your
namespace):

```
jeffcof> grep -ri SCX_Agent /etc/opt/omi/conf/omiregister/root-scx/* | cut -f1 -d:
/etc/opt/omi/conf/omiregister/root-scx/SCXProvider-root.reg
jeffcof>
```

In this case, the provider registration name is `SCXProvider-root.reg`.

So, if a provider aborts, please supply Microsoft with the following
information:

1. All of the information described in
   [Required information when reporting problems](#required-information-when-reporting-problems),
2. Provider registration name, retrived as described above.
