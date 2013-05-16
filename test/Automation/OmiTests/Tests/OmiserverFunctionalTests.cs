//-----------------------------------------------------------------------
// <copyright file="OmiserverFunctionalTests.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-klosli</author>
// <description>Omiserver functional test class</description>
// <history>01/05/2010 01:38:20 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Tests
{
    using System;
    using System.Collections.Generic;
    using System.IO;

    using Common;
    using Infra.Frmwrk;

    public class OmiserverFunctionalTests : Utilities, ISetup, IRun, IVerify
    {
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

        /// <summary>
        /// Enumerate, Get, Invoke, Static invoke
        /// </summary>
        private string operation;
        /// <summary>
        /// Option of register provider
        /// </summary>
        private string hostingModel;

        private bool deepEnumeration;

        /// <summary>
        /// Method name for instance invoke
        /// </summary>
        private string instanceMethodName;

        /// <summary>
        /// Method name for static invoke
        /// </summary>
        private string staticMethodName;

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

            logger = new McfLogger(ctx);

            clientLocation = ctx.Records.FindValue("testInstallerLocation");
            clientType = ctx.Records.FindValue("client");
            clientManager = new ClientManager(clientType, logger, sys, clientLocation);
            nameSpace = ctx.Records.FindValue("namespace");
            className = ctx.Records.FindValue("className");
            operation = ctx.Records.FindValue("operation");
            hostingModel = ctx.Records.FindValue("hostingOption");
            instanceMethodName = ctx.Records.FindValue("instanceMethodName");
            staticMethodName = ctx.Records.FindValue("staticMethodName");
            Boolean.TryParse(ctx.Records.FindValue("deepEnumeration"), out deepEnumeration);
        }

        #endregion

        #region IRun Members

        /// <summary>
        /// We launch different client accroding to the client element in varmap, but we need to define an uniform interface for the client at first.
        /// Because now the clients(Binary and Wsman) are isolated with each other. 
        /// </summary>
        /// <param name="ctx"></param>
        public void Run(IContext ctx)
        {
            this.logger.WriteInfo("The Client type is {0}", clientType);
            this.logger.WriteInfo("The Operation is {0}", operation);
            this.logger.WriteInfo("The Hosting model is {0}", hostingModel);

            CimInstance cimInstance = new CimInstance { ClassName = className, Namespace = nameSpace, Properties = new List<CimProperty>() };
            CimProperty cimProperty = new CimProperty { IsKey = true, PropertyType = "UINT32", Name = "SN", Value = "1" };
            cimInstance.Properties.Add(cimProperty);

            switch (operation)
            {
                case "enumerate":
                    clientManager.Enumerate(nameSpace, className, deepEnumeration);
                    break;
                case "get":
                    clientManager.Get(cimInstance);
                    break;
                case "invoke":
                    List<MethodParameter> instanceMethoedParameters = new List<MethodParameter>();
                    MethodParameter instanceParams = new MethodParameter { Name="NewState", Value="2" };
                    instanceMethoedParameters.Add(instanceParams);
                    clientManager.InvokeInstanceMethod(cimInstance, instanceMethodName, instanceMethoedParameters);
                    break;
                case "staticinvoke":
                    List<MethodParameter> staticMethoedParameters = new List<MethodParameter>();
                    MethodParameter staticParams = new MethodParameter { Name = "NewValue", Value = "10" };
                    staticMethoedParameters.Add(staticParams);
                    clientManager.InvokeStaticMethod(nameSpace,className,staticMethodName,staticMethoedParameters);
                    break;
                default:
                    break;
            }
        }

        #endregion

        #region IVerify Members

        public void Verify(IContext ctx)
        {
            #region modification

            this.logger.WriteInfo("Test Verify");

            // Get the path of verifyXml
            string verifyXmlFilePath = ctx.Records.HasKey("verifyXmlRelativePath") ?
            ctx.Records.GetValue("verifyXmlRelativePath") : @"ExpectedResult\Response.xml";
            verifyXmlFilePath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, verifyXmlFilePath);

            IVarContext tempVarContext = (IVarContext)ctx;

            // Get case id
            string id = string.Format("{0}{1}{2}",
                                      tempVarContext.Set,
                                      tempVarContext.Level,
                                      tempVarContext.VarID);

            // Get actually instances from response
            IList<CimInstance> actualInstances;
            clientManager.ConvertResponseToInstanceData(out actualInstances);

            // Compare the actually instances with expect instances
            bool isEqualed = VerificationHelper.VerifyInstancesData(verifyXmlFilePath, id, actualInstances, logger, clientType);
            if (isEqualed)
            {
                this.logger.WriteInfo("The results which we get are under our expected value");
            }
            else
            {
                throw new VarFail("The results which we get aren't under our expected value");
            }
            #endregion
        }

        #endregion
    }
}
