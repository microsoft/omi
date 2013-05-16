//-----------------------------------------------------------------------
// <copyright file="omiserverConfigurationTests.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-klosli</author>
// <description>omiserver configuration test class</description>
// <history>01/25/2010 01:38:20 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Tests
{
    using System;
    using System.Threading;

    using Common;
    using Infra.Frmwrk;

    public class omiserverConfigurationTests : Utilities, ISetup
    {
        /// <summary>
        /// Temporary IConText method to use
        /// </summary>
        private IVarContext varContext;

        private ClientManager clientManager;

        /// <summary>
        /// Machine's information
        /// </summary>
        private SysInfo sys;

        /// <summary>
        /// Location of TestClient
        /// </summary>
        private string clientLocation;
        /// <summary>
        /// Type of client
        /// </summary>
        private string clientType;

        /// <summary>
        /// Namespace of test provider
        /// </summary>
        private string nameSpace;

        /// <summary>
        /// Class name of test provider
        /// </summary>
        private string className;

        private bool deepEnumeration;

        #region ISetup Members

        public void Setup(IContext ctx)
        {
            sys = new SysInfo
            {
                Hostname = ctx.Records.FindValue("hostName"),
                Username = ctx.Records.FindValue("rootUser"),
                Password = ctx.Records.FindValue("rootPassword"),
                IsHttps = Convert.ToBoolean(ctx.Records.FindValue("isHttps")),
                PortNumber = uint.Parse(ctx.Records.FindValue("portNumber")),
                XmlSchemaPrefix = ctx.Records.FindValue("xmlSchemaPrefix")
            };

            varContext = (IVarContext)ctx;
            logger = new McfLogger(ctx);

            clientLocation = ctx.Records.FindValue("testInstallerLocation");
            clientType = ctx.Records.FindValue("client");
            
            nameSpace = ctx.Records.FindValue("namespace");
            className = ctx.Records.FindValue("className");
            Boolean.TryParse(ctx.Records.FindValue("deepEnumeration"), out deepEnumeration);
        }

        #endregion


        /// <summary>
        /// Enumerate instance with wsman client
        /// </summary>
        /// <param name="connectionType">is Https or Http mode</param>
        /// <param name="connectionPortNumber">Connect to which port</param>
        /// <param name="exceptToPass">expected result of enumerate instance</param>
        public void EnumerateWithWsman(string connectionType, string connectionPortNumber, string expectToPass)
        {
            sys.PortNumber = uint.Parse(connectionPortNumber);
            clientManager = new ClientManager(clientType, logger, sys, clientLocation);

            bool expectEnumerateToPass;
            Boolean.TryParse(expectToPass, out expectEnumerateToPass);

            // Enumerate instance
            this.clientManager.Enumerate(nameSpace, className, deepEnumeration);

            // Detect error
            if (clientManager.Response.ToString().Contains("<OperationError>"))
            {
                if (expectEnumerateToPass == true)
                {
                    throw new VarFail(string.Format("Wsman enumerate instances failed! Connect type is {0}, Port number is {1}", connectionType, sys.PortNumber.ToString()));
                }
            }

        }

        /// <summary>
        /// Sleep timeout to verify server idletimeout
        /// </summary>
        /// <param name="timeout"></param>
        public void SleepForIdletimeout(string timeout)
        {
            Thread.Sleep(Int32.Parse(timeout) * 1000);
        }

        /// <summary>
        /// Verify option output for omiserver
        /// </summary>
        public void VerifyomiserverOptionOutput()
        {
            bool isPass = true;

            if (varContext.Records.HasKey("output"))
            {
                string actualOutput = varContext.FncRecords.FindValue("omiserverOutput");
                string[] expectOutputs = varContext.Records.GetValues("output");
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
                logger.WriteInfo("Verify the omiserver command with option pass");
            }
            else
            {
                throw new VarFail("Verify omiserver command with option failed");
            }
        }

        /// <summary>
        /// This function is used to verify omiserver start with no option
        /// </summary>
        /// <param name="startServerCommand">Command of start server with no option</param>
        /// <param name="verifyServerCommand">Command of verify server is up</param>
        public void VerifyOmiserverOptionWithMultiThread(string startServerCommand, string verifyServerCommand)
        {
            ParameterizedThreadStart startServer = this.StartomiserverWithNoOption;
            Thread runServerThread = new Thread(startServer);
            runServerThread.Start(startServerCommand);

            Thread.Sleep(30000);
            RunSshCommand(sys.Hostname, sys.Username, sys.Password, verifyServerCommand, true);
        }

        /// <summary>
        /// Thread function of start server
        /// </summary>
        /// <param name="command"></param>
        private void StartomiserverWithNoOption(object command)
        {
            if (command is string)
            {
                RunSshCommand(sys.Hostname, sys.Username, sys.Password, command as string, false,true);
            }
        }
    }

}
