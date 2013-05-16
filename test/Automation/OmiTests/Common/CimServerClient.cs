//-----------------------------------------------------------------------
// <copyright file="CimServerClient.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>sunilmu, v-zhegu</author>
// <description></description>
// <history>11/12/2010 9:38:20 AM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using System;
    using System.Collections.Generic;
    using System.Xml.Linq;

    public abstract class CimServerClient
    {
        protected XDocument response;
        protected Logger log;
        protected SysInfo sys;

        /// <summary>
        /// Response from the action performed on the server.
        /// </summary>
        public XDocument Response
        {
            get { return response; }

#if DEBUG
            set { response = value; }
#endif
        }

        protected CimServerClient(Logger logger, SysInfo systemInfo)
        {
            if (logger == null)
            {
                throw new ArgumentNullException("logger");
            }

            if (systemInfo == null)
            {
                throw new ArgumentNullException("systemInfo");
            }

            log = logger;
            sys = systemInfo;
        }

        /// <summary>
        /// Enumerates all instances of the given class.
        /// </summary>
        /// <param name="provNamespace">Namespace of the provider.</param>
        /// <param name="className">Class to be enumerated.</param>
        /// <param name="deepInheritance">True if the enumeration has to be deep.</param>
        public abstract void Enumerate(string provNamespace, string className, bool deepInheritance);

        /// <summary>
        /// Gets the instance of the class.
        /// </summary>
        /// <param name="instance">Instance to get.</param>
        public abstract void Get(CimInstance instance);

        /// <summary>
        /// Invokes a method on the class.
        /// </summary>
        /// <param name="provNamespace">Namespace of the provider.</param>
        /// <param name="className">Class name.</param>
        /// <param name="methodName">Name of the method.</param>
        /// <param name="methodParameters">Parameters to the method.</param>
        public abstract void InvokeStaticMethod(
            string provNamespace,
            string className,
            string methodName,
            IList<MethodParameter> methodParameters);

        /// <summary>
        /// Invokes a method on the instance.
        /// </summary>
        /// <param name="instance">Instance to be used.</param>
        /// <param name="methodName">Method name.</param>
        /// <param name="methodParameters">Parameters to the method.</param>
        public abstract void InvokeInstanceMethod(
            CimInstance instance,
            string methodName,
            IList<MethodParameter> methodParameters);

        /// <summary>
        /// Converts response XML to .Net instances.
        /// </summary>
        /// <param name="instances">Output.</param>
        public abstract void ConvertResponseToInstanceData(out IList<CimInstance> instances);
    }
}
