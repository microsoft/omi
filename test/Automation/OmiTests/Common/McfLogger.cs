//-----------------------------------------------------------------------
// <copyright file="McfLogger.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>sunilmu</author>
// <description></description>
// <history>5/17/2010 3:32:26 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using Infra.Frmwrk;

    /// <summary>
    /// MCF-based ILogger implementation.
    /// </summary>
    public class McfLogger : Logger
    {
        /// <summary>
        /// MCF context object, which implements the ILog interface.
        /// </summary>
        private readonly ILog mcfContextLogger;

        /// <summary>
        /// Log level for the current logging context.
        /// </summary>
        private LogLevel logLevel;

        /// <summary>
        /// Constuctor for Info level of logging.
        /// </summary>
        /// <param name="ctx">MCF context.</param>
        public McfLogger(IContext ctx)
        {
            if (ctx == null)
                throw new VarAbort("Attempt to initialize MCF logger with null context");

            mcfContextLogger = ctx;
            logLevel = LogLevel.Info;
        }

        /// <summary>
        /// Verbosity or log level of the current logging.  Smaller value means more important and should be logged.
        /// </summary>
        public LogLevel Verbosity
        {
            get
            {
                return logLevel;
            }
            set
            {
                logLevel = value;
            }
        }

        /// <summary>
        ///     Writes a log message.
        /// </summary>
        /// <param name="logLvl">Log level of the message</param>
        /// <param name="format">Format in string of the message</param>
        /// <param name="args">Object list used by the format. If null is provided, then the string in the format parameter
        /// is printder as-is</param>
        protected override void Write(LogLevel logLvl, string format, params object[] args)
        {
            if (logLvl <= logLevel)
            {
                // If the user wants to just log the message, then the args parameter will be empty,
                // in which case, the format will be treated as the message.
                string message = format;
                if (args != null && args.Length != 0)
                {
                    message = string.Format(format, args);
                }
            
                switch (logLvl)
                {
                    case LogLevel.Info:
                    case LogLevel.Debug:
                        mcfContextLogger.Trc(message);
                        break;

                    case LogLevel.Fatal:
                        mcfContextLogger.Alw(message);
                        break;

                    case LogLevel.Error:
                        mcfContextLogger.Err(message);
                        break;

                    case LogLevel.Warning:
                        mcfContextLogger.Wrn(message);
                        break;
                }
            }
        }

        /// <summary>
        /// This method is not supported for MCF.
        /// </summary>
        /// <param name="deviceName">Not supported.</param>
        protected override void Initialize(string deviceName)
        {
            mcfContextLogger.Alw("MCF logger is initialized successfully");
        }

        protected override void Close()
        {
            mcfContextLogger.Alw("MCF logger is closed successfully");
        }
    }
}
