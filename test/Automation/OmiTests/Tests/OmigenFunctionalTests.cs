//-----------------------------------------------------------------------
// <copyright file="omigenFunctionalTests.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>sunilmu;v-erlv</author>
// <description></description>
// <history>1/20/2011 9:30:00 AM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Tests
{
    using System;

    using Common;
    using Infra.Frmwrk;

    /// <summary>
    /// omigen funcational test.
    /// </summary>
    public class omigenFuncationalTests : Utilities, ISetup
    {
        #region Private Fields

        /// <summary>
        /// SshHelper.
        /// </summary>
        private SshHelper sshHelper;

        /// <summary>
        /// Get SO file after running correctly make command .
        /// </summary>
        private string providerBinaryFileName;

        /// <summary>
        /// The path is used to compile the MOF file.
        /// </summary>
        private string buildPath;

        /// <summary>
        /// reaname the provider classname;
        /// </summary>
        private string renameProviderClassname;

        #endregion

        /// <summary>
        /// Performs initial omigen functionnal test  setup.
        /// </summary>
        /// <param name="ctx">Initial context</param> 
        public void Setup(IContext ctx)
        {
            this.logger = new McfLogger(ctx);
            this.sshHelper = new SshHelper(
                ctx.Records.FindValue("hostName"),
                ctx.Records.FindValue("rootUser"),
                ctx.Records.FindValue("rootPassword"),
                this.logger);
            this.providerBinaryFileName = ctx.Records.FindValue("providerBinaryFileName");
            this.buildPath = ctx.Records.FindValue("buildPath");
            this.renameProviderClassname = ctx.Records.FindValue("renameProviderClassname");
        }

        /// <summary>
        /// Run command make and Verify that it compiles correctly.
        /// </summary>
        public void BuildAndVerify()
        {
            string expectedProviderBinaryFile = string.Format("lib{0}.so", this.providerBinaryFileName);
            string verifyCmd = string.Format("ls {0} | grep {1}", this.buildPath, expectedProviderBinaryFile);
            string makeCmd = string.Format("cd {0};make", this.buildPath);
            try
            {
                this.sshHelper.RunCmd(makeCmd);
            }
            catch (Exception ex) 
            {
                this.logger.WriteError(string.Format("Failed to run command: {0} . <<Exception>> : {1}", makeCmd, ex.Message));
            }

            this.sshHelper.RunCmd(verifyCmd);
            if (!this.sshHelper.StdOut.Contains(expectedProviderBinaryFile))
            {
                throw new VarFail(string.Format("Failed to get expected {0}", expectedProviderBinaryFile));
            }
        }

        /// <summary>
        /// Verify file contents 
        /// </summary>
        /// <param name="command">Linux/unix command</param>
        /// <param name="expectedString">Get the expected string after running the command</param>
        public void VerifyFileContents(string command,string expectedString)
        {
            string grepCmd = command;
            sshHelper.RunCmd(grepCmd);
            if (!sshHelper.StdOut.Contains(expectedString))
            {
                throw new VarFail(string.Format("Failed to get expected \"{0}\"", expectedString));
            }
        }
    }
}
