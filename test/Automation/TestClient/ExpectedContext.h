/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.     
*/
/**
    \ExpectedContext.h 
    \brief       < Parse PropertiesMaps.xml to run command for expected property value. > 
    \date        12-28-10 11:23:02
*/
/*----------------------------------------------------------------------------*/
#ifndef _ExpectedContext_h
#define _ExpectedContext_h  

#include <micxx/dinstance.h>
#include <micxx/array.h>
#include <string>
#include <base/strings.h>
#include <vector>
#include <map>
#include <xml/xml.h>


/*----------------------------------------------------------------------------*/
/**
    < The expected context. The context contains expected value of property for all hadware classes  >
    \date        12-28-10 11:23:02
    < This class is used to parse PropertiesMaps.xml to create DInstance. 
    Execute Linux command to get expected value. save it to DInstance. > 
*/
class ExpectedContext
{
public: 
    ExpectedContext();
    ExpectedContext(mi::Array<mi::DInstance> &instances, FILE& sout);

    ~ExpectedContext();

    mi::Array<mi::DInstance>* GetExpectedInstance();
    bool Parse(const char* path); 

protected:   
    bool ReadXml(const char* path, std::vector<char>& data);
    mi::String GetAttribute(XML_Elem &element, mi::String attributeName);
    mi::String GetInnerText(XML &xml, XML_Elem &element);

    void CreateInstances(const mi::String& className, const mi::String& instanceKey, const mi::String& keyValue, mi::Array<int> &instancesSame);
    void AppendInstance(const mi::String& className, const mi::String& instanceKey, const mi::String& keyValue, mi::Array<int> &instancesSame);
    void SetInstanceValue(mi::DInstance* pCurrent, const mi::String &instanceKey, const mi::String &propertyName, const mi::String &methodName, mi::String value, mi::Type dataType, bool isKey);
    void GetExpectedValue(const mi::String &key, mi::String &val);

private:
    mi::Array<mi::DInstance> *m_pAllInstances;
    FILE* m_sout;
    std::map<std::string, std::string>  m_propertyFunction;
};

#endif

