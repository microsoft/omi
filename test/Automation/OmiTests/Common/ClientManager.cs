//-----------------------------------------------------------------------
// <copyright file="ClientManager.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-zhegu</author>
// <description></description>
// <history>11/29/2010 01:38:20 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using System.Collections.Generic;
    using System.Xml.Linq;

    /// <summary>
    /// Generate different client according to the specified client type
    /// </summary>
    public class ClientManager
    {
        private CimServerClient client;

        // This property is used in omireg test.
        public XDocument Response
        {
            get { return this.client.Response; }
        }

        public ClientManager(string clientType, Logger logger, SysInfo sys, string clientLoc)
        {
            if (string.Equals(clientType, "binary", System.StringComparison.OrdinalIgnoreCase))
            {
                client = new BinaryClient(logger, sys, clientLoc);
            }
            else if (string.Equals(clientType, "wsman", System.StringComparison.OrdinalIgnoreCase))
            {
                client = new WsmanClient(logger, sys);
            }
        }

        /// <summary>
        /// Enumerates all instances of the given class
        /// </summary>
        /// <param name="provNamespace">Namespace of the provider</param>
        /// <param name="className">Class to be enumerated</param>
        /// <param name="deepInheritance">True if the enumeration has to be deep.</param>
        public void Enumerate(string provNamespace, string className, bool deepInheritance)
        {
            client.Enumerate(provNamespace, className, deepInheritance);
        }

        /// <summary>
        /// Get is currently only supported for non-Association classes.
        /// </summary>
        /// <param name="instance">Instance to get.</param>
        public void Get(CimInstance instance)
        {
            client.Get(instance);
        }

        /// <summary>
        /// Invokes a method on the instance.
        /// </summary>
        /// <param name="instance">Instance to be used.</param>
        /// <param name="methodName">Method name.</param>
        /// <param name="methodParameters">Parameters to the method.</param>
        public void InvokeInstanceMethod(
            CimInstance instance,
            string methodName,
            IList<MethodParameter> methodParameters)
        {
            client.InvokeInstanceMethod(instance, methodName, methodParameters);
        }

        /// <summary>
        /// Invokes a method on the class.
        /// </summary>
        /// <param name="provNamespace">Namespace of the provider.</param>
        /// <param name="className">Class name.</param>
        /// <param name="methodName">Name of the method.</param>
        /// <param name="methodParameters">Parameters to the method.</param>
        public void InvokeStaticMethod(
            string provNamespace,
            string className,
            string methodName,
            IList<MethodParameter> methodParameters)
        {
            client.InvokeStaticMethod(provNamespace, className, methodName, methodParameters);
        }

        /// <summary>
        /// Converts response XML to .Net instances.
        /// </summary>
        /// <param name="instances">Output.</param>
        public void ConvertResponseToInstanceData(out IList<CimInstance> instances)
        {
            client.ConvertResponseToInstanceData(out instances);
        }
    }
}
