//-----------------------------------------------------------------------
// <copyright file="SshHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>a-brmill, v-zhegu</author>
// <description></description>
// <history>1/20/2009 3:50:59 PM: Created</history>
// <history>10/29/2010 Modified add it to our common library and add Logging interface</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using System;
    using sshcomLib;

    // This is the Microsoft SSL library

    /// <summary>
    /// Run a command on a Posix system via SSH connection
    /// </summary>
    public class SshHelper : IDisposable
    {
        #region Private Fields

        /// <summary>
        /// SSH connection to Posix host
        /// </summary>
        private scxssh ssh;

        /// <summary>
        /// Name of Posix host
        /// </summary>
        private string hostName = string.Empty;

        /// <summary>
        /// Port number of SSH
        /// </summary>
        private int port = 22;

        /// <summary>
        /// Valid user name
        /// </summary>
        private string userName = string.Empty;

        /// <summary>
        /// Password for user name
        /// </summary>
        private string password = string.Empty;

        /// <summary>
        /// Followup password used in case of prompt, for example, when using su.
        /// </summary>
        private string followupPassword = string.Empty;

        /// <summary>
        /// Full path to executable file
        /// </summary>
        private string fileName = string.Empty;

        /// <summary>
        /// Arguments passed to executable file
        /// </summary>
        private string arguments = string.Empty;

        /// <summary>
        /// Is command expected to pass
        /// </summary>
        private bool expectToPass = true;

        /// <summary>
        /// Should the exit value be ignored
        /// </summary>
        private bool ignoreExit;

        /// <summary>
        /// Timeout for command, in milliseconds
        /// </summary>
        private int timeOut;

        /// <summary>
        /// Return value from command
        /// </summary>
        private uint exitCode;

        /// <summary>
        /// StdOut result from executing command
        /// </summary>
        private string stdout = string.Empty;

        /// <summary>
        /// StdErr result from executing command
        /// </summary>
        private string stderr = string.Empty;

        /// <summary>
        /// Delegate method for executing a command via SSH
        /// </summary>
        private PosixExecCmd posixExecCmd;

        /// <summary>
        /// Contains exception if an exception was thrown in the worker thread
        /// </summary>
        private Exception threadException;

        /// <summary>
        /// Logger
        /// </summary>
        private Logger logger;

        #endregion protected Fields

        #region Constructors

        /// <summary>
        /// Initializes a new instance of the SshHelper class.
        /// </summary>
        /// <param name="hostName">Name of Posix host</param>
        /// <param name="userName">Valid user on Posix host</param>
        /// <param name="password">Password for user</param>
        public SshHelper(string hostName, string userName, string password, Logger logger)
        {
            if (string.IsNullOrEmpty(hostName))
            {
                throw new ArgumentNullException("HostName");
            }

            if (string.IsNullOrEmpty(userName))
            {
                throw new ArgumentNullException("UserName");
            }

            if (string.IsNullOrEmpty(password))
            {
                throw new ArgumentNullException("Password");
            }
            if (logger == null)
            {
                throw new ArgumentNullException("logger");
            }

            this.hostName = hostName;
            this.userName = userName;
            this.password = password;
            this.logger = logger;
            this.NewSshConnection();
        }

        /// <summary>
        /// Finalizes an instance of the SshHelper class
        /// </summary>
        ~SshHelper()
        {
            this.Dispose(false);
        }

        #endregion Constructors

        #region Delegates

        /// <summary>
        /// Delegate method for executing a command via SSH
        /// </summary>
        /// <param name="command">Command to be executed</param>
        /// <param name="result">Standard output from the command</param>
        /// <returns>Command return value, 0-255</returns>
        protected delegate uint PosixExecCmd(string command, out string result);

        #endregion Delegates

        #region Properties

        /// <summary>
        /// Gets or sets the HostName property
        /// </summary>
        public string HostName
        {
            get { return this.hostName; }
            set { this.hostName = value; }
        }

        /// <summary>
        /// Gets or sets the UserName property
        /// </summary>
        public string UserName
        {
            get { return this.userName; }
            set { this.userName = value; }
        }

        /// <summary>
        /// Gets or sets the Password property
        /// </summary>
        public string Password
        {
            get { return this.password; }
            set { this.password = value; }
        }

        /// <summary>
        /// Gets or sets the FileName property
        /// </summary>
        /// <remarks>This is the full path to the executable</remarks>
        public string FileName
        {
            get { return this.fileName; }
            set { this.fileName = value; }
        }

        /// <summary>
        /// Gets or sets the Arguments property
        /// </summary>
        /// <remarks>This is appended to the FileName property</remarks>
        public string Arguments
        {
            get { return this.arguments; }
            set { this.arguments = value; }
        }

        /// <summary>
        /// Gets or sets the TimeOut property
        /// </summary>
        /// <remarks>Optional value specifies time to wait before aborting operation, in seconds</remarks>
        public int TimeOut
        {
            get { return this.timeOut; }
            set { this.timeOut = value; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the command is expected to pass
        /// </summary>
        /// <remarks>Optional value</remarks>
        public bool ExpectToPass
        {
            get { return this.expectToPass; }
            set { this.expectToPass = value; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the command exit value should be ignored
        /// </summary>
        public bool IgnoreExit
        {
            get { return this.ignoreExit; }
            set { this.ignoreExit = value; }
        }

        /// <summary>
        /// Gets the command's standard output
        /// </summary>
        public string StdOut
        {
            get { return this.stdout; }
        }

        /// <summary>
        /// Gets the command's standard error output (not used)
        /// </summary>
        /// <remarks>Provided for interface compatibility, and is never set.
        /// Stderr stream is not available under the sshlib.dll COM library.</remarks>
        public string StdErr
        {
            get { return this.stderr; }
        }

        /// <summary>
        /// Gets or sets the followup password
        /// </summary>
        public string FollowupPassword
        {
            get { return this.followupPassword; }
            set { this.followupPassword = value; }
        }

        /// <summary>
        /// Gets or sets the ssh property
        /// </summary>
        public scxssh Ssh
        {
            get { return this.ssh; }
            set { this.ssh = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public Logger Logger
        {
            get { return this.logger; }
            set { this.logger = value; }
        }

        #endregion Properties

        #region Methods

        #region Public Methods

        /// <summary>
        /// Execute a command on a remote Posix machine using ExecuteCommand
        /// </summary>
        /// <remarks>When there is a problem with a SSH command, a
        /// very generic exception is thrown by the COM library.  This
        /// does not indicate that a significant bug-type error occured.  Check
        /// whether the host is accessible by DNS name and IP, whether you are
        /// using an executable binary or shell command, if the full path is
        /// specified, etc.</remarks>
        public void RunCmd()
        {
            bool threadCompleted = true;

            if (string.IsNullOrEmpty(this.fileName))
            {
                throw new ArgumentNullException("FileName property is null or empty");
            }

            // Create thread for SSH command to control timeout
            System.Threading.Thread posixThread = new System.Threading.Thread(this.ExecuteSshCommand);
            posixThread.Start();

            if (this.timeOut != 0)
            {
                threadCompleted = posixThread.Join(this.timeOut);
            }
            else
            {
                posixThread.Join();
            }

            // The threadException will be set independently of the Join()
            if (this.threadException != null)
            {
                throw new ApplicationException("SSH command failure", this.threadException);
            }

            // Thread completed normally
            if (threadCompleted == true)
            {
                bool testSucceeded;
                string message;

                // TODO: Fix the logic here!
                this.AnalyzeCmdResults(out testSucceeded, out message);

                //logger.WriteInfo("Command returned: " + this.stdout);
                //logger.WriteInfo(message);

                if (testSucceeded == false)
                {
                    throw new ApplicationException(message);
                }
            }
            else
            {
                throw new ApplicationException("SshHelper '" + this.fileName + "' timed out");
            }
        }

        /// <summary>
        /// Execute a command on a remote Posix machine using ExecuteCommand
        /// </summary>
        /// <param name="fullCommand">The full command string containing path to the command and its arguments</param>
        /// <remarks>with this method there is no need to set FileName or Arguments as these are extracted from 'fullCommand'
        /// </remarks>
        public void RunCmd(string fullCommand)
        {
            this.Arguments = string.Empty;
            this.FileName = fullCommand;
            this.RunCmd();
        }

        /// <summary>
        /// Execute a command on a remote Posix machine, making retry attempts if the first one fails.
        /// </summary>
        /// <param name="fullCommand">The full command string containing path to the command and its arguments</param>
        /// <param name="maxRetries">Maximum number of times to run the command in case the first attempts fail.</param>
        public void RunCmd(string fullCommand, int maxRetries)
        {
            string errorMessage = string.Empty;
            bool success = false;

            for (int tries = 0; tries < maxRetries && !success; tries++)
            {
                try
                {
                    this.RunCmd(fullCommand);
                    success = true;
                }
                catch (Exception ex)
                {
                    success = false;
                    errorMessage = ex.Message;
                }

                if (!success)
                {
                    System.Threading.Thread.Sleep(new TimeSpan(0, 0, 30));
                }
            }

            if (!success)
            {
                throw new Exception(string.Format("PosixCmd({0}) failed after {1} attempts: {2}", fullCommand, maxRetries, errorMessage));
            }
        }

        /// <summary>
        /// Open a shell on the remote system.  This is necessary in case the command being run requires a second, interative
        /// password entry (for example, using the sudo command)
        /// </summary>
        public void OpenShell()
        {
            uint retValue = this.ssh.OpenShell();
            if (retValue != 0)
            {
                throw new Exception(string.Format("ssh.OpenShell failed: return code = {0}", retValue));
            }
            else
            {
                Logger.WriteInfo("Shell has been opened successfully");
            }
        }

        /// <summary>
        /// Run command in a shell, optionally entering a followup password when prompted (for example, in reply to su or sudo)
        /// </summary>
        /// <param name="cmd">The full command, including file and arguments</param>
        public void RunShellCommand(string cmd)
        {
            bool threadCompleted = true;

            this.fileName = cmd;

            this.ssh.SetTimeout((uint)this.timeOut);
            this.ssh.SetShellOutputTimeout((uint)this.timeOut);

            // Create thread for SSH command to control timeout
            System.Threading.Thread posixThread = new System.Threading.Thread(this.ExecuteSshShellCommand);
            posixThread.Start();

            if (this.timeOut != 0)
            {
                threadCompleted = posixThread.Join(this.timeOut);
            }
            else
            {
                posixThread.Join();
            }

            // The threadException will be set independently of the Join()
            if (this.threadException != null)
            {
                throw new ApplicationException("SSH shell command failure", this.threadException);
            }

            // Thread completed normally
            if (threadCompleted == true)
            {
                bool testSucceeded;
                string message;

                this.AnalyzeCmdResults(out testSucceeded, out message);
                logger.WriteInfo("Command returned: " + this.stdout);
                logger.WriteInfo(message);

                if (testSucceeded == false)
                {
                    throw new ApplicationException(message);
                }
            }
            else
            {
                throw new ApplicationException("SshHelper '" + this.fileName + "' timed out");
            }
        }

        /// <summary>
        /// Interface method to copy files from a Posix host
        /// </summary>
        /// <param name="winPath">Path for source file(s)</param>
        /// <param name="nonwinPath">Destination path</param>
        public void CopyFromWindows(string winPath, string nonwinPath)
        {
            if (String.IsNullOrEmpty(winPath))
            {
                throw new ArgumentException("sourcePath is null or empty");
            }

            if (String.IsNullOrEmpty(nonwinPath))
            {
                throw new ArgumentException("destPath is null or empty");
            }
            try
            {
                this.ssh.SFTPCopyToRemote(winPath, nonwinPath);
                this.logger.WriteInfo("Successfully copied files from {0} to {1}", winPath, nonwinPath);
            }
            catch (Exception e)
            {
                throw new Exception("Failed to copy files .", e);
            }

        }

        /// <summary>
        /// Interface method to copy files to a Posix host
        /// </summary>
        /// <param name="winPath">Path for source file(s)</param>
        /// <param name="nonwinPath">Destination path</param>
        public void CopyToWindows(string winPath, string nonwinPath)
        {
            if (String.IsNullOrEmpty(winPath))
            {
                throw new ArgumentException("sourcePath is null or empty");
            }

            if (String.IsNullOrEmpty(nonwinPath))
            {
                throw new ArgumentException("destPath is null or empty");
            }
            try
            {
                // Returns uint, but throws exception on error (like source file not found)
                this.ssh.SFTPCopyToLocal(winPath, nonwinPath);
                this.logger.WriteInfo("Successfully copy files from {0} to {1}", winPath, nonwinPath);
            }
            catch (Exception e)
            {
                throw new Exception("Failed to copy files .", e);
            }
        }

        public void Dispose()
        {
            this.Dispose(true);
        }

        #endregion Public Methods

        #region protected Methods

        /// <summary>
        /// Initialize a new SSH connection
        /// </summary>
        /// <returns>returns whether the connection completed successfully</returns>
        protected bool NewSshConnection()
        {
            uint connectValue;

            try
            {
                this.ssh = new scxssh();
                /*returns uint*/
                connectValue = this.ssh.ConnectWithPassword(this.hostName, this.port, this.userName, this.password);
                this.posixExecCmd = this.ssh.ExecuteCommand2;
            }
            catch (Exception e)
            {
                throw new Exception("Unable to connect to host", e);
            }

            return connectValue == 0;
        }

        /// <summary>
        /// Run a seperate thread to execute a command over SSH.
        /// </summary>
        /// <remarks>This (hopefully) provides timeout control over remote process</remarks>
        protected void ExecuteSshCommand()
        {
            this.stdout = string.Empty;
            this.stderr = string.Empty;
            this.threadException = null;

            try
            {
                if (string.IsNullOrEmpty(this.arguments))
                {
                    this.exitCode = this.posixExecCmd(this.fileName, out this.stdout);
                }
                else
                {
                    this.exitCode = this.posixExecCmd(this.fileName + " " + this.arguments, out this.stdout);
                }
            }
            catch (Exception e)
            {
                this.logger.WriteError("Failed to execute SSH command");
                this.threadException = e;
            }
        }

        /// <summary>
        /// Run a seperate thread to execute a shell command over SSH.
        /// </summary>
        protected void ExecuteSshShellCommand()
        {
            this.stdout = string.Empty;
            this.stderr = string.Empty;
            this.threadException = null;

            try
            {
                if (!string.IsNullOrEmpty(this.followupPassword))
                {
                    string[] followupPasswords = this.followupPassword.Split(new char[] { ';' });

                    this.ssh.SetShellOutputTimeout(5000);

                    this.exitCode = this.ssh.ShellCommand2(this.fileName, out this.stdout);

                    for (int passwordIndex = 0;
                        passwordIndex < followupPasswords.Length && this.exitCode == 0;
                        passwordIndex++)
                    {
                        string stdOutBuffer;
                        System.Threading.Thread.Sleep(1000);
                        this.exitCode = this.ssh.ShellCommand2(followupPasswords[passwordIndex], out stdOutBuffer);
                        this.stdout += stdOutBuffer;
                    }
                }
                else
                {
                    this.exitCode = this.ssh.ShellCommand2(this.fileName, out this.stdout);
                }
            }
            catch (Exception e)
            {
                this.logger.WriteError("Failed to execute to SSH shell command");
                this.threadException = e;
            }
        }

        /// <summary>
        /// Analyze the command's return value according to whether it was expected to pass or fail
        /// </summary>
        /// <param name="succeeded">set to true if the command succeeded according to expectations</param>
        /// <param name="usrMsg">text containing user message</param>
        /// <remarks>Success is based on test expectation, not the actual result.</remarks>
        protected void AnalyzeCmdResults(out bool succeeded, out string usrMsg)
        {
            succeeded = false;
            usrMsg = string.Format("SshHelper '{0}' returned {1}", this.fileName, this.exitCode.ToString());

            if (this.ignoreExit == true)
            {
                succeeded = true;
                return;
            }

            if (this.expectToPass)
            {
                if (this.exitCode == 0)
                {
                    usrMsg += ", expected to pass, has passed";
                    succeeded = true;
                }
                else
                {
                    usrMsg += ", expected to pass, has failed";
                }
            }
            else
            {
                if (this.exitCode == 0)
                {
                    usrMsg += ", expected to fail, has passed";
                }
                else
                {
                    usrMsg += ", expected to fail, has failed";
                    succeeded = true;
                }
            }
        }

        #endregion protected Methods

        #region private Methods

        private void Dispose(bool disPosing)
        {
            // Release unmanaged resources. Because this class don't have managed resources, I don't using Dispose(bool disposing) Model.
            if (this.ssh != null)
            {
                lock (this)
                {
                    if (this.ssh != null)
                    {
                        this.ssh.Shutdown();
                        this.ssh = null;
                    }
                }
            }

            // Take yourself off the Finalization queue 
            // to prevent finalization code for this object
            // from executing a second time.
            if (disPosing)
            {
                GC.SuppressFinalize(this);
            }
        }

        #endregion private Methods

        #endregion Methods
    }
}
