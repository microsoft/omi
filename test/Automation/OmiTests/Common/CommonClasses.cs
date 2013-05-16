//-----------------------------------------------------------------------
// <copyright file="CommonClasses.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>sunilmu, v-zhegu</author>
// <description></description>
// <history>11/11/2010 10:52:31 AM: Created</history>
//-----------------------------------------------------------------------

namespace Scx.OmiTests.Common
{
    using System;
    using System.Collections.Generic;
    using System.Xml;
    using System.Xml.Schema;
    using System.Xml.Serialization;

    public class SysInfo
    {
        public string Hostname { get; set; }
        public string Username { get; set; }
        public string Password { get; set; }
        public string XmlSchemaPrefix { get; set; }
        public uint PortNumber { get; set; }
        public bool IsHttps { get; set; }
    }

    public class CimProperty : IXmlSerializable
    {
        private static bool ConvertToBoolean(string value)
        {
            bool convertToBool;
            return bool.TryParse(value, out convertToBool) && convertToBool;
        }

        /// <summary>
        /// Convert bianry client datetime value format to wsman format.
        /// </summary>
        /// <param name="dtValue">datetime string from binary client enumerat</param>
        /// <returns>datetime string which foramt is same as wsman return</returns>
        private string ConvertToWsManDateTimeFormat(string dtValue)
        {
            if (dtValue.Length == 0)
            {
                return string.Empty;
            }
            string wsManDateTimeString = string.Empty;
            char splitTimeChar = '.';
            char splitZeroCharSub = '-';
            char splitZeroCharAdd = '+';
            char splitZeor = ' ';
            string bigTime = string.Empty;
            string millisec = string.Empty;
            string zero = string.Empty;

            string[] dtInfo = dtValue.Split(splitTimeChar);
            // the datetime value doesn't not contain millisecond and time zone.
            if (dtInfo.Length == 1)
            {
                //yyyy-mm-ddThh:mm:ss
                dtInfo[0] = dtInfo[0].Insert(4, "-");
                dtInfo[0] = dtInfo[0].Insert(7, "-");
                dtInfo[0] = dtInfo[0].Insert(10, "T");
                dtInfo[0] = dtInfo[0].Insert(13, ":");
                dtInfo[0] = dtInfo[0].Insert(16, ":");
                wsManDateTimeString = dtInfo[0];
                return wsManDateTimeString;
            }
            else
            {
                //yyyy-mm-ddThh:mm:ss
                dtInfo[0] = dtInfo[0].Insert(4, "-");
                dtInfo[0] = dtInfo[0].Insert(7, "-");
                dtInfo[0] = dtInfo[0].Insert(10, "T");
                dtInfo[0] = dtInfo[0].Insert(13, ":");
                dtInfo[0] = dtInfo[0].Insert(16, ":");
                bigTime = dtInfo[0];

                string[] dtmmInfo = null;
                if (dtInfo[1].Contains("-"))
                {
                    dtmmInfo = dtInfo[1].Split(splitZeroCharSub);
                    splitZeor = splitZeroCharSub;
                }
                else if (dtInfo[1].Contains("+"))
                {
                    dtmmInfo = dtInfo[1].Split(splitZeroCharAdd);
                    splitZeor = splitZeroCharAdd;
                }
                else
                {
                    throw new NotImplementedException("Zero should have signed (+/-) specified !");
                }

                millisec = dtmmInfo[0];

                if (dtmmInfo.Length > 1)
                {
                    int dtmmLength = dtmmInfo[dtmmInfo.Length - 1].Length;
                    if (!dtmmInfo[dtmmInfo.Length - 1].Contains(":") && dtmmLength < 4)
                    {
                        int zeroNumber = 4 - dtmmLength;
                        string zeroStr = new string('0', zeroNumber);
                        dtmmInfo[dtmmInfo.Length - 1] = dtmmInfo[dtmmInfo.Length - 1].Insert(0, zeroStr);
                        dtmmInfo[dtmmInfo.Length - 1] = dtmmInfo[dtmmInfo.Length - 1].Insert(2, ":");
                    }

                    zero = dtmmInfo[dtmmInfo.Length - 1];
                }
            }

            wsManDateTimeString = bigTime + splitTimeChar.ToString() + millisec + splitZeor.ToString() + zero;
            return wsManDateTimeString;
        }

        public string Name { get; set; }

        public string PropertyType { get; set; }

        public object Value { get; set; }

        public bool IsKey { get; set; }

        public bool IsRef { get; set; }

        public bool IsArray { get; set; }

        #region IXmlSerializable Members

        public XmlSchema GetSchema()
        {
            return null;
        }

        /// <summary>
        /// Generates an object from its XML representation.
        /// </summary>
        /// <param name="reader">The System.Xml.XmlReader stream from which the object is deserialized</param>
        public void ReadXml(XmlReader reader)
        {
            if (reader.MoveToContent() == XmlNodeType.Element && reader.LocalName == "CimProperty")
            {
                Name = reader.GetAttribute("Name");
                PropertyType = reader.GetAttribute("PropertyType");
                IsKey = ConvertToBoolean(reader.GetAttribute("IsKey"));
                IsRef = ConvertToBoolean(reader.GetAttribute("IsRef"));
                IsArray = ConvertToBoolean(reader.GetAttribute("IsArray"));
                reader.ReadStartElement();
                if (reader.MoveToContent() == XmlNodeType.Text)
                {
                    if (PropertyType == "DATETIME")
                    {
                        string dtValue = reader.ReadString();
                        Value = ConvertToWsManDateTimeFormat(dtValue);                      
                    }
                    else
                    {
                        Value = reader.ReadString();
                    }
                }
                else if (reader.MoveToContent() == XmlNodeType.Element && reader.LocalName == "CimInstance")
                {
                    string cimInstanceXmlString = reader.ReadOuterXml();
                    CimInstance instance = XmlParser.FromXmlString<CimInstance>(cimInstanceXmlString);
                    if (instance != null)
                    {
                        Value = instance;
                    }
                }
                else if (reader.MoveToContent() == XmlNodeType.Element && reader.LocalName == "ArrayElement")
                {
                    List<object> objectList = new List<object>();
                    do
                    {
                        string innerXml = reader.ReadInnerXml();
                        // if array element is CinInstance , do with Ciminstacne operation
                        if (innerXml.StartsWith("<CimInstance") && innerXml.EndsWith("</CimInstance>"))
                        {
                            CimInstance instance = XmlParser.FromXmlString<CimInstance>(innerXml);
                            if (instance != null)
                            {
                                objectList.Add(instance);
                            }
                        }
                        else
                        {
                            // if common type value , just add to the value list .
                            objectList.Add(innerXml);
                        }

                    } while (reader.MoveToContent() == XmlNodeType.Element && reader.LocalName == "ArrayElement");
                    Value = objectList;
                }

                reader.ReadEndElement();
            }
        }

        /// <summary>
        /// Converts an object into its XML representation.
        /// </summary>
        /// <param name="writer">The System.Xml.XmlWriter stream to which the object is serialized</param>
        public void WriteXml(XmlWriter writer)
        {
            throw new NotImplementedException();
        }

        #endregion
    }

    public class CimInstance
    {
        public CimInstance()
        {
            Properties = new List<CimProperty>();
        }

        [XmlAttribute(AttributeName = "Namespace")]
        public string Namespace { get; set; }

        [XmlAttribute(AttributeName = "ClassName")]
        public string ClassName { get; set; }

        [XmlArrayAttribute("Properties")]
        public List<CimProperty> Properties { get; set; }
    }

    public class MethodParameter
    {
        public string Name { get; set; }
        public object Value { get; set; }
    }
}
