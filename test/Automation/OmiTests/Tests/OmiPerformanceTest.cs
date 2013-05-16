//-----------------------------------------------------------------------
// <copyright file="OmiPerformanceTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-klosli</author>
// <description>OMI performance test class</description>
// <history>05/17/2010 01:38:20 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Tests
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Threading;
    using System.Xml.Linq;
    using Common;
    using Infra.Frmwrk;

    /// <summary>
    /// Parameters for create client
    /// </summary>
    struct ClientThreadParameters
    {
        public string clientType;
        public Logger logger;
        public SysInfo sysInfo;
        public string clientLocation;
        public string operation;
        public List<ClientAndOperationResult> resultInstances;
        public string nameSpace;
        public string className;
        public bool deepEnumeration;
        public int threadIndex;

        public ClientThreadParameters(
            string cliType,
            Logger logger,
            SysInfo sys,
            string cliLoc,
            string op,
            List<ClientAndOperationResult> resultInstances,
            string nameSpace,
            string className,
            bool deepEnumeration, int index)
        {
            this.clientType = cliType;
            this.logger = logger;
            this.sysInfo = sys;
            this.clientLocation = cliLoc;
            this.operation = op;
            this.resultInstances = resultInstances;
            this.nameSpace = nameSpace;
            this.className = className;
            this.deepEnumeration = deepEnumeration;
            this.threadIndex = index;
        }
    }

    /// <summary>
    /// Client thread class
    /// </summary>
    class ClientThread
    {
        private ClientThreadParameters cliParameters;
        private static object locker = new object();

        public ClientThread(ClientThreadParameters cliParams)
        {
            this.cliParameters = cliParams;
        }

        public void ClientOperation()
        {
            switch (cliParameters.operation)
            {
                case "enumerate":
                    ClientManager cliMng = new ClientManager(cliParameters.clientType, cliParameters.logger, cliParameters.sysInfo, cliParameters.clientLocation);
                    cliParameters.logger.WriteInfo("{0}-client-{1} is requesting data from server.", cliParameters.clientType, cliParameters.threadIndex);
                    cliMng.Enumerate(cliParameters.nameSpace, cliParameters.className, cliParameters.deepEnumeration);
                    IList<CimInstance> resultInstance;
                    cliMng.ConvertResponseToInstanceData(out resultInstance);
                    lock (locker)
                    {
                        cliParameters.resultInstances.Add(new ClientAndOperationResult(cliParameters.clientType, resultInstance));
                        cliParameters.logger.WriteInfo("{0}-client-{1} received data done.", cliParameters.clientType, cliParameters.threadIndex);
                    }
                    break;
                default:
                    throw new VarUnsupported(string.Format("Operation is not supported: {0}", cliParameters.operation));
            }
        }
    }

    /// <summary>
    /// to describe relationship for client type and operation result
    /// </summary>
    struct ClientAndOperationResult
    {
        public string cliType;
        public IList<CimInstance> operationResult;

        public ClientAndOperationResult(string cliType, IList<CimInstance> operationResult)
        {
            this.cliType = cliType;
            this.operationResult = operationResult;
        }
    }

    /// <summary>
    /// OMI Performance test class
    /// </summary>
    class PerformanceTest : Utilities, ISetup, IVerify
    {
        /// <summary>
        /// Machine information
        /// </summary>
        private SysInfo sys;

        /// <summary>
        /// Location of TestClient
        /// </summary>
        private string clientLocation;

        /// <summary>
        /// Type of clients. wsman or binary or both them
        /// </summary>
        private string[] clientToUse;

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

        private bool deepEnumeration;

        /// <summary>
        /// A list to contain all clients operation results
        /// </summary>
        private List<ClientAndOperationResult> actualAllInstances;

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
            actualAllInstances = new List<ClientAndOperationResult>();

            nameSpace = ctx.Records.FindValue("namespace");
            className = ctx.Records.FindValue("className");
            operation = ctx.Records.FindValue("operation");
            Boolean.TryParse(ctx.Records.FindValue("deepEnumeration"), out deepEnumeration);
        }

        #endregion

        #region IVerify Members

        public void Verify(IContext ctx)
        {
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

            bool isEqualed = true;
            // Verify each result for clients
            foreach (var actualInstance in actualAllInstances)
            {
                isEqualed &= (PerformanceTestVerify(verifyXmlFilePath, id, actualInstance.operationResult, logger, actualInstance.cliType));
                if (!isEqualed)
                    throw new VarFail("The results which we get aren't under our expected value");
            }
            this.logger.WriteInfo("The results which we get are under our expected value");
        }

        #endregion

        public bool PerformanceTestVerify(string verifyXmlFilePath,
                        string id,
                        IList<CimInstance> actualInstances,
                         Logger logger, string clientType)
        {
            List<CimInstance> expectedInstances = new List<CimInstance>();
            XDocument expectedXDocument = XDocument.Load(verifyXmlFilePath);

            if (expectedXDocument != null)
            {
                // Find the related xml result according to related Varmap file path and case Id
                XElement resultElement = expectedXDocument.Root.Elements("Result").SingleOrDefault(
                    e => e.Attribute("Id").Value == id);

                if (resultElement != null)
                {
                    IEnumerable<XElement> xmlElements = resultElement.Elements();
                    string xmlElementString = string.Empty;
                    foreach (XElement xmlElement in xmlElements)
                    {
                        // Demo_Performance class return 1000 instance
                        for (int i = 0; i < 1000; i++)
                        {
                            // construct expected instances here to avoid large amount duplicate instance place in Response.xml
                            xmlElement.Element("Properties").Element("CimProperty").SetValue(i.ToString());
                            xmlElementString = xmlElement.ToString();
                            CimInstance instance = XmlParser.FromXmlString<CimInstance>(xmlElementString);
                            if (instance != null)
                            {
                                expectedInstances.Add(instance);
                            }
                        }
                    }
                }
            }

            return VerificationHelper.CollectionEquals(actualInstances, expectedInstances, logger, clientType);
        }

        public void CreateMultiConnections(int countOfConnections, string clientType)
        {
            this.logger.WriteInfo("{0} connections will be created.", countOfConnections);
            clientToUse = clientType.Equals("random", StringComparison.OrdinalIgnoreCase) ? new[] { "binary", "wsman" } : new[] { clientType };

            Random random = new Random();
            List<Thread> clientThreads = new List<Thread>();
            for (int i = 1; i <= countOfConnections; i++)
            {
                int randomIndex = random.Next(clientToUse.Length);
                ClientThreadParameters cliParams = new ClientThreadParameters(
                    clientToUse[randomIndex],
                    logger,
                    sys,
                    clientLocation,
                    operation,
                    actualAllInstances,
                    nameSpace,
                    className,
                    deepEnumeration, i);

                ClientThread cliThread = new ClientThread(cliParams);
                Thread cli = new Thread(cliThread.ClientOperation);
                clientThreads.Add(cli);
                cli.Start();
            }

            foreach (var thread in clientThreads)
            {
                thread.Join();
            }
        }
    }
}



