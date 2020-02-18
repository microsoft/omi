## Authorization Feature

In April, 2018, the authorization feature was introduced to further control access to OMI.  This is done through two new parameters in omiserver.conf:  `AuthorizedGroups` and `UnauthorizedGroups`. This document describes how these two parameters should be used to limit access to OMI.

### Default Behavior

By default, if these two parameters have null values, or if the two parameter lines are commented out, no authorization is performed.  All authenticated users are granted access, maintaining backward compatibility with earlier behaviors.

### Syntax

Each of these authorization lines accepts a list of group names, separated by commas.  Group names can be local (i.e. defined in /etc/group), or domain groups.  Domain group names can either be in Windows domain format (Domain\Group) or the UPN format (Group@Domain).  For example:

    AuthorizedGroups=SCX\scx local admins, SCX\domain users, adm
    UnauthorizedGroups=games

### Recommended Usage

It's recommended that OMI be configured to use either *AuthorizedGroups*, or *UnauthorizedGroups*, but not both.  Furthermore, to have better control of users, create a local group instead of using domain groups.  A local Linux group can contain local users as well as domain users.  For example, one could create following in /etc/group:

    omi_access_group:x:1001:root, SCX\omi_test

#### To Grant Access to a Few Users

To allow OMI access to just a few users, for example, users *u1*, *u2*, and *u3*:

1. Create a local group in /etc/group:

    `omi_allowed_group:x:1001:u1, u2, u3`

2. Edit omiserver.conf and add following lines:

    AuthorizedGroups=omi_allowed_group

    UnauthorizedGroups=

3. Restart OMI

#### To Deny Access to a Few Users

To deny OMI access to just a few users, for example, users *u1*, *u2*, and *u3*:

1. Create a local group in /etc/group:

    `omi_denied_group:x:1002:u1, u2, u3`

2. Edit omiserver.conf and add following lines:

    AuthorizedGroups=

    UnauthorizedGroups=omi_denied_group

3. Restart OMI

### Conflict Resolution

If you wish to control access through both the *AuthorizedGroups* parameter and the *UnauthorizedGroups* parameter, and a conflict occurs, the general rule is that:

* `UnauthorizedGroups takes precedence over AuthorizedGroups`

For example, if a user x is both a member of groups g1, and g2, and following is in omiserver.conf:

    AuthorizedGroups=g1

    UnauthorizedGroups=g2

User x will always be denied since *UnauthorizedGroups* takes precedence.

### Caveat

For best results, be consistent in using either Windows domain format (i.e. Domain\Group), or the UPN format (i.e. Group@Domain). This is because on some platforms, it's been observed that if one logs in as SCX\omi_test, and /etc/group defines allowed_group to contain user omi_test@SCX.com, the Linux "id" command does not show the user as a member of allowed_group.  If one logs out and then back in as omi_test@SCX.com, then "id" command shows the correct group membership.

### Supported Platforms

Currently, only Linux and Mac platforms support this feature.


