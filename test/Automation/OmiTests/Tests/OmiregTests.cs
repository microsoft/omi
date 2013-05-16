//-----------------------------------------------------------------------
// <copyright file="omiregTests.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>sunilmu;v-mayz</author>
// <description></description>
// <history>1/12/2011 1:30:11 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Tests
{
    using System;
    using System.Collections;
    using System.Linq;
    using System.Xml;
    using System.Xml.Linq;

    using Common;
    using Infra.Frmwrk;

    /// <summary>
    /// This class contains the automation for omireg configuration and functional tests.
    /// </summary>
    public class omiregTests : Utilities, ISetup
    {
        #region Private Fields
        /// <summary>
        /// Output from the enumeration operation.
        /// </summary>
        private string enumOutput;
        /// <summary>
        /// Contains omiagent related data.
        /// </summary>
        private ArrayList agentProcesses;
        /// <summary>
        /// IConText temp for all method to use .
        /// </summary>
        private IVarContext varContext;
        /// <summary>
        /// OMI install folder. 
        /// </summary>
        private string omiinstalledFolder;
        /// <summary>
        /// provider register host mode.
        /// </summary>
        private string regHostingOption;
        /// <summary>
        /// provider register namespace.
        /// </summary>
        private string regNameSpace;
        /// <summary>
        /// System info for test.
        /// </summary>
        private SysInfo sysInfo;
        /// <summary>
        /// Explicite user when enum an instance.
        /// </summary>
        private string expliciteUser;
        /// <summary>
        /// Explicite password.
        /// </summary>
        private string explicitePwd;
        /// <summary>
        /// incidite if or not use explicite user.
        /// </summary>
        private bool useExpliciteUser;
        /// <summary>
        /// Test Client Type.
        /// </summary>
        private string clientType;
        /// <summary>
        /// Test Client for very the omireg result.
        /// </summary>
        private ClientManager clientManager;
        /// <summary>
        /// Class to contain omiagent process related data.
        /// </summary>
        private class ProcessInfo
        {
            /// <summary>
            /// Gets or sets process user value
            /// </summary>
            public string Name { get; set; }
            /// <summary>
            /// Gets or sets Process PID value
            /// </summary>
            public string Id { get; set; }
        }

        #endregion

        /// <summary>
        /// Test Environment preparation
        /// </summary>
        /// <param name="ctx">MCF Context</param>
        public void Setup(IContext ctx)
        {
            this.agentProcesses = new ArrayList();
            this.sysInfo = new SysInfo();
            logger = new McfLogger(ctx);
            this.varContext = (IVarContext)ctx;
            this.sysInfo.Hostname = this.varContext.Records.FindValue("hostName");
            this.sysInfo.Username = this.varContext.Records.FindValue("rootUser");
            this.sysInfo.Password = this.varContext.Records.FindValue("rootPassword");
            logger.WriteInfo(
                "Test Environment credentials info:\r\n hostName: {0} \r\n connectUser: {1}",
                this.sysInfo.Hostname,
                this.sysInfo.Username);
            this.useExpliciteUser = false;
            this.omiinstalledFolder = this.varContext.Records.FindValue("omiInstallFolder");
            this.clientType = this.varContext.Records.FindValue("clientType");
            this.clientManager = new ClientManager(this.clientType, logger, this.sysInfo, this.omiinstalledFolder + "/bin/TestClient");
            this.RetrieveRegisterInfo();
        }

        /// <summary>
        /// Enumerate the test class using binary client.
        /// </summary>
        public void EnumerateTestClass()
        {
            string className = this.varContext.Records.GetValue("classname");
            if (string.IsNullOrEmpty(className))
            {
                throw new ArgumentNullException("Classname should not be null or empty in ei request!");
            }

            bool deep = this.varContext.Records.HasKey("deep");
            string testClientLocat = this.omiinstalledFolder + "/bin/TestClient";
            if (this.varContext.Records.HasKey("credentialInfo"))
            {
                IRecords[] credentialRcs = this.varContext.Records.GetSubRecords("credentialInfo");
                foreach (IRecords credentialRc in credentialRcs)
                {
                    if (credentialRc.HasKey("connectionUser"))
                    {
                        this.sysInfo.Username = credentialRc.GetValue("connectionUser");
                    }

                    if (credentialRc.HasKey("connectionPwd"))
                    {
                        this.sysInfo.Password = credentialRc.GetValue("connectionPwd");
                    }

                    if (credentialRc.HasKey("explicitUser") && credentialRc.HasKey("explicitPwd"))
                    {
                        this.useExpliciteUser = true;
                        this.expliciteUser = credentialRc.GetValue("explicitUser");
                        this.explicitePwd = credentialRc.GetValue("explicitPwd");
                        testClientLocat += " -u " + this.expliciteUser + " -p " + this.explicitePwd;
                    }
                }
            }

            this.clientManager = new ClientManager(this.clientType, logger, this.sysInfo, testClientLocat);

            // Ignore exception here for we will verify the return message in verification step .
            try
            {
                this.clientManager.Enumerate(this.regNameSpace, className, deep);
            }
            finally
            {
                this.enumOutput = this.clientManager.Response.ToString();
            }
        }

        /// <summary>
        /// Verify the output from the enumerate operation.
        /// </summary>
        public void VerifyEnumOutput()
        {
            if (this.varContext.Records.HasKey("output"))
            {
                string[] expectResults = this.varContext.Records.GetValues("output");
                XDocument actualXML = XDocument.Parse(this.enumOutput);
                string actualResult = actualXML.Root.Value;
                bool verifyPass = true;
                for (int i = 0; i < expectResults.Length; i++)
                {
                    if (!actualResult.Contains(expectResults[i]))
                    {
                        verifyPass = false;
                        break;
                    }
                }

                if (verifyPass)
                {
                    logger.WriteInfo("Verify Enum Ouput result Pass");
                    return;
                }

                throw new VarFail("Failed in verify enum output result");
            }
            else
            {
                this.VerifyProcessDetails();
            }
        }

        /// <summary>
        /// Verify omiagent process info when run Repeat times.
        /// </summary>
        public void VerifyRepeatEnumOmiagentProcessInfo()
        {
            ProcessInfo responsePs = this.RetrievePsInfoFromEnumOuput();
            this.EnumerateTestClass();
            ProcessInfo currentPs = this.RetrievePsInfoFromEnumOuput();
            if (responsePs.Id == currentPs.Id && responsePs.Name == currentPs.Name)
            {
                logger.WriteInfo("Repeat enum instance with no interleave will not create new agent process");
            }
        }

        /// <summary>
        /// Verify the omireg command with option output 
        /// </summary>
        public void VerifyomiregOptionOutput()
        {
            bool isPass = true;
            try
            {
                if (varContext.Records.HasKey("output"))
                {
                    string acutalOutput = varContext.FncRecords.FindValue("omiregOutput");
                    if (string.IsNullOrEmpty(acutalOutput))
                    {
                        throw new VarFail("Verify omireg command with option failed");
                    }

                    string[] expectOutputs = varContext.Records.GetValues("output");
                    isPass = expectOutputs.All(output => CompareResult(output, acutalOutput));
                }

                if (isPass)
                {
                    logger.WriteInfo("Verify the omireg command with option pass");
                }
                else
                {
                    throw new VarFail("Verify omireg command with option failed");
                }
            }
            catch (Exception ex)
            {

                throw new VarAbort("Verify omireg command with option abort with unknown reason.", ex);
            }
        }

        /// <summary>
        /// Retrieve register provider info.
        /// </summary>
        private void RetrieveRegisterInfo()
        {
            this.regNameSpace = this.varContext.Records.FindValue("regNameSpace");
            this.regHostingOption = string.Empty;
            if (this.varContext.Records.HasKey("regInfo"))
            {
                IRecords[] rcs = this.varContext.Records.GetSubRecords("regInfo");
                foreach (IRecords rc in rcs)
                {
                    if (rc.HasKey("namespace"))
                    {
                        this.regNameSpace = rc.GetValue("namespace");
                    }

                    if (rc.HasKey("hostingOption"))
                    {
                        this.regHostingOption = rc.GetValue("hostingOption");
                    }
                }
            }
        }

        /// <summary>
        /// Retrives all agent process and store their detail infos
        /// </summary>
        private void GetOmiAgentProcessDetails()
        {
            string omiAgentPsCommand = this.varContext.Records.FindValue("omiagentPsGrepCmd");
            if (string.IsNullOrEmpty(omiAgentPsCommand))
            {
                throw new VarAbort("Can not found omiagentPsGrepCmd record in varmap.");
            }

            string outPutResult = RunSshCommand(this.sysInfo.Hostname, this.sysInfo.Username, this.sysInfo.Password, omiAgentPsCommand, true, true);
            outPutResult = outPutResult.TrimStart();
            if (!string.IsNullOrEmpty(outPutResult))
            {
                this.agentProcesses.Clear();
                ProcessInfo psInfo = new ProcessInfo();
                string[] psArray = outPutResult.Split('\n');
                for (int indexps = 0; indexps < psArray.Length; indexps++)
                {
                    string psItem = psArray[indexps];
                    if (psItem.Length <= 3)
                    {
                        continue;
                    }

                    string[] psItemInfoArray = psItem.Split(' ');
                    psInfo.Name = psItemInfoArray[0];
                    for (int indexDetail = 1; indexDetail < psItemInfoArray.Length; indexDetail++)
                    {
                        if (psItemInfoArray[indexDetail] != string.Empty)
                        {
                            psInfo.Id = psItemInfoArray[indexDetail];
                            break;
                        }
                    }

                    this.agentProcesses.Add(psInfo);
                }
            }
        }

        /// <summary>
        /// Retrieve omiagent process info from enum result
        /// </summary>
        /// <returns>omiagent process for enum opreation</returns>
        private ProcessInfo RetrievePsInfoFromEnumOuput()
        {
            ProcessInfo responsePsInfo = null;
            if (!string.IsNullOrEmpty(this.enumOutput) && !this.enumOutput.Contains("</Root>"))
            {
                throw new VarFail("Enum instance operation failed");
            }

            try
            {
                XElement responseXml = XElement.Parse(this.enumOutput);
                var cimProperties = responseXml.Descendants("CimProperty");
                var pidNode = cimProperties.FirstOrDefault(item => item.Attribute("Name").Value == "pid");
                if (pidNode != null)
                {
                    responsePsInfo = new ProcessInfo();
                    responsePsInfo.Id = pidNode.Value;
                    responsePsInfo.Name = cimProperties.FirstOrDefault(item => item.Attribute("Name").Value == "user").Value;
                }
            }
            catch (XmlException xmlEx)
            {
                throw xmlEx;
            }

            return responsePsInfo;
        }

        /// <summary>
        /// Retrive the omiserver process info
        /// </summary>
        /// <returns>omiserver process info</returns>
        private ProcessInfo GetServerPsInfo()
        {
            ProcessInfo psInfo = null;
            string pscmd = this.varContext.Records.FindValue("omiserverPsGrepCmd");
            if (string.IsNullOrEmpty(pscmd))
            {
                throw new VarAbort("Can not found omiserverPsGrepCmd record in varmap.");
            }

            string responses = RunSshCommand(this.sysInfo.Hostname, this.sysInfo.Username, this.sysInfo.Password, pscmd, true, true);
            if (!string.IsNullOrEmpty(responses))
            {
                psInfo = new ProcessInfo();
                responses = responses.TrimStart();
                string[] psinfo = responses.Split(' ');
                psInfo.Name = psinfo[0];
                for (int i = 1; i < psinfo.Length; i++)
                {
                    if (psinfo[i] != string.Empty)
                    {
                        psInfo.Id = psinfo[i];
                        break;
                    }
                }
            }

            return psInfo;
        }

        /// <summary>
        /// Use predetermined rules to verify if the correct omiagent was created (unless in-proc was used).
        /// </summary>
        private void VerifyProcessDetails()
        {
            bool verifyPass = false;
            this.agentProcesses.Clear();
            this.GetOmiAgentProcessDetails();
            ProcessInfo responsePs = this.RetrievePsInfoFromEnumOuput();
            if (responsePs == null)
            {
                throw new VarFail("Enum operation response has no ps info.");
            }

            switch (this.regHostingOption)
            {
                case "":
                case "@inproc@":
                    ProcessInfo serverPsInfo = this.GetServerPsInfo();
                    if (serverPsInfo.Id == responsePs.Id && serverPsInfo.Name == responsePs.Name)
                    {
                        verifyPass = true;
                    }

                    break;
                case "@requestor@":
                    if (this.agentProcesses.Count != 0)
                    {
                        foreach (ProcessInfo ps in this.agentProcesses)
                        {
                            if (ps.Id == responsePs.Id && ps.Name == responsePs.Name)
                            {
                                if (this.useExpliciteUser)
                                {
                                    if (ps.Name == this.expliciteUser)
                                    {
                                        verifyPass = true;
                                    }
                                }
                                else if (ps.Name == this.sysInfo.Username)
                                {
                                    verifyPass = true;
                                }
                            }
                        }
                    }

                    break;
                default:
                    if (!string.IsNullOrEmpty(this.regHostingOption) && this.agentProcesses.Count != 0)
                    {
                        foreach (ProcessInfo ps in this.agentProcesses)
                        {
                            if (ps.Id == responsePs.Id && ps.Name == responsePs.Name && ps.Name == this.regHostingOption)
                            {
                                verifyPass = true;
                            }
                        }
                    }

                    break;
            }

            if (verifyPass)
            {
                logger.WriteInfo("Verify omiagent process info pass.");
            }
            else
            {
                throw new VarFail("Failed when verifying omiagent process info");
            }
        }
    }
}
