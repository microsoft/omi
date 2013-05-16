//-----------------------------------------------------------------------
// <copyright file="Utilities.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>sunilmu, v-hotong, v-hew,v-mayz</author>
// <description></description>
// <history>12/1/2010 1:59:06 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using System;
    using System.IO;
    using System.Text;
    using System.Text.RegularExpressions;

    /// <summary>
    /// This class contains useful methods that will be needed by vars and grps.
    /// Whenever a var/grp class wants to utilize this functionality, they can directly inherit from this class.
    /// </summary>
    public class Utilities
    {
        /// <summary>
        /// Logger for track info out
        /// </summary>
        public Logger logger
        {
            get;
            set;
        }

        #region Methods

        /// <summary>
        /// Run a command in the specified Unix/Linux machine
        /// </summary>
        /// <param name="hostName">The server name of Unix/Linux machine</param>
        /// <param name="username">The user name to logon Unix/Linux machine</param>
        /// <param name="password">The password of the specified user</param>
        /// <param name="command">The command going to be executed</param>        
        public string RunSshCommand(string hostName, string username, string password, string command)
        {
            try
            {
                logger.WriteInfo("Entering method RunSshCommand, command is : {0}", command);
                using (SshHelper ssh = new SshHelper(hostName, username, password, logger))
                {
                    ssh.RunCmd(command);
                    logger.WriteInfo("Leaving method RunSshCommand, command is : {0}", command);
                    return ssh.StdOut;
                }
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format("Failed to run RunSshCommand : {0} \n<Error> :{1}", command, ex.Message));
            }
        }

        /// <summary>
        /// Run a command in the specified Unix/Linux machine
        /// </summary>
        /// <param name="hostName">The server name of Unix/Linux machine</param>
        /// <param name="username">The user name to logon Unix/Linux machine</param>
        /// <param name="password">The password of the specified user</param>
        /// <param name="command">The command going to be executed</param>
        /// <param name="exceptToPass">The except result to run pass or failed of command executed, default is execute pass</param>
        /// <returns>output for ssh command</returns>
        public string RunSshCommand(string hostName, string username, string password, string command, bool exceptToPass = true)
        {
            try
            {
                logger.WriteInfo("Entering method RunSshCommand, command is : {0}", command);
                using (SshHelper ssh = new SshHelper(hostName, username, password, logger))
                {
                    ssh.ExpectToPass = exceptToPass;
                    ssh.RunCmd(command);
                    logger.WriteInfo("Leaving method RunSshCommand, command is : {0}", command);
                    return ssh.StdOut;
                }
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format("Failed to run RunSshCommand : {0} \n<Error> :{1}", command, ex.Message));
            }
        }

        /// <summary>
        /// Run a command in the specified Unix/Linux machine
        /// </summary>
        /// <param name="hostName">The server name of Unix/Linux machine</param>
        /// <param name="username">The user name to logon Unix/Linux machine</param>
        /// <param name="password">The password of the specified user</param>
        /// <param name="command">The command going to be executed</param>
        /// <param name="exceptToPass">The except result to run pass or failed of command executed, default is execute pass</param>
        /// <param name="ignoreError">true to ignor the result exception , false to throw the exception</param>
        /// <returns>output for ssh command</returns>
        public string RunSshCommand(string hostName, string username, string password, string command, bool exceptToPass, bool ignoreError)
        {
            string stdout = "";
            try
            {
                stdout = RunSshCommand(hostName, username, password, command, exceptToPass);
            }
            catch (Exception ex)
            {
                if (!ignoreError)
                {
                    throw ex;
                }
                else
                {
                    logger.WriteWarning("Warning :Failed to run RunSshCommand: {0} , But ignore this error", command);
                }
            }

            return stdout;
        }

        /// <summary>
        /// Run a command in the specified Unix/Linux machine, compare the return result with expected result
        /// </summary>
        /// <param name="hostName">The server name of Unix/Linux machine</param>
        /// <param name="username">The user name to logon Unix/Linux machine</param>
        /// <param name="password">The password of the specified user</param>
        /// <param name="command">The command going to be executed</param>
        /// <param name="expectedString">The expected result from executing the command</param>
        public void RunSshCommand(string hostName, string username, string password, string command, string expectedString)
        {
            try
            {
                logger.WriteInfo("Entering method RunSshCommand, command is : {0}", command);
                using (SshHelper ssh = new SshHelper(hostName, username, password, logger))
                {
                    ssh.RunCmd(command);
                    logger.WriteInfo("Command has been executed!");
                    if (!string.Equals(ssh.StdOut, expectedString, StringComparison.CurrentCultureIgnoreCase))
                    {
                        throw new Exception(string.Format("Expected:{0}; \n Actual:{0}", expectedString, ssh.StdOut));
                    }
                    logger.WriteInfo("Leaving method RunSshCommand, command is : {0}", command);
                }
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format("Failed to run RunSshCommand : {0} \n<Error> :{1}", command, ex.Message));
            }
        }


        /// <summary>
        /// Run a command to verify that OMI has been successfully installed on the specified Unix/Linux machine 
        /// </summary>
        /// <param name="hostName">The server name of Unix/Linux machine</param>
        /// <param name="username">The user name to logon Unix/Linux machine</param>
        /// <param name="password">The password of the specified user</param>
        /// <param name="omiBinLocation">The install location of omi</param>
        /// <returns></returns>
        public void VerifyOmiInstall(string hostName, string username, string password, string omiBinLocation)
        {
            try
            {
                logger.WriteInfo("Entering method VerifyInstall");
                string command = "{0}/bin/omiserver -d;{0}/bin/omiserver -d";
                string pattern = @"/+omi/+bin/+omiserver.bin: server is already running\n*";
                string stdOut = RunSshCommand(hostName, username, password, string.Format(command, omiBinLocation), false);
                bool isMatch = Regex.IsMatch(stdOut, pattern);
                if (!isMatch)
                {
                    throw new Exception(string.Format("Expected:{0}; \n Actual:{0}", pattern, stdOut));
                }
                logger.WriteInfo("Leaving method VerifyomiInstall");
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format("Failed to verify OMI installation status \n<Error> :{0}", ex.Message));
            }
        }

        /// <summary>
        /// Clean OMI on the specified Unix/Linux machine
        /// </summary>
        /// <param name="hostname">The server name of Unix/Linux machine</param>
        /// <param name="username">The user name to logon Unix/Linux machine</param>
        /// <param name="password">The password of the specified user</param>
        /// <param name="omiBinLocation">The install location of omi</param>
        /// <returns></returns>
        public void CleanOmi(string hostname, string username, string password, string checkProcessCommand, string omiLocation)
        {
            try
            {
                logger.WriteInfo("Entering method CleanOmi");
                // if the omiserver is running, stop it
                if (RunSshCommand(hostname, username, password, checkProcessCommand).Contains("omiserver.bin"))
                {
                    RunSshCommand(hostname, username, password, omiLocation + "/bin/omiserver -s");
                }
                RunSshCommand(hostname, username, password, "rm -rf " + omiLocation);
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format("Failed to run CleanOmi \n<Error> :{0}", ex.Message));
            }
            logger.WriteInfo("Leaving method CleanOmi");
        }


        /// <summary>
        /// Copy files from windows to Unix/Linux;
        /// we suppose tests are running in windows side; so we don't need to know machine name of windows side
        /// </summary>
        /// <param name="hostName">The server name of Unix/Linux machine</param>
        /// <param name="username">The user name to logon Unix/Linux machine</param>
        /// <param name="password">The password of the specified user</param>
        /// <param name="fromLoc">The absolute path of the file be copied (windows side)</param>
        /// <param name="toLoc">The absolute location to place the file (Unix/Linux side) </param>
        public void CopyFileToNoomiindows(string hostName, string username, string password, string fromLoc, string toLoc)
        {
            try
            {
                logger.WriteInfo("Entering method CopyFileToNoomiindows, copy file {0} to {1}", fromLoc, toLoc);
                using (SshHelper ssh = new SshHelper(hostName, username, password, logger))
                {
                    ssh.CopyFromWindows(fromLoc, toLoc);
                }
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format("Failed to CopyFileToNoomiindows copy file {0} to {1} \n<Error> :{3}", fromLoc, toLoc, ex.Message));
            }
            logger.WriteInfo("Leaving method CopyFileToNoomiindows, copy file {0} to {1}", fromLoc, toLoc);
        }

        /// <summary>
        /// Copy files from Unix/Linux to windows; 
        /// we suppose tests are running in windows side; so we don't need to know machine name of windows side
        /// </summary>
        /// <param name="hostName">The server name of Unix/Linux machine</param>
        /// <param name="username">The user name to logon Unix/Linux machine</param>
        /// <param name="password">The password of the specified user</param>
        /// <param name="fromLoc">The absolute location of file be copied (Unix/Linux side)</param>
        /// <param name="toLoc"> The absolute location to place the file (Windows side)</param>
        public void CopyFileFromNoomiindows(string hostName, string username, string rootuser, string password, string fromLoc, string toLoc)
        {
            try
            {
                logger.WriteInfo("Entering method CopyFileFromNoomiindows, copy file {0} to {1}", fromLoc, toLoc);
                using (SshHelper ssh = new SshHelper(hostName, username, password, logger))
                {
                    ssh.CopyToWindows(fromLoc, toLoc);
                }
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format("Failed to CopyFileFromNoomiindows copy file {0} to {1} \n<Error> :{3}", fromLoc, toLoc, ex.Message));
            }
            logger.WriteInfo("Leaving method CopyFileFromNoomiindows, copy file {0} to {1}", fromLoc, toLoc);
        }

        /// <summary>
        /// Register the specified provider in Unix/Linux machine; 
        /// we suppose tests are running in windows side
        /// </summary>
        /// <param name="hostName">The server name of Unix/Linux machine</param>
        /// <param name="username">The user name to logon Unix/Linux machine</param>
        /// <param name="password">The password of the specified user</param>
        /// <param name="omiregCmd">The command for omireg</param>
        /// <param name="providerPath">The full path of the provider (non-Windows side)</param>
        /// <param name="regNameSpace"> The namespace for the provider</param>
        /// <param name="hosting">The hosting of the provider</param>
        public void RegisterProvider(string hostName, string username, string password, string omiregCmd, string providerPath, string regNameSpace, string hosting)
        {
            try
            {
                logger.WriteInfo("Entering method RegisterProvider, Provider is {0}, regNameSpace is {1}", providerPath, regNameSpace);
                omiregCmd = omiregCmd + " " + providerPath;
                if (regNameSpace != string.Empty)
                {
                    omiregCmd = omiregCmd + " -n " + regNameSpace;
                }
                if (hosting != "")
                {
                    omiregCmd = omiregCmd + " -o " + hosting;
                }
                RunSshCommand(hostName, username, password, omiregCmd);
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format("Failed to RegisterProvider : <Error> :{0}", ex.Message));
            }

            logger.WriteInfo("Leaving method RegisterProvider, Provider is {0}, regNameSpace is {1}", providerPath, regNameSpace);
        }

        /// <summary>
        /// Compare the expect result and actual result.
        /// </summary>
        /// <param name="expectResult">the expect result of a command</param>
        /// <param name="actualResult">the actual result when run a command </param>
        /// <returns>true indicate the compare result is pass . else compare result is false</returns>
        public bool CompareResult(string expectResult, string actualResult)
        {
            bool comparePass = false;
            try
            {
                if (File.Exists(expectResult))
                {
                    string expectOutput = File.ReadAllText(expectResult, Encoding.Default);
                    expectOutput = Regex.Replace(expectOutput, @"[\s/]", "");
                    actualResult = Regex.Replace(actualResult, @"[\s/]", "");
                    comparePass = actualResult.Contains(expectOutput);
                }
                else
                {
                    expectResult = Regex.Replace(expectResult, @"[/]+", "/");
                    actualResult = Regex.Replace(actualResult, @"[/]+", "/");
                    comparePass = actualResult.Contains(expectResult);
                }
            }
            catch (Exception)
            {
                throw new InvalidOperationException();
            }

            return comparePass;
        }

        /// <summary>
        /// Get version of OMI components from build file
        /// </summary>
        /// <param name="versionFilePath">the path of build version file</param>
        /// <returns>version</returns>
        public static string GetVersion(string versionFilePath)
        {
            string buildVersion = string.Empty;

            try
            {
                using (StreamReader sr = new StreamReader(versionFilePath))
                {
                    buildVersion = sr.ReadToEnd();
                    string regExp = @"(\d{1,3})";
                    MatchCollection matchSet = Regex.Matches(buildVersion, regExp);
                    buildVersion = string.Format("{0}.{1}.{2}.{3}", matchSet[0], matchSet[1], matchSet[3], matchSet[2]);
                }
            }
            catch (Exception ex)
            {
                throw new Exception("Exception occured, failed to get build version ", ex);
            }

            return buildVersion;
        }
        #endregion
    }
}
