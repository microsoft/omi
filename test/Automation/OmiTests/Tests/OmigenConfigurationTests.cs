`﻿//-----------------------------------------------------------------------
// <copyright file="OmigenConfigurationTests.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>sunilmu;v-erlv</author>
// <description></description>
// <history>1/25/2011 13:30:00 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Tests
{
    using Common;
    using Infra.Frmwrk;    

    /// <summary>
    /// omigen configuration test.
    /// </summary>
    public class omigenConfigurationTests : Utilities, ISetup
    {
        #region Private Fields

        /// <summary>
        /// SshHelper.
        /// </summary>
        private SshHelper sshHelper;

        /// <summary>
        /// Initialize IContext.
        /// </summary>
        private IContext context;

        #endregion

        /// <summary>
        /// Performs initial omigen configuration test setup.
        /// </summary>
        /// <param name="ctx">Initial context</param> 
        public void Setup(IContext ctx)
        {
            this.logger = new McfLogger(ctx);
            this.context = ctx;
            this.sshHelper = new SshHelper(
                ctx.Records.FindValue("hostName"), 
                ctx.Records.FindValue("rootUser"), 
                ctx.Records.FindValue("rootPassword"), 
                this.logger);
        }

        /// <summary>
        /// Verify that get result is correct.
        /// </summary>
        /// <param name="verification">For example : CheckForFiles/CheckForOutput</param>
        /// <param name="expectedResult">The expected result</param>
        /// <param name="target">target</param>
        public void VerifyResult(string verification, string expectedResult, string target)
        {
            switch (verification)
            {
                case "CheckForFiles":
                    this.CheckForFiles(expectedResult, target);
                    break;
                case "CheckForOutput":
                    this.CheckForOutput(expectedResult, target);
                    break;
                default:
                    break;
            }
        }

        /// <summary>
        /// Verify option output for omigen
        /// </summary>
        public void CheckomigenOptionOutputs()
        {
            bool isPass = true;

            if (context.Records.HasKey("output"))
            {
                string actualOutput = context.FncRecords.FindValue("omigenOutput");
                string[] expectOutputs = context.Records.GetValues("output");
                for (int i = 0; i < expectOutputs.Length; i++)
                {
                    if (!CompareResult(expectOutputs[i], actualOutput))
                    {
                        isPass = false;
                        break;
                    }
                }
            }

            if (isPass)
            {
                logger.WriteInfo("Verify the omigen command with option pass");
            }
            else
            {
                throw new VarFail("Verify omigen command with option failed");
            }
        }

        /// <summary>
        /// Verify that the expected files are exist.
        /// </summary>
        /// <param name="files">files name</param>
        /// <param name="path">path of the files</param>
        public void CheckForFiles(string files, string path)
        {
            string[] fileArr = files.Split(',');
            string command;
            for (int i = 0; i <= fileArr.Length - 1; i++)
            {
                command = string.Format("find {0} -name {1}", path, fileArr[i]);
                this.sshHelper.RunCmd(command);
                if (!this.sshHelper.StdOut.Contains(fileArr[i]))
                {
                    throw new VarFail(string.Format("Failed to get the expected file : {0}", fileArr[i]));
                }
                this.logger.WriteInfo(string.Format("Found the expected file : {0}", fileArr[i]));
            }
        }

        /// <summary>
        /// Verify that the expected content of file is exist.
        /// </summary>
        /// <param name="expectedString">the expected string</param>
        /// <param name="filePath">the path of the file</param>
        /// <param name="targetFileName">file name</param>   
        public void CheckForString(string expectedString, string filePath, string targetFileName)
        {
            string command = string.Format("grep \"{0}\" $(find {1} -name {2})", expectedString, filePath, targetFileName);
            this.sshHelper.RunCmd(command);
            if (!this.sshHelper.StdOut.Contains(expectedString))
            {
                throw new VarFail(string.Format("Failed to find the expected string : {0}", expectedString));
            }
            this.logger.WriteInfo(string.Format("Found the expected string : {0}", expectedString));
        }

        /// <summary>
        /// Verify that the expected output is right.
        /// </summary>
        /// <param name="expectedString">the expected string</param>
        /// <param name="command">file name</param>
        public void CheckForOutput(string expectedString, string command)
        {            
            this.sshHelper.RunCmd(command);
            if (!this.sshHelper.StdOut.Contains(expectedString))
            {
                throw new VarFail(string.Format("Failed to find the expected string : {0}", expectedString));
            }
            this.logger.WriteInfo(string.Format("Found the expected string : {0}", expectedString));
        }
    }
}
