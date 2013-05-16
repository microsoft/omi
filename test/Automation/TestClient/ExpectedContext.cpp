#include "ExpectedContext.h"
#include "CustomizedMethod.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <xml/xml.h>
#include <stdlib.h>
#include <string>
#include <base/strings.h>
#include <common.h>
#include <stdio.h>
#include <map>

#include "TestClient.h"
using namespace std;
using namespace mi;

// Assumed max length of XML file.
const int MAX_XML_LENGTH = 4096;

// Assumed max length of result returned from command line.
const int MAX_RESULT_LENGTH = 1024;

// This is a special variable which is used to replace with key value in Linux command of PropertiesMaps.xml. 
const mi::String KEY_VAR = "$key";

extern std::map<std::string, MODULE_TEST_CALLBACK> s_fn;

ExpectedContext::ExpectedContext()
{
}

ExpectedContext::ExpectedContext(Array<DInstance> &instances, FILE& sout)
{
    this->m_pAllInstances = &instances;
    this->m_sout = &sout;

    if (s_fn.size() <= 0)
    {
        REG_TEST();    
    }
}

ExpectedContext::~ExpectedContext()
{
}

bool ExpectedContext::ReadXml(const char* path, vector<char>& data)
{
    struct stat st;

    if (stat(path, &st) != 0)
    {
        fprintf(this->m_sout,"Error: failed to stat file: %s\n", path);
        return false;
    }

    data.reserve(st.st_size + 1);

    FILE* file = fopen(path, "r");

    if (!file)
    {
        fprintf(this->m_sout,"Error: failed to open file: %s\n", path);
        return false;
    }

    size_t n;
    char buf[MAX_XML_LENGTH];

    while ((n = fread(buf, 1, sizeof(buf), file)) != 0)
    {
        data.insert(data.end(), buf, buf + n);
    }

    data.push_back('\0');

    fclose(file);   
    return true;
}

bool ExpectedContext::Parse(const char* path)
{
    DEBUG_ASSERT(NULL == this->m_pAllInstances);

    XML xml;
    XML_Elem element;
    int result;
    vector<char> data;

    if (!ReadXml(path, data))
    {
        return false;
    }

    XML_Init(&xml);
    XML_SetText(&xml, &data[0]);

	// When Array allocation is out of default, old pointer which points DInstance will be removed by Resize(). 
	// Create index for the same instances so as to access m_pAllInstances by index rather than by instance pointer.
    mi::Array<int> instancesSame;
    String instanceKey;

    // Walk through XML file to read XML node. 
    while ((result = XML_Next(&xml, &element)) == 0)
    { 
        if (strcmp(element.data, "ExpectedContext") == 0)
        {
            // Current node is ClassName node.
            String className = this->GetAttribute(element, T("ClassName"));   
            
            // If no className indicates it is </ExpectedContext>, else it is <ExpectedContext>.
            if (className.GetSize() <= 0)
            {
                // Clear previous ExpectedContext. 
                instancesSame.Clear();
                instanceKey.Clear();
                continue;
            }
            else
            { 
                // Read attributes. 
                instanceKey = this->GetAttribute(element, T("KeyPropertyName"));
                String keyValue = this->GetAttribute(element, T("KeyValue")); 

                // Create instances by key values.
                this->CreateInstances(className, instanceKey, keyValue, instancesSame);
            }
         }
        else if (strcmp(element.data, "ExpectedProperty") == 0)
        { 
            // Current node is property node.             
            String propertyName = this->GetAttribute(element, T("Name"));

            if (propertyName.GetSize() <= 0)
            {
                continue;
            }

            String methodName = this->GetAttribute(element, T("Method"));
            String isKey = this->GetAttribute(element, T("IsKey"));
            String dataType = this->GetAttribute(element, T("PropertyType"));
            String value = this->GetInnerText(xml, element);   

            bool bIsKey = StringToBoolean(isKey);
            mi::Type propertyType = StringToType(dataType);

            // Read all instances which have the same class name.
            for (MI_Uint32 i = 0; i < instancesSame.GetSize(); i++)
            { 
                // Set the instance property value.
				int index = instancesSame[i];
                this->SetInstanceValue(&(this->m_pAllInstances->GetWritableData()[index]), instanceKey, propertyName, methodName, value, propertyType, bIsKey);                 
            } 
        }  
    }

    if (result != 1)
    {
        char msg[1024];
        XML_FormatError(&xml, msg, sizeof(msg));
        fprintf(this->m_sout,"%s:%s\n", path, msg);

        return false;
    }

    return true;
}

// Append a instance.
void ExpectedContext::AppendInstance(const String& className, const String& instanceKey, const String& keyValue, mi::Array<int> &instancesSame)
{   
    DInstance dinstance(className, DInstance::CLASS);
    if (instanceKey.GetSize() > 0)
    {
        dinstance.AddString(instanceKey, keyValue, false, true);
    }

	this->m_pAllInstances->PushBack(dinstance);
    instancesSame.PushBack(this->m_pAllInstances->GetSize() - 1); 
}

// Create instances according to key values.
// Run Linux command to get key values. Every line of command result is a key value of an instance. 
// Multiple lines indicate multiple instances.
void ExpectedContext::CreateInstances(const String& className, const String& instanceKey, const String& keyValue, mi::Array<int> &instancesSame)
{
    String key;
    // If only one instance, directly append.
    if (instanceKey.GetSize() <= 0)
    {
        this->AppendInstance(className, instanceKey, key, instancesSame);
        return;
    }

    String keyValues;

    // Run Linux command to get key values.
    RunCommand(keyValue.Str(), keyValues);

    // Parse key values.
    const MI_Char *p=keyValues.Str();
    const MI_Char delim = '\n';

	mi::Array<mi::String> keys;
	while(*p!=0)
	{
		if(*p==delim)
		{
			// Compare string to find duplicate key.
			bool bFound = false;
			for (int i=0; i < keys.GetSize(); i++)
			{
				if (strcmp(keys[i].Str(), key.Str()) == 0)
				{
					bFound = true;
					break;
				}
			}

			if (!bFound)
			{
				keys.PushBack(key);
				this->AppendInstance(className, instanceKey, key, instancesSame);
			}

			key=String();
		}
		else
		{
			key+=*p;
		}
		++p;
	} 
}

// Set instance property value.
// If property is key and the key value is already set when the instance creates, Needn't set the key value.
// Else set property value as expected value which is gotten by running Linux command or calling customized function.
// Support to replace $key with key value.
void ExpectedContext::SetInstanceValue(DInstance* pCurrent, const String &instanceKey, const String &propertyName, const String &methodName, String value, mi::Type dataType, bool isKey)
{
    String keyValue;
    if (NULL == pCurrent)
    {
        return;  
    }  

    // instanceKey exists.
    bool hasKey = false;
    if (instanceKey.GetSize() > 0)
    {
        hasKey = pCurrent->GetString(instanceKey, keyValue);
    }

     // If property value contains $key, replace it with key value.
    if (hasKey)
    {
        value = Replace(value, KEY_VAR, keyValue);
    }

    // If property attribute is key property and instance exists key property, Needn't set the value.
    if (propertyName.Equal(instanceKey) && hasKey)
    { 
        // Needn't set key property value.
    }
    else
    { 
        //pCurrent->AddValue(propertyName, (MI_Value*)&value, dataType, false, isKey);
		if(dataType==MI_STRINGA)
		{
			// Wrap the value with array.
			StringA valueA;
			valueA.PushBack(value);

			pCurrent->AddStringA(propertyName, valueA, false, isKey);
		}
		else
		{
            pCurrent->AddString(propertyName, value, false, isKey);   
		}
    } 
    
    String className = pCurrent->GetClassName();
    String key = className;
    key += propertyName;           
    map<std::string, std::string>::const_iterator it = this->m_propertyFunction.find(key.Str()); 
    
    if (it == m_propertyFunction.end())
	{
        this->m_propertyFunction.insert(std::pair<std::string, std::string>(key.Str(), methodName.Str()));
    }
}

mi::String ExpectedContext::GetAttribute(XML_Elem &element, mi::String attributeName)
{
    // Walk thorugh XML attributes.
    mi::String propertyName;
    for (unsigned int i = 0; i < element.attrsSize; i++)
    {
        // Current node is property node.
        if (strcmp(element.attrs[i].name, attributeName.Str()) == 0)
        {
            propertyName = MakeString(element.attrs[i].value);  
            break;
        }
    } 

    return propertyName;
}

mi::String ExpectedContext::GetInnerText(XML &xml, XML_Elem &element)
{
    String value = "";

    // Get inner text of property node. 
    if (strcmp(element.data, "ExpectedProperty") == 0 &&
        XML_Next(&xml, &element) == 0 &&
		strlen(element.data) != 0 && 
		strcmp(element.data, "ExpectedProperty") != 0) /*There is a bug in XML class, XML can not read inner text, if the value is empty or null.*/
    {
		value = MakeString(element.data);
    }

    return value;
}

Array<DInstance>* ExpectedContext::GetExpectedInstance()
{
    DEBUG_ASSERT(NULL == this->m_pAllInstances);

    for (MI_Uint32 i = 0; i < this->m_pAllInstances->GetSize(); i++)
    {
        DInstance* pCurrent = &(*(this->m_pAllInstances))[i];
        if (NULL == pCurrent)
        {
            continue;
        }

        String className = pCurrent->GetClassName();  
        for (mi::Uint32 i = 0; i < pCurrent->Count(); i++)
        {
            String name;
            String val;
			MI_Type _type;

            pCurrent->GetName(i, name);
			pCurrent->GetType(i,_type);
            String key = className;
            key += name;        

			if(_type==MI_STRINGA)
			{  
				StringA valA;
				pCurrent->GetStringA(name, valA);    
				String cVal;
				StringA vals;

				for(mi::Uint32 j=0;j<valA.GetSize();j++)
				{
				   cVal=valA[j];
				   this->GetExpectedValue(key, cVal);
				   // TODO: Write function to split string to array.
				   vals.PushBack(cVal);
				}

			    pCurrent->SetStringA(name,vals);
			}
			else
			{
				pCurrent->GetString(name, val);  
			    this->GetExpectedValue(key, val);                 
                pCurrent->SetString(name, val);
			}
        } 
    }

    return this->m_pAllInstances;
} 

void ExpectedContext::GetExpectedValue(const mi::String &key, mi::String &val)
{
    map<std::string, std::string>::const_iterator it = this->m_propertyFunction.find(key.Str()); 

    if (it == m_propertyFunction.end())
    {
        return;
    }   

    std::string methodName = it->second;   
    map<std::string, MODULE_TEST_CALLBACK>::const_iterator itMethod = s_fn.find(methodName);

    if (itMethod == s_fn.end())
    {
        return;
    }

    itMethod->second(val);
} 
