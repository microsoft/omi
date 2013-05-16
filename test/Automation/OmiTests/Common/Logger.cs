//-----------------------------------------------------------------------
// <copyright file="Logger.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>zhyao</author>
// <description>From Opalis source code</description>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    /// <summary>
    ///     Log level used in the logging interface.
    /// </summary>
    public enum LogLevel
    {
        Fatal = 0x10 << 1,
        Error = 0x10 << 2,
        Warning = 0x10 << 3,
        Info = 0x10 << 4,
        Debug = 0x10 << 5,
    }

    /// <summary>
    ///     Generic logging support class.
    /// </summary>
    public abstract class Logger
    {
        /// <summary>
        ///     Verbosity or log level of the current logging.  Smaller value means more important and should be logged.
        /// </summary>
        LogLevel Verbosity
        {
            get;
            set;
        }

        /// <summary>
        ///     Initializes the logging device.  Note that multiple devices may be specified as logging destination depending on
        ///     the concrete implementation of this interface.
        /// </summary>
        /// <param name="deviceName">
        ///     name of the underlying logging device.  (For instance, file name for file system based logging)
        /// </param>
        protected abstract void Initialize(string deviceName);

        /// <summary>
        ///     Closes the logging device and stops all logging afterwards (exception will be raised).
        /// </summary>
        protected abstract void Close();

        /// <summary>
        ///     Writes a log message.
        /// </summary>
        /// <param name="logLevel">log level of the message</param>
        /// <param name="format">format in string of the message</param>
        /// <param name="args">object list used by the format</param>
        protected abstract void Write(LogLevel logLevel, string format, params object[] args);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="format"></param>
        /// <param name="args"></param>
        public void WriteInfo(string format, params object[] args)
        {
            Write(LogLevel.Info, format, args);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="format"></param>
        /// <param name="args"></param>
        public void WriteError(string format, params object[] args)
        {
            Write(LogLevel.Error, format, args);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="format"></param>
        /// <param name="args"></param>
        public void WriteWarning(string format, params object[] args)
        {
            Write(LogLevel.Warning, format, args);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="format"></param>
        /// <param name="args"></param>
        public void WriteDebug(string format, params object[] args)
        {
            Write(LogLevel.Debug, format, args);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="format"></param>
        /// <param name="args"></param>
        public void WriteFatal(string format, params object[] args)
        {
            Write(LogLevel.Fatal, format, args);
        }
    }
}
