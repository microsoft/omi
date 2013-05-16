//-----------------------------------------------------------------------
// <copyright file="GroupHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>sunilmu</author>
// <description></description>
// <history>12/1/2010 3:59:57 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using Infra.Frmwrk;

    /// <summary>
    /// Interface for groups.
    /// </summary>
    public class GroupHelper : Utilities, ISetup
    {
        void ISetup.Setup(IContext ctx)
        {
            this.logger = new McfLogger(ctx);
        }
    }
}
