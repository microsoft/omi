//-----------------------------------------------------------------------
// <copyright file="XmlParser.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-zhegu</author>
// <description></description>
// <history>11/17/2010 01:38:20 PM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using System.IO;
    using System.Text;
    using System.Xml;
    using System.Xml.Serialization;

    public static class XmlParser
    {
        /// <summary>
        /// Deserialize Xml format string to Instance
        /// </summary>
        /// <typeparam name="T">The type of the instance</typeparam>
        /// <param name="xmlString">The Xml format string</param>
        /// <returns>The Instance which is converted from Xml format string</returns>
        public static T FromXmlString<T>(string xmlString)
        {
            if (string.IsNullOrEmpty(xmlString))
            {
                return default(T);
            }

            using (StringReader stringReader = new StringReader(xmlString))
            {
                XmlSerializer xmlSerializer = new XmlSerializer(typeof(T));
                return (T)xmlSerializer.Deserialize(stringReader);
            }
        }

        /// <summary>
        /// Serialize the Instance to xml format string
        /// </summary>
        /// <typeparam name="T">The type of the instance</typeparam>
        /// <param name="theObject">The Instance which is needed to serialize</param>
        /// <returns>The Xml format string</returns>
        public static string ToXmlString<T>(T theObject)
        {
            StringBuilder sb = new StringBuilder();
            using (XmlWriter xmlWriter = XmlWriter.Create(sb))
            {
                XmlSerializer xmlSerializer = new XmlSerializer(typeof(T));
                xmlSerializer.Serialize(xmlWriter, theObject);
            }

            return sb.ToString();
        }
    }

}
