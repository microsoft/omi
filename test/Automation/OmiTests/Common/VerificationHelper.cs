//-----------------------------------------------------------------------
// <copyright file="VerificationHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-zhegu, v-hotong,v-erlv</author>
// <description></description>
// <history>12/2/2010 Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Linq;
    using System.Reflection;
    using System.Xml.Linq;

    /// <summary>
    /// Helper class for verification methods
    /// </summary>
    public class VerificationHelper
    {
        /// <summary>
        /// Verify instances with expect result.
        /// </summary>
        /// <param name="verifyXmlFilePath">The path of verify Xml File</param>
        /// <param name="id">The test case id</param>
        /// <param name="actualInstances">The actual CimInstances</param>
        /// <param name="expectedInstances">The expected CimInstances</param>
        /// <param name="logger">The Logger</param>
        /// <param name="clientType">Binary Client or WSManClient</param>
        /// <returns>Verify result, true for pass and false for failed</returns>
        public static bool VerifyInstancesData(
                        string verifyXmlFilePath,
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
                        xmlElementString = xmlElement.ToString();
                        CimInstance instance = XmlParser.FromXmlString<CimInstance>(xmlElementString);
                        if (instance != null)
                        {
                            expectedInstances.Add(instance);
                        }
                    }
                }
            }

            return CollectionEquals(actualInstances, expectedInstances, logger, clientType);
        }

        /// <summary>
        /// Compare two enumerable instances collections whether are equaled.
        /// </summary>
        /// <param name="actualEnumerable">A instance which implement IEnumerable.</param>
        /// <param name="exceptedEnumerable">A instance which implement IEnumerable.</param>
        /// <param name="logger">The Logger.</param>
        /// <returns>true if these two instances are equal, otherwise, false.</returns>
        internal static bool CollectionEquals(IEnumerable actualEnumerable, IEnumerable exceptedEnumerable, Logger logger, string clientType)
        {
            if (logger == default(Logger))
            {
                throw new NullReferenceException("The logger is null reference!");
            }

            List<bool> isEqualsList = new List<bool>();

            if (object.ReferenceEquals(actualEnumerable, exceptedEnumerable))
            {
                return true;
            }

            if (object.ReferenceEquals(actualEnumerable, null) || object.ReferenceEquals(exceptedEnumerable, null))
            {
                logger.WriteError("One of these two enumerable instances is Null Reference");
                return false;
            }

            if (actualEnumerable.GetType() != exceptedEnumerable.GetType())
            {
                logger.WriteError("The types of these two enumerable instances are different");
                return false;
            }

            // Compare the counts of two collections.
            var aCount = GetCollectionElementCount(actualEnumerable);
            var bCount = GetCollectionElementCount(exceptedEnumerable);
            if (aCount != bCount)
            {
                logger.WriteError("The counts of these two enumerable instances are different");
                logger.WriteError("The count of actual enumerable is {0}", aCount);
                logger.WriteError("The count of expected enumerable is {0}", bCount);
                return false;
            }

            var aList = actualEnumerable.Cast<object>().ToArray();
            var bList = exceptedEnumerable.Cast<object>().ToArray();
            for (int i = 0; i < aList.Length; i++)
            {
                var aObj = aList[i];
                var bObj = bList[i];

                // Compare the two CimInstance.
                CimInstance aCimInstance = aObj as CimInstance;
                if (aCimInstance != null)
                {
                    if (!CimInstanceEquals(aCimInstance, (CimInstance)bObj, logger, clientType))
                    {
                        isEqualsList.Add(false);
                    }

                    continue;
                }

                // Compare the properties of the two CimInstnces.
                CimProperty aCimProperty = aObj as CimProperty;
                if (aCimProperty != null)
                {
                    if (!CimPropertyEquals(aCimProperty, (CimProperty)bObj, logger, clientType))
                    {
                        isEqualsList.Add(false);
                    }

                    continue;
                }

                if (!object.Equals(aObj, bObj))
                {
                    isEqualsList.Add(false);
                }
            }

            bool isEquals = true;
            if (isEqualsList.Any(e => e == false))
            {
                isEquals = false;
            }

            isEqualsList.Clear();
            return isEquals;
        }

        /// <summary>
        /// Compare two enumerable instances whether are equaled.
        /// </summary>
        /// <param name="resultCimInstance">A instance which implement IEnumerable.</param>
        /// <param name="expectedCimInstance">A instance which implement IEnumerable.</param>
        /// <param name="logger">The Logger.</param>
        /// <returns>true if these two instances are equal, otherwise, false.</returns>        
        private static bool CimInstanceEquals(CimInstance resultCimInstance, CimInstance expectedCimInstance, Logger logger, string clientType)
        {
            if (logger == default(Logger))
            {
                throw new NullReferenceException("The logger is null reference!");
            }

            if (object.ReferenceEquals(resultCimInstance, expectedCimInstance))
            {
                return true;
            }

            if (object.ReferenceEquals(resultCimInstance, null) || object.ReferenceEquals(expectedCimInstance, null))
            {
                logger.WriteError("One of these two CimInstances is Null Reference.");
                return false;
            }

            logger.WriteFatal("Start to Compare result CimInstance whose class name is {0}", resultCimInstance.ClassName);
            if (resultCimInstance.GetType() != expectedCimInstance.GetType())
            {
                logger.WriteError("The types of these two CimInstances are different");
                return false;
            }

            // Compare the value of the propeties.
            IEnumerable<PropertyInfo> propertyInfoList = resultCimInstance.GetType().GetProperties();
            if (string.Equals(clientType, "wsman", StringComparison.OrdinalIgnoreCase))
            {
                // If the client type is wsman, we only comapre ClassName and Properties in CimInstance
                propertyInfoList = propertyInfoList.Where(p => p.Name == "ClassName" || p.Name == "Properties");
            }
            foreach (PropertyInfo propertyInfo in propertyInfoList)
            {
                object resultPropertyValue = propertyInfo.GetValue(resultCimInstance, null);
                object expectedPropertyValue = propertyInfo.GetValue(expectedCimInstance, null);
                IEnumerable<CimProperty> resultCimProperties = resultPropertyValue as IEnumerable<CimProperty>;
                if (resultCimProperties != null)
                {
                    if (!CollectionEquals(resultCimProperties, (IEnumerable<CimProperty>)expectedPropertyValue, logger, clientType))
                    {
                        logger.WriteError("Fail: Compare the current CimInstance whose name called {0} is unsccessful !", resultCimInstance.ClassName);
                        return false;
                    }

                    continue;
                }

                if (!object.Equals(resultPropertyValue, expectedPropertyValue))
                {
                    logger.WriteError("Fail: Compare the current CimInstance whose name called {0} is unsccessful !", resultCimInstance.ClassName);
                    return false;
                }
            }

            logger.WriteFatal("Pass: Compare the current CimInstance whose name called {0} is sccessful !", resultCimInstance.ClassName);
            return true;
        }

        /// <summary>
        /// Compare the properties of two enumerable instances whether are equaled.
        /// </summary>
        /// <param name="resultCimProperty">A property which implement CimProperty.</param>
        /// <param name="expectedCimProperty">A property which implement CimProperty.</param>
        /// <param name="logger">The Logger.</param>
        /// <returns>true if these properties are equal, otherwise ,false.</returns>
        private static bool CimPropertyEquals(CimProperty resultCimProperty, CimProperty expectedCimProperty, Logger logger, string clientType)
        {
            if (logger == default(Logger))
            {
                throw new NullReferenceException("The logger is null reference!");
            }

            if (object.ReferenceEquals(resultCimProperty, expectedCimProperty))
            {
                return true;
            }

            if (object.ReferenceEquals(resultCimProperty, null) || object.ReferenceEquals(expectedCimProperty, null))
            {
                logger.WriteError("One of these two CimProperties is Null Reference");
                return false;
            }

            if (resultCimProperty.GetType() != expectedCimProperty.GetType())
            {
                logger.WriteError("The types of these two CimProperties are different");
                return false;
            }

            // Verify each property's Name and Value.
            IEnumerable<PropertyInfo> propertyInfoList = resultCimProperty.GetType().GetProperties();
            if (string.Equals(clientType, "wsman", System.StringComparison.OrdinalIgnoreCase))
            {
                // If the client type is wsman, we only comapre Name and Value in CimProperty
                propertyInfoList = propertyInfoList.Where(property => property.Name == "Name" || property.Name == "Value");
            }
            foreach (PropertyInfo propertyInfo in propertyInfoList)
            {
                object resultPropertyValue = propertyInfo.GetValue(resultCimProperty, null);
                object expectedPropertyValue = propertyInfo.GetValue(expectedCimProperty, null);
                string resultStringProperty = resultPropertyValue as string;
                if (resultStringProperty == null)
                {
                    IEnumerable resultArrayProperty = resultPropertyValue as IEnumerable;
                    if (resultArrayProperty != null)
                    {
                        if (!CollectionEquals(resultArrayProperty, (IEnumerable)expectedPropertyValue, logger, clientType))
                        {
                            logger.WriteError("The Arrays of these two CimProperty are different");
                            return false;
                        }

                        continue;
                    }

                    CimInstance resultCimInstanceProperty = resultPropertyValue as CimInstance;
                    if (resultCimInstanceProperty != null)
                    {
                        if (!CimInstanceEquals(resultCimInstanceProperty, (CimInstance)expectedPropertyValue, logger, clientType))
                        {
                            logger.WriteError("The CimInstance of these two CimProperty are different");
                            return false;
                        }

                        continue;
                    }
                }

                if (!object.Equals(resultPropertyValue, expectedPropertyValue))
                {
                    logger.WriteError("Fail: The resluts of CimProperty whose name called {0} is different.The excepted value is {1} ,but the actual value is {2} .", expectedCimProperty.Name, expectedPropertyValue.ToString(), resultPropertyValue.ToString());
                    return false;
                }
            }

            logger.WriteFatal("Pass : The results of CimProperty whose name called {0} are the same .", resultCimProperty.Name);
            return true;
        }

        /// <summary>
        /// Get the counts of the collection's elements.
        /// </summary>
        /// <param name="enumerable">A collections which implement IEnumerable.</param>
        /// <returns>The count of the collection's elements. </returns>
        private static int GetCollectionElementCount(IEnumerable enumerable)
        {
            var collection = enumerable as ICollection;
            return collection != null ? collection.Count : enumerable.Cast<object>().Count();
        }
    }
}
