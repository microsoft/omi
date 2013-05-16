//-----------------------------------------------------------------------
// <copyright file="WsmanQuery.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>sunilmu</author>
// <description>Wrapper for accessing OMI via WSMan</description>
// <history>10/28/2010 10:30:00 AM: Modified - Removed hardcoded strings, added logging abstraction, refactored</history>
// <history>10/29/2010 10:00:00 AM: Modified - Remove external references, and make it support all OMI features</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using System;
    using System.Collections.Generic;
    using System.Runtime.InteropServices;
    using System.Xml;
    using WSManAutomation;

    /// <summary>
    /// The WsmanQuery class encapsulates methods for performing Web 
    /// Service Management operations on a Posix host.
    /// </summary>
    public class WsmanQuery
    {
        #region Properties
        public Logger Log { get; set; }

        public string Hostname { get; set; }

        public string Username { get; set; }

        public string Password { get; set; }

        public uint Port { get; set; }

        public string XmlSchemaPrefix { get; set; }

        public string XmlSchemaSuffix { get; set; }

        public bool HttpsMode { get; set; }

        #endregion Properties

        #region Constructors

        /// <summary>
        /// Initializes a new instance of the WsmanQuery class.
        /// </summary>
        /// <param name="logger">The logger interface</param>
        /// <param name="hostName">Name or IP address of the Posix system</param>
        /// <param name="userName">Valid user name for the Posix system</param>
        /// <param name="password">Password for the username</param>
        /// <param name="portNumber">port number of host</param>
        /// <param name="schemaPrefix">xml prefix</param>
        /// <param name="schemaSuffix">xml suffix</param>
        /// <param name="isHttps">whether the port is for https</param>
        public WsmanQuery(Logger logger, string hostName, string userName, string password, uint portNumber, string schemaPrefix, string schemaSuffix, bool isHttps)
        {
            this.Log = logger;
            this.Hostname = hostName;
            this.Username = userName;
            this.Password = password;
            this.Port = portNumber;
            this.XmlSchemaPrefix = schemaPrefix;
            this.XmlSchemaSuffix = schemaSuffix;
            this.HttpsMode = isHttps;
        }

        #endregion Constructors

        #region Methods

        #region Public Methods

        /// <summary>
        /// Execute a WSMAN query against a Posix system in the root/scx namespace.
        /// </summary>
        /// <param name="queryXml">Results of WSMAN query in XML format</param>
        /// <param name="queryClass">Class in root/scx namespace to query</param>
        public void EnumerateScx(out List<string> queryXml, string queryClass)
        {
            queryXml = new List<string>();
            WSMan webSvcMan = new WSMan();

            int enumFlag = webSvcMan.EnumerationFlagReturnObject();
            try
            {
                IWSManSession session = this.GetWSMANSession(queryClass);

                // Construct XML namespace URI
                string strResourceLocator = string.Concat(this.XmlSchemaPrefix, queryClass, this.XmlSchemaSuffix);
                IWSManResourceLocator resourceLocator = (IWSManResourceLocator)webSvcMan.CreateResourceLocator(strResourceLocator);

                IWSManEnumerator enumerator = (IWSManEnumerator)session.Enumerate(resourceLocator, string.Empty, string.Empty, enumFlag);

                while (enumerator.AtEndOfStream == false)
                {
                    queryXml.Add(enumerator.ReadItem());
                }
            }
            catch (COMException ce)
            {
                this.HandleWSMANException(ce, queryClass, webSvcMan);
            }
        }

        /// <summary>
        /// Execute a WSMAN query against a Posix system in the root/scx namespace.
        /// </summary>
        /// <param name="queryXml">Results of WSMAN query in XML format</param>
        /// <param name="queryClass">Class in root/scx namespace to query</param>
        /// <param name="keyValuePair">A key/value pair for the resource locator string.</param>
        public void GetScx(out string queryXml, string queryClass, string keyValuePair)
        {
            queryXml = string.Empty;
            WSMan webSvcMan = new WSMan();

            int getFlag = 0;

            try
            {
                IWSManSession session = this.GetWSMANSession(queryClass);

                // Construct XML namespace URI
                string strResourceLocator = string.Concat(this.XmlSchemaPrefix, queryClass, this.XmlSchemaSuffix, "+", keyValuePair);
                IWSManResourceLocator resourceLocator = (IWSManResourceLocator)webSvcMan.CreateResourceLocator(strResourceLocator);

                string getOutput = session.Get(resourceLocator, getFlag);
                queryXml = getOutput;
                this.Log.WriteInfo("output of get " + getOutput);
            }
            catch (COMException ce)
            {
                this.HandleWSMANException(ce, queryClass, webSvcMan);
            }
        }

        /// <summary>
        /// Execute a WSMAN invoke against a Posix system in the root/scx namespace.
        /// </summary>
        /// <param name="result">Output parameter containing the XML-encoded result of the invocation.</param>
        /// <param name="queryClass">Query class (provider) to use, e.g. SCX_OperatingSystem</param>
        /// <param name="invokeMethod">The invoke method, e.g. ExecuteCommand</param>
        /// <param name="parameters">The WSMAN parameter string</param>
        public void InvokeScx(out string result, string queryClass, string invokeMethod, string parameters)
        {
            result = string.Empty;
            WSMan webSvcMan = new WSMan();

            try
            {
                IWSManSession session = this.GetWSMANSession(queryClass);

                // Construct XML namespace URI
                string strResourceLocator = string.Concat(this.XmlSchemaPrefix, queryClass, this.XmlSchemaSuffix);
                IWSManResourceLocator resourceLocator = (IWSManResourceLocator)webSvcMan.CreateResourceLocator(strResourceLocator);

                result = session.Invoke(invokeMethod, resourceLocator, parameters, 0);
                this.Log.WriteInfo("output of get " + result);
            }
            catch (COMException ce)
            {
                this.HandleWSMANException(ce, queryClass, webSvcMan);
            }
        }

        /// <summary>
        /// Helper method to run a posix style command on the remote client using WSMAN, handling normal error conditions following a command
        /// execution.
        /// </summary>
        /// <param name="result">Output parameter containing the contents of stdout</param>
        /// <param name="queryClass">Query class (provider) to use, e.g. SCX_OperatingSystem</param>
        /// <param name="invokeMethod">The invoke method, e.g. ExecuteCommand</param>
        /// <param name="parameters">The WSMAN parameter string</param>
        public void InvokeCommand(out string result, string queryClass, string invokeMethod, string parameters)
        {
            result = string.Empty;
            string resultRawXml = string.Empty;

            this.InvokeScx(out resultRawXml, queryClass, invokeMethod, parameters);

            XmlDocument resultXml = new XmlDocument();
            resultXml.LoadXml(resultRawXml);
            XmlElement resultXmlRoot = resultXml.DocumentElement;

            XmlNodeList nodeList = resultXmlRoot.GetElementsByTagName("n1:ReturnCode");

            if (nodeList.Count > 0)
            {
                string returnCode = nodeList[0].InnerText.Trim();

                if (returnCode != "0")
                {
                    this.Log.WriteInfo("InvokeScx: returnCode = " + returnCode);
                }
            }

            nodeList = resultXmlRoot.GetElementsByTagName("n1:StdErr");

            if (nodeList.Count > 0)
            {
                string stdErr = nodeList[0].InnerText.Trim();

                if (stdErr.Contains("Permission denied"))
                {
                    this.Log.WriteInfo("InvokeScx: stderr contains 'Permission denied'");
                }
            }

            nodeList = resultXmlRoot.GetElementsByTagName("n1:StdOut");

            if (nodeList.Count > 0)
            {
                result = nodeList[0].InnerText.Trim();
                this.Log.WriteInfo("InvokeScx: result = " + result);
            }
        }

        /// <summary>
        /// Run the WSMAN invocation for executing a a given command on the remote client.
        /// </summary>
        /// <param name="result">Output parameter containing the contents of stdout</param>
        /// <param name="command">Command to run on the remote client</param>
        /// <param name="timeout">Timeout in seconds for the execution</param>
        public void InvokeExecuteCommand(out string result, string command, string timeout)
        {
            string xmlns = "_INPUT xmlns:p=\"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/SCX_OperatingSystem.xsd\">";

            string parameters = string.Concat(
                "<p:ExecuteCommand",
                xmlns,
                "<p:command>",
                command,
                "</p:command><p:timeout>",
                timeout,
                "</p:timeout></p:ExecuteCommand_INPUT>");

            this.InvokeCommand(out result, "SCX_OperatingSystem", "ExecuteCommand", parameters);
        }

        /// <summary>
        /// Run the WSMAN invocation for executing a a given shell command on the remote client.
        /// </summary>
        /// <param name="result">Output parameter containing the contents of stdout</param>
        /// <param name="command">Command to run on the remote client</param>
        /// <param name="timeout">Timeout in seconds for the execution</param>
        public void InvokeExecuteShellCommand(out string result, string command, string timeout)
        {
            string xmlns = "_INPUT xmlns:p=\"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/SCX_OperatingSystem.xsd\">";

            string parameters = string.Concat(
                "<p:ExecuteShellCommand",
                xmlns,
                "<p:command>",
                command,
                "</p:command><p:timeout>",
                timeout,
                "</p:timeout></p:ExecuteShellCommand_INPUT>");

            this.InvokeCommand(out result, "SCX_OperatingSystem", "ExecuteShellCommand", parameters);
        }

        /// <summary>
        /// Run the WSMAN invocation for executing a given script on the remote client
        /// </summary>
        /// <param name="result">Output parameter containing the contents of stdout</param>
        /// <param name="script">Contents of the script to be run.</param>
        /// <param name="timeout">Timeout in seconds for the execution</param>
        public void InvokeExecuteScript(out string result, string script, string timeout)
        {
            string xmlns = "_INPUT xmlns:p=\"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/SCX_OperatingSystem.xsd\">";
            string parameters = string.Concat(
                "<p:ExecuteScript",
                xmlns,
                "<p:script>",
                script,
                "</p:script><p:arguments></p:arguments><p:timeout>",
                timeout,
                "</p:timeout></p:ExecuteScript_INPUT>");

            this.InvokeCommand(out result, "SCX_OperatingSystem", "ExecuteScript", parameters);
        }

        /// <summary>
        /// Run the WSMAN invocation to retrieve a list of processes using the most resources
        /// </summary>
        /// <param name="result">Output parameter for the plaintext result of the invocation</param>
        /// <param name="resource">The resource type, for example 'CPUTime'</param>
        /// <param name="count">The length of the list of processes to retrieve</param>
        public void InvokeTopResourceConsumers(out string result, string resource, string count)
        {
            string xmlns = "_INPUT xmlns:p=\"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/SCX_UnixProcess.xsd\">";

            string parameters = string.Concat(
                "<p:TopResourceConsumers",
                xmlns,
                "<p:resource>",
                resource,
                "</p:resource><p:count>",
                count,
                "</p:count></p:TopResourceConsumers_INPUT>");

            this.InvokeCommand(out result, "SCX_UnixProcess", "TopResourceConsumers", parameters);
        }

        /// <summary>
        /// Run the WSMAN invocation to retrieve matched log file rows
        /// </summary>
        /// <param name="results">Output parameter for an array of strings, each containing a plaintext row from the logfiel (stripped of XML tags)</param>
        /// <param name="fileName">Full path to the log file being polled</param>
        /// <param name="regexp">A regular expression with which to examine the log file</param>
        /// <param name="qid">The 'qid'.  This is the hostname of the server generating the WSMAN, and is usually 'localhost'</param>
        public void InvokeGetMatchedRows(out string[] results, string fileName, string regexp, string qid)
        {
            string xmlns = "_INPUT xmlns:p=\"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/SCX_LogFile.xsd\">";

            results = new string[0];
            int matchesFound = 0;

            string parameters = string.Concat(
                "<p:GetMatchedRows",
                xmlns,
                "<p:filename>",
                fileName,
                "</p:filename><p:regexps>",
                regexp,
                "</p:regexps><p:qid>",
                qid,
                "</p:qid></p:GetMatchedRows_INPUT>");

            string resultRawXml = string.Empty;

            try
            {
                this.InvokeScx(out resultRawXml, "SCX_LogFile", "GetMatchedRows", parameters);
            }
            catch (Exception e)
            {
                this.Log.WriteError("InvokeGetMatchedRows failed: " + e.Message);
                return;
            }

            XmlDocument resultXml = new XmlDocument();
            resultXml.LoadXml(resultRawXml);
            XmlElement resultXmlRoot = resultXml.DocumentElement;

            XmlNodeList nodeList = resultXmlRoot.GetElementsByTagName("n1:ReturnValue");
            if (nodeList.Count > 0)
            {
                string returnValue = nodeList[0].InnerText.Trim();

                if (returnValue == "0")
                {
                    return;
                }
            }
            else
            {
                return;
            }

            nodeList = resultXmlRoot.GetElementsByTagName("n1:rows");
            matchesFound = nodeList.Count;

            if (matchesFound > 0)
            {
                int rowOffset = 0;

                // If a regular expression is invalid, the error message is contained inline in the row list
                if (nodeList[0].InnerText.Trim().StartsWith("InvalidRegexp"))
                {
                    this.Log.WriteInfo("InvokeGetMatchedRows: Invalid Regular expression");
                    return;
                }

                // if the first row matches this, it is not 'real' data but rather an indication that
                // there are more rows which were matched by the regexps but not returned by the invoke.
                // Therefore, this row has to be suppressed from the results of this method.
                if (nodeList[0].InnerText.Trim().StartsWith("MoreRowsAvailable"))
                {
                    matchesFound--;
                    rowOffset = 1;
                }

                this.Log.WriteInfo(string.Format("InvokeGetMatchedRows: {0} matches found", matchesFound));

                results = new string[matchesFound];

                for (int i = 0; i < matchesFound; i++)
                {
                    string result = nodeList[i + rowOffset].InnerText.Trim();

                    // For unknown reasons, sometimes row results start with a spurious '0;'. 
                    if (result.StartsWith("0;"))
                    {
                        result = result.Substring(2).Trim();
                    }

                    results[i] = result;
                }
            }
            else
            {
                this.Log.WriteInfo("InvokeGetMatchedRows: no matches found");
            }
        }

        #endregion Public Methods

        #region Private Methods

        /// <summary>
        /// Create a WSMAN session with the remote client based the query class (provider) and information in the constructor.
        /// </summary>
        /// <param name="queryClass">The query class</param>
        /// <returns>Returns an interface class to WSMAN</returns>
        private IWSManSession GetWSMANSession(string queryClass)
        {
            WSMan webSvcMan = new WSMan();
            IWSManSession session = null;

            IWSManConnectionOptions cnctOptions = (IWSManConnectionOptions)webSvcMan.CreateConnectionOptions();
            cnctOptions.UserName = this.Username;
            cnctOptions.Password = this.Password;

            int sessionFlags = webSvcMan.SessionFlagUseBasic() + webSvcMan.SessionFlagCredUsernamePassword()
                        + webSvcMan.SessionFlagSkipCACheck() + webSvcMan.SessionFlagSkipCNCheck()
                        + webSvcMan.SessionFlagUTF8()
                        + webSvcMan.SessionFlagSkipRevocationCheck(); // Add for winrm 2.0, remove for winrm 1.1.

            try
            {
                string sessionHost = string.Concat("https://", this.Hostname, ":", this.Port.ToString());
                session = (IWSManSession)webSvcMan.CreateSession(sessionHost, sessionFlags, cnctOptions);
            }
            catch (COMException ce)
            {
                this.HandleWSMANException(ce, queryClass, webSvcMan);
            }

            return session;
        }

        /// <summary>
        /// Handle a WSMAN Exception
        /// </summary>
        /// <param name="ce">The exception class being handled</param>
        /// <param name="queryClass">The query class</param>
        /// <param name="webSvcMan">The WSMAN interface class</param>
        private void HandleWSMANException(COMException comException, string queryClass, WSMan webSvcMan)
        {
            if (this.Log != null)
            {
                this.Log.WriteError("hostname=" + this.Hostname);
                this.Log.WriteError("HttpsMode=" + this.HttpsMode);
                this.Log.WriteError("username=" + this.Username);
                this.Log.WriteError("password=" + this.Password);
                this.Log.WriteError("XmlSchemaPrefix=" + this.XmlSchemaPrefix);
                this.Log.WriteError("XmlSchemaSuffix=" + this.XmlSchemaSuffix);
                this.Log.WriteError("Port=" + this.Port);
                this.Log.WriteError("queryClass=" + queryClass);
                this.Log.WriteError("Error: " + comException.Message);
                this.Log.WriteError("WSMan: " + webSvcMan.Error);
                // what exception we should throw in stead?????
                //throw new VarAbort("WSMAN query failed", ce);
                throw comException;
            }
            else
            {
                throw comException;
            }
        }

        #endregion Private Methods

        #endregion Methods
    }
}
