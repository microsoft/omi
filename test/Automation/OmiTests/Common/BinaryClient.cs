//-----------------------------------------------------------------------
// <copyright file="BinaryClient.cs" company="Microsoft">
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
    using System.Linq;
    using System.Text;
    using System.Xml.Linq;

    public class BinaryClient : CimServerClient, IDisposable
    {
        private readonly SshHelper sshHelper;

        private bool isDisposed;

        public string ClientLocation { get; set; }

        public BinaryClient(Logger logger, SysInfo systemInfo, string clientLoc)
            : base(logger, systemInfo)
        {
            ClientLocation = clientLoc;
            sshHelper = new SshHelper(sys.Hostname, sys.Username, sys.Password, log);
        }

        public void Dispose()
        {
            if (!this.isDisposed)
            {
                lock (this)
                {
                    if (!this.isDisposed)
                    {
                        this.sshHelper.Dispose();
                        this.isDisposed = true;
                    }
                }
            }
        }

        /// <summary>
        /// Enumerates all instances of the given class.
        /// </summary>
        /// <param name="provNamespace">Namespace of the provider.</param>
        /// <param name="className">Class to be enumerated.</param>
        /// <param name="deepInheritance">True if the enumeration has to be deep.</param>
        public override void Enumerate(string provNamespace, string className, bool deepInheritance)
        {
            try
            {
                this.log.WriteInfo("Begin to Enumerate the instances on OmiServer");

                string command = deepInheritance
                                     ? string.Format("{0} ei {1} {2} {3}", ClientLocation, "-deep", provNamespace, className)
                                     : string.Format("{0} ei {1} {2}", ClientLocation, provNamespace, className);
                sshHelper.RunCmd(command);
                response = XDocument.Parse(sshHelper.StdOut);
                this.log.WriteInfo("Succeeded to Enumerate the instances on OmiServer");
            }
            catch (Exception e)
            {              
                this.HandleException(e, "Failed to Enumerate the instance on OmiServer");
            }
        }

        /// <summary>
        /// Get is currently only supported for non-Association classes.
        /// </summary>
        /// <param name="instance">Instance to get.</param>
        public override void Get(CimInstance instance)
        {
            try
            {
                this.log.WriteInfo("Begin to Get the instance on OmiServer");
                IEnumerable<CimProperty> keyPropertyList = instance.Properties.Where(p => p.IsKey);

                // Build the key-value string
                StringBuilder keyValueStringBuilder = new StringBuilder();
                foreach (CimProperty keyProperty in keyPropertyList)
                {
                    keyValueStringBuilder.AppendFormat("{0} {1} ", keyProperty.Name, keyProperty.Value);
                }

                sshHelper.RunCmd(string.Format("{0} gi {1} {{ {2} {3} }}",
                    ClientLocation,
                    instance.Namespace,
                    instance.ClassName,
                    keyValueStringBuilder));

                response = XDocument.Parse(sshHelper.StdOut);
                this.log.WriteInfo("Succeeded to Get the instance on OmiServer");
            }
            catch (Exception e)
            {
                this.HandleException(e, "Failed to Get the instance on OmiServer");
            }
        }

        /// <summary>
        /// Invokes a method on the instance.
        /// </summary>
        /// <param name="instance">Instance to be used.</param>
        /// <param name="methodName">Method name.</param>
        /// <param name="methodParameters">Parameters to the method.</param>
        public override void InvokeInstanceMethod(
            CimInstance instance,
            string methodName,
            IList<MethodParameter> methodParameters)
        {
            try
            {
                this.log.WriteInfo("Begin to Invoke the instance method on OmiServer");
                IEnumerable<CimProperty> keyPropertyList = instance.Properties.Where(p => p.IsKey);

                // Build the key-value string
                StringBuilder keyValueStringBuilder = new StringBuilder();
                foreach (CimProperty keyProperty in keyPropertyList)
                {
                    keyValueStringBuilder.AppendFormat("{0} {1} ", keyProperty.Name, keyProperty.Value);
                }

                // Build the parameter-value string
                StringBuilder methodParameterStringBuilder = new StringBuilder();
                foreach (MethodParameter methodParameter in methodParameters)
                {
                    methodParameterStringBuilder.AppendFormat("{0} {1} ", methodParameter.Name, methodParameter.Value);
                }

                sshHelper.RunCmd(string.Format("{0} iv {1} {{ {2} {3} }} {4} {{ {5} }}",
                    ClientLocation,
                    instance.Namespace,
                    instance.ClassName,
                    keyValueStringBuilder,
                    methodName,
                    methodParameterStringBuilder));

                response = XDocument.Parse(sshHelper.StdOut);
                this.log.WriteInfo("Succeeded to Invoke the instance method on OmiServer");
            }
            catch (Exception e)
            {
                this.HandleException(e, "Failed to Invoke the instance method on OmiServer");
            }
        }

        /// <summary>
        /// Invokes a method on the class.
        /// </summary>
        /// <param name="provNamespace">Namespace of the provider.</param>
        /// <param name="className">Class name.</param>
        /// <param name="methodName">Name of the method.</param>
        /// <param name="methodParameters">Parameters to the method.</param>
        public override void InvokeStaticMethod(
            string provNamespace,
            string className,
            string methodName,
            IList<MethodParameter> methodParameters)
        {
            try
            {
                this.log.WriteInfo("Begin to Invoke the static method on OmiServer");

                // Build the parameter-value string
                StringBuilder methodParameterStringBuilder = new StringBuilder();
                foreach (MethodParameter methodParameter in methodParameters)
                {
                    methodParameterStringBuilder.AppendFormat("{0} {1} ", methodParameter.Name, methodParameter.Value);
                }

                sshHelper.RunCmd(string.Format("{0} iv {1} {{ {2} }} {3} {{ {4} }}",
                    ClientLocation,
                    provNamespace,
                    className,
                    methodName,
                    methodParameterStringBuilder));

                response = XDocument.Parse(sshHelper.StdOut);
                this.log.WriteInfo("Succeeded to Invoke the static method on OmiServer");
            }
            catch (Exception e)
            {
                this.HandleException(e, "Failed to Invoke the static method on OmiServer");
            }
        }

        /// <summary>
        /// Converts response XML to .Net instances.
        /// </summary>
        /// <param name="instances">Output.</param>
        public override void ConvertResponseToInstanceData(out IList<CimInstance> instances)
        {
            instances = new List<CimInstance>();
            if (response != null)
            {
                IEnumerable<XElement> xmlElements = response.Root.Elements();
                string xmlElementString = string.Empty;
                foreach (XElement xmlElement in xmlElements)
                {
                    try
                    {
                        xmlElementString = xmlElement.ToString();
                        CimInstance instance = XmlParser.FromXmlString<CimInstance>(xmlElementString);
                        if (instance != null)
                        {
                            instances.Add(instance);
                        }
                    }
                    catch (InvalidOperationException e)
                    {
                        HandleException(e, string.Format("Failed to Deserialize Xml string: {0}", xmlElementString));
                    }
                }
            }
        }

        private void HandleException(Exception e, string failedInfo)
        {
            // Resolve the issue if the xml output append some error info
            StringBuilder errorXmlParse = new StringBuilder();
            errorXmlParse.AppendFormat("<ParseError>{0}</ParseError>", sshHelper.StdOut);
            response = XDocument.Parse(errorXmlParse.ToString());
            if (this.log == null)
            {
                // WARNING: This will truncate the stack of the exception 
                throw e;
            }

            this.log.WriteError("Failed Info: ", failedInfo);
            this.log.WriteError("Hostname: {0}", this.sys.Hostname);
            this.log.WriteError("Exception Info: {0}", e.ToString());
        }
    }
}
