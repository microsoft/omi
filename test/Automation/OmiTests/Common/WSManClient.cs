//-----------------------------------------------------------------------
// <copyright file="WsmanClient.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-zhegu</author>
// <description></description>
// <history>12/16/2010 3:50:59 PM: Created</history>
// <history></history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Xml.Linq;

    public class WsmanClient : CimServerClient
    {
        private const String xmlSchemaSuffix = "?__cimnamespace=";

        private readonly WsmanQuery wsmanQuery;

        public WsmanClient(Logger logger, SysInfo systemInfo)
            : base(logger, systemInfo)
        {
            wsmanQuery = new WsmanQuery(log, sys.Hostname, sys.Username, sys.Password, sys.PortNumber, sys.XmlSchemaPrefix, string.Empty, sys.IsHttps);
        }

        public override void Enumerate(string provNamespace, string className, bool deepInheritance)
        {
            try
            {
                this.log.WriteInfo("Begin to Enumerate the instances on OmiServer");
                List<string> enumerateQueryXml;
                wsmanQuery.XmlSchemaSuffix = String.Format("{0}{1}", xmlSchemaSuffix, provNamespace);
                wsmanQuery.EnumerateScx(out enumerateQueryXml, className);
                // Add root element, because there are too much elements appeared when you enumerate a class
                StringBuilder result = new StringBuilder("<root>");
                foreach (var queryXml in enumerateQueryXml)
                {
                    result.Append(queryXml);
                }

                result.Append("</root>");
                this.response = XDocument.Parse(result.ToString());
                this.log.WriteInfo("Succeeded to Enumerate the instance on OmiServer");
            }
            catch (Exception e)
            {
                this.HandleException(e, "Failed to Enumerate the instance on OmiServer");
            }

        }

        public override void Get(CimInstance instance)
        {
            string getQueryResult;
            IEnumerable<CimProperty> keyPropertyList = instance.Properties.Where(p => p.IsKey);
            StringBuilder keyPairStringBuilder = new StringBuilder();
            foreach (var keyProperty in keyPropertyList)
            {
                keyPairStringBuilder.AppendFormat("{0}={1}+", keyProperty.Name, keyProperty.Value);
            }

            // Remove the last Plus Sign
            int lastPlusSignIndex = keyPairStringBuilder.Length - 1;
            keyPairStringBuilder.Remove(lastPlusSignIndex, 1);

            wsmanQuery.XmlSchemaSuffix = String.Format("{0}{1}", xmlSchemaSuffix, instance.Namespace);
            wsmanQuery.GetScx(out getQueryResult, instance.ClassName, keyPairStringBuilder.ToString());
            StringBuilder result = new StringBuilder("<root>");
            result.Append(getQueryResult);
            result.Append("</root>");
            this.response = XDocument.Parse(result.ToString());
        }

        public override void InvokeStaticMethod(string provNamespace, string className, string methodName, IList<MethodParameter> methodParameters)
        {
            string invokeQueryResult;
            wsmanQuery.XmlSchemaSuffix = String.Format("{0}{1}", xmlSchemaSuffix, provNamespace);
            StringBuilder parameters = new StringBuilder("<p:");
            parameters.AppendFormat("{0}_INPUT xmlns:p=\"{1}{2}.xsd\">", methodName, this.wsmanQuery.XmlSchemaPrefix, className);
            foreach (var methodParameter in methodParameters)
            {
                parameters.AppendFormat("<p:{0}>{1}</p:{0}>", methodParameter.Name, methodParameter.Value);
            }

            parameters.AppendFormat("</p:{0}_INPUT>", methodName);
            wsmanQuery.InvokeScx(out invokeQueryResult, className, methodName, parameters.ToString());
            this.response = XDocument.Parse(invokeQueryResult.ToString());
        }

        public override void InvokeInstanceMethod(CimInstance instance, string methodName, IList<MethodParameter> methodParameters)
        {
            string invokeQueryResult;
            IEnumerable<CimProperty> keyPropertyList = instance.Properties.Where(p => p.IsKey);
            StringBuilder keyPairStringBuilder = new StringBuilder();
            foreach (var keyProperty in keyPropertyList)
            {
                keyPairStringBuilder.AppendFormat("+{0}={1}", keyProperty.Name, keyProperty.Value);
            }

            wsmanQuery.XmlSchemaSuffix = String.Format("{0}{1}{2}", xmlSchemaSuffix, instance.Namespace, keyPairStringBuilder);

            StringBuilder parameters = new StringBuilder("<p:");
            parameters.AppendFormat("{0}_INPUT xmlns:p=\"{1}{2}.xsd\">", methodName, this.wsmanQuery.XmlSchemaPrefix, instance.ClassName);
            foreach (var methodParameter in methodParameters)
            {
                parameters.AppendFormat("<p:{0}>{1}</p:{0}>", methodParameter.Name, methodParameter.Value);
            }

            parameters.AppendFormat("</p:{0}_INPUT>", methodName);
            wsmanQuery.InvokeScx(out invokeQueryResult, instance.ClassName, methodName, parameters.ToString());
            this.response = XDocument.Parse(invokeQueryResult);

            // Remove NewStateProperty because we can't get this property in Binary Client
            XElement newStatePropertyElement = response.Root.Descendants().FirstOrDefault(e => e.Name.LocalName == "NewState");
            if (newStatePropertyElement != null)
            {
                newStatePropertyElement.Remove();
            }
        }

        public override void ConvertResponseToInstanceData(out IList<CimInstance> instances)
        {
            instances = new List<CimInstance>();
            foreach (XElement cimInstanceElement in response.Root.Elements())
            {
                CimInstance cimInstance = new CimInstance
                {
                    ClassName = cimInstanceElement.Name.LocalName
                };

                LoadCimProperty(cimInstanceElement, cimInstance);
                instances.Add(cimInstance);
            }
        }

        public void LoadCimProperty(XElement cimInstanceElement, CimInstance cimInstance)
        {
            string propertName = string.Empty;
            object propertValue = null;
            foreach (XElement propertyElement in cimInstanceElement.Elements())
            {
                propertName = propertyElement.Name.LocalName;                
                //  current filter datetimeArray beacuse of bug 36123 in Iteration 10
                if (propertName == "datetimeArray")
                {
                    continue;
                }

                IEnumerable<XElement> propertySubElements = propertyElement.Elements();
                if (propertySubElements.Count() != 0)
                {
                    // ref type
                    if (propertySubElements.FirstOrDefault(element => element.Name.LocalName == "ReferenceParameters") != null)
                    {
                       IEnumerable<XElement> refParamElements =
                           propertySubElements.FirstOrDefault(element => element.Name.LocalName == "ReferenceParameters").Elements();
                        XElement classNameElement = refParamElements.FirstOrDefault(element => element.Name.LocalName == "ResourceURI");
                        CimInstance refCimInstance = new CimInstance();
                        refCimInstance.ClassName = classNameElement.Value.Remove(0, classNameElement.Value.LastIndexOf('/') + 1);
                        XElement refCimInstancePropertyElement =
                            refParamElements.FirstOrDefault(element => element.Name.LocalName == "SelectorSet");
                        foreach (XElement refInstanceKeyProperty in refCimInstancePropertyElement.Elements())
                        {
                            CimProperty refCimProperty = new CimProperty();
                            refCimProperty.Name = refInstanceKeyProperty.Attribute("Name").Value;
                            refCimProperty.Value = refInstanceKeyProperty.Value;
                            refCimInstance.Properties.Add(refCimProperty);
                        }
                        propertValue = refCimInstance;
                    }
                    else
                    {
                        XElement instanceNode = propertySubElements.FirstOrDefault();
                        CimInstance instance = new CimInstance { ClassName = instanceNode.Name.LocalName};
                        LoadCimProperty(instanceNode, instance);
                        propertValue = instance;
                    }
                }
                else
                {
                    propertValue = propertyElement.Value;
                }

                CimProperty cimProperty = new CimProperty
                {
                    Name = propertName,
                    Value = propertValue
                };

              CimProperty existProperty =  cimInstance.Properties.FirstOrDefault(props => props.Name == propertName);
              if (existProperty != null)
              {
                  List<object> innerValueList = existProperty.Value as List<object>;
                  if (innerValueList == null)
                  {
                      innerValueList = new List<object>();
                      innerValueList.Add(existProperty.Value);
                  }
                  innerValueList.Add(propertValue);
                  cimInstance.Properties.Remove(existProperty);
                  cimProperty.Value = innerValueList;
                  cimInstance.Properties.Add(cimProperty);
              }
              else
              {
                  cimInstance.Properties.Add(cimProperty);
              }
            }
        }

        private void HandleException(Exception e, string failedInfo)
        {
            if (this.log == null)
            {
                // WARNING: This will truncate the stack of the exception 
                throw e;
            }

            this.response = XDocument.Parse("<OperationError>The operation fails</OperationError>");
            this.log.WriteError("Failure  Infomation: ", failedInfo);
            this.log.WriteError("Hostname: {0}", this.sys.Hostname);
            this.log.WriteError("Exception Info: {0}", e.ToString());
        }
    }
}
