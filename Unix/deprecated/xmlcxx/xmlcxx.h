/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#ifndef _xmlcxx_xmlcxx_h
#define _xmlcxx_xmlcxx_h

#include <cstddef>
#include <string>
#include <vector>

//==============================================================================
//
// XMLCXX_EXPORT
// XMLCXX_IMPORT
// XMLCXX_LINKAGE
//
//==============================================================================

#if defined(_MSC_VER)
# define XMLCXX_EXPORT __declspec(dllexport)
# define XMLCXX_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
# define XMLCXX_EXPORT __attribute__((visibility("default")))
# define XMLCXX_IMPORT /* empty */
#elif defined(sun)
# define XMLCXX_EXPORT __global 
# define XMLCXX_IMPORT /* empty */
#else
# define XMLCXX_EXPORT 
# define XMLCXX_IMPORT
#endif

#ifdef BUILDING_XMLCXX
#  define XMLCXX_LINKAGE XMLCXX_EXPORT
#else
#  define XMLCXX_LINKAGE XMLCXX_IMPORT
#endif

//==============================================================================
//
// XMLCXX_BEGIN
// XMLCXX_END
//
//==============================================================================

#define XMLCXX_BEGIN namespace xmlcxx {
#define XMLCXX_END }

//==============================================================================
//
// class XMLElement
//
//==============================================================================

XMLCXX_BEGIN

class XMLCXX_LINKAGE XMLElement
{
public:

    enum Type
    {
        NONE, /* Uninitialized */
        START, /* XML start tag */
        END, /* XML end tag */
        INSTRUCTION, /* XML processing instruction */
        CHARS, /* XML character data */
        COMMENT /* XML comment */
    };

    // Default constructor (sets type to NONE).
    XMLElement();

    // Copy constructor.
    XMLElement(const XMLElement& x);

    // Destructor.
    ~XMLElement();

    // Assignment operator constructor.
    XMLElement& operator=(const XMLElement& x);

    // Clear the element (setting type to NONE).
    void Clear();

    // Get the type of this element.
    Type GetType() const;

    // Get data for the current element, which represents either XML character 
    // data or an XML tag name.
    const char* GetData() const;

    // Get the number of attrs (applies to START elements only).
    size_t GetAttributeCount() const;

    // Get the name of the attribute at the given index (applies to START
    // elements only).
    const char* GetAttributeName(size_t index) const;

    // Get the value of the attribute at the given index (applies to START
    // elements only).
    const char* GetAttributeValue(size_t index) const;

    // Find attribute with this name. Return null if not found (applies to 
    // START elements only).
    const char* FindAttributeValue(const char* name) const;

    // Dump the element to standard output.
    void Dump() const;

private:

    class XMLElementRep* _rep;

    friend class XMLReader;
};

XMLCXX_END

//==============================================================================
//
// class XMLReader
//
//     This class incrementally parses an XML document. The example below
//     illustrates the general approach.
//
//         const char* text;
//         ...
//         XMLReader reader(text);
//         XMLElement element;
//
//         while (reader.GetNext(element))
//         {
//             ...
//         }
//
//     The constructor makes a copy of the XML text passed as the sole
//     parameter. XMLReader::GetNext() gets the next XML element, whose
//     type (given by XMLElement::GetType()) is one of the following:
//
//          XMLElement::START - XML start tag
//          XMLElement::END - XML end tag
//          XMLElement::INSTRUCTION - XML processing instruction
//          XMLElement::CHARS - XML character data
//          XMLElement::COMMENT - an XML comment
//
//     The XMLElement class provides method for obtaining more information 
//     about an element. For example, XMLElement provides methods for 
//     examining the attrs of a start tag.
//
//     A false return value from XMLReader::GetNext() indicates either the
//     end of XML input or a parsing error. To detect an error, call
//     XMLReader::GetError(). For example:
//
//         if (reader.GetError())
//         {
//             std::string msg = reader.GetErrorMessage();
//             ...
//         }
//
//     This parser handles XML namespaces (the prefixes borne by tag names,
//     which are terminated by a ':' character). By default, the parser
//     returns the actual namespace prefix encountered during parsing. Consider
//     this fragment.
//
//         <ws:a xmlns:ws='http://schemas.dmtf.org/wbem/ws/1/ws.xsd'>
//             <ws:a>
//                 ...
//            </ws:a>
//        </ws:a>
//
//     In this example, XMLReader::GetNext() returns tags whose names
//     include the "ws" prefix. But by registering the URI above,
//     this prefix may be mapped to a predictable single character prefix
//     (note that there is no guarantee otherwise that the prefixes will be
//     predictable; one client may send "ws" whereas another may send "wsman").
//     The following example registers a namespace URI:
//
//         reader.RegisterNameSpace(
//             'w', "http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd");
//
//     Subsequently, XMLReader::GetNext() returns tags whose corresponding
//     names bear the "w" prefix.
//
//==============================================================================

XMLCXX_BEGIN

class XMLCXX_LINKAGE XMLReader
{
public:

    // Default constructor.
    XMLReader();

    // Construct reader with this text.
    XMLReader(const char* text);

    // Destructor.
    ~XMLReader();

    // Get the current line number of the XML text.
    size_t GetLineNumber() const;

    // Set the XML text to be parsed.
    void SetText(const char* text);

    // Read the next XML element.
    bool GetNext(XMLElement& elem);

    // Skip the current element (and any child elements at this level).
    bool Skip();

    // Put back the last element obtained from GetNext().
    bool PutBack(XMLElement& elem);

    // Dump internal state information about the parser to standard output.
    void Dump() const;

    // Write the current error (if any) to standard error.
    void PutError() const;

    // Return true if parser is in error state.
    bool GetError() const;

    // Get error message if in error state. Else return false.
    std::string GetErrorMessage() const;

    // Get error message if in error state. Else return false.
    void GetErrorMessage(char* buffer, size_t size);

    // Register an XML namespace, causing the original namespace prefix
    // to be mapped to the single character given by the 'id' parameter.
    bool RegisterNameSpace(char id, const char* uri);

private:

    XMLReader(const XMLReader&);

    XMLReader& operator=(const XMLReader&);

    class XMLReaderRep* _rep;
};

XMLCXX_END

//==============================================================================
//
// class XMLWriter
//
//     This class is used to build XML documents. It provides methods for
//     creating all kinds of XML document elements. Consider the following
//     XML document.
//
//         <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
//         <p:Animal Type="Dog" Height="44">
//         My name is Fido!
//         </p:Animal>
//
//     The following code fragment builds the document above.
//
//         XMLWriter w;
//
//         w.EnableLineSeparators();
//
//         w.PutProcessingInstruction("xml", MakeAttrs("version", "1.0", 
//             "encoding", "UTF-8", "standalone", "yes"));
//
//         w.PutStartTag(
//            "p:Animal", MakeAttrs("Type", "Dog", "Height", "44"));
//
//         w.PutCharacterData("My name is Fido!");
//
//         w.PutEndTag(
//            "p:Animal", MakeAttrs("Type", "Dog", "Height", "44"));
//
//         std::string document = w.GetText();
//
//         printf("document{%s}", document.c_str());
//
//     This class takes care of translating special characters to XML entity
//     references. This fragment:
//
//         w.PutCharacterData("99 < 100");
//
//     Inserts the following text.
//
//         99 &lt; 100
//
//     XML Attributes are represented by the XMLAttr class. You may build 
//     vectors of these as follows:
//
//         std::vector<XMLAttr> attrs;
//         attrs.push_back(XMLAttr("Type", "Dog");
//         attrs.push_back(XMLAttr("Height", "44");
//
//     Or you may use the MakeAttrs() functions as follows.
//
//         MakeAttrs("Type", "Dog", "Height", "44")
//
//     There are version of MakeAttrs() for creating vectors with 0 to 8
//     attributes.
//
//==============================================================================

XMLCXX_BEGIN

class XMLAttr
{
public:

    XMLAttr(const std::string& name_, const std::string& value_) :
        name(name_), value(value_)
    {
    }

    std::string name;
    std::string value;
};

class XMLCXX_LINKAGE XMLWriter
{
public:

    // Default constructor.
    XMLWriter();

    // Destructor.
    ~XMLWriter();

    // Retrieve the output text.
    std::string GetText() const;

    // Enable automatic insertion of line separators after each element.
    void EnableLineSeparators();

    // Disable automatic insertion of line separators after each element.
    void DisableLineSeparators();

    // Append an XML start tag with the given name and attrs. Return 
    // false if on of the identifiers (tag name or attribute name) is invalid.
    bool PutStartTag(
        const char* tagName,
        const std::vector<XMLAttr>& attrs);

    // Same as PutStartTag() above but takes no attributes.
    bool PutStartTag(const char* tagName);

    // Append an XML empty tag with the given name and attrs. Return 
    // false if on of the identifiers (tag name or attribute name) is invalid.
    bool PutEmptyTag(
        const char* tagName,
        const std::vector<XMLAttr>& attrs);

    // Append a processing instruction. Example:
    //     <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
    bool PutProcessingInstruction(
        const char* tagName,
        const std::vector<XMLAttr>& attrs);

    // Append an XML end tag.
    bool PutEndTag(const char* tagName);

    // Append XML character data (escape special characters).
    void PutCharacterData(const char* str);

    // Append an XML comment of the form "<!-- ... -->". Escape special
    // characters.
    void PutComment(const char* str);

    // Append an XML CDATA section of the form "<![CDATA[...]]>". Escape
    // special characters.
    void PutCDATA(const char* str);

    // Append a line separator (\r\n).
    void PutLineSeparator();

private:

    XMLWriter(const XMLWriter&);

    XMLWriter& operator=(const XMLWriter&);

    struct XMLWriterRep* _rep;
};

inline std::vector<XMLAttr> MakeAttrs(
    const std::string& name1,
    const std::string& value1)
{
    std::vector<XMLAttr> attrs;
    attrs.reserve(1);
    attrs.push_back(XMLAttr(name1, value1));
    return attrs;
}

inline std::vector<XMLAttr> MakeAttrs(
    const std::string& name1,
    const std::string& value1,
    const std::string& name2,
    const std::string& value2)
{
    std::vector<XMLAttr> attrs;
    attrs.reserve(2);
    attrs.push_back(XMLAttr(name1, value1));
    attrs.push_back(XMLAttr(name2, value2));
    return attrs;
}

inline std::vector<XMLAttr> MakeAttrs(
    const std::string& name1,
    const std::string& value1,
    const std::string& name2,
    const std::string& value2,
    const std::string& name3,
    const std::string& value3)
{
    std::vector<XMLAttr> attrs;
    attrs.reserve(3);
    attrs.push_back(XMLAttr(name1, value1));
    attrs.push_back(XMLAttr(name2, value2));
    attrs.push_back(XMLAttr(name3, value3));
    return attrs;
}

inline std::vector<XMLAttr> MakeAttrs(
    const std::string& name1,
    const std::string& value1,
    const std::string& name2,
    const std::string& value2,
    const std::string& name3,
    const std::string& value3,
    const std::string& name4,
    const std::string& value4)
{
    std::vector<XMLAttr> attrs;
    attrs.reserve(4);
    attrs.push_back(XMLAttr(name1, value1));
    attrs.push_back(XMLAttr(name2, value2));
    attrs.push_back(XMLAttr(name3, value3));
    attrs.push_back(XMLAttr(name4, value4));
    return attrs;
}

inline std::vector<XMLAttr> MakeAttrs(
    const std::string& name1,
    const std::string& value1,
    const std::string& name2,
    const std::string& value2,
    const std::string& name3,
    const std::string& value3,
    const std::string& name4,
    const std::string& value4,
    const std::string& name5,
    const std::string& value5)
{
    std::vector<XMLAttr> attrs;
    attrs.reserve(5);
    attrs.push_back(XMLAttr(name1, value1));
    attrs.push_back(XMLAttr(name2, value2));
    attrs.push_back(XMLAttr(name3, value3));
    attrs.push_back(XMLAttr(name4, value4));
    attrs.push_back(XMLAttr(name5, value5));
    return attrs;
}

inline std::vector<XMLAttr> MakeAttrs(
    const std::string& name1,
    const std::string& value1,
    const std::string& name2,
    const std::string& value2,
    const std::string& name3,
    const std::string& value3,
    const std::string& name4,
    const std::string& value4,
    const std::string& name5,
    const std::string& value5,
    const std::string& name6,
    const std::string& value6)
{
    std::vector<XMLAttr> attrs;
    attrs.reserve(6);
    attrs.push_back(XMLAttr(name1, value1));
    attrs.push_back(XMLAttr(name2, value2));
    attrs.push_back(XMLAttr(name3, value3));
    attrs.push_back(XMLAttr(name4, value4));
    attrs.push_back(XMLAttr(name5, value5));
    attrs.push_back(XMLAttr(name6, value6));
    return attrs;
}

inline std::vector<XMLAttr> MakeAttrs(
    const std::string& name1,
    const std::string& value1,
    const std::string& name2,
    const std::string& value2,
    const std::string& name3,
    const std::string& value3,
    const std::string& name4,
    const std::string& value4,
    const std::string& name5,
    const std::string& value5,
    const std::string& name6,
    const std::string& value6,
    const std::string& name7,
    const std::string& value7)
{
    std::vector<XMLAttr> attrs;
    attrs.reserve(7);
    attrs.push_back(XMLAttr(name1, value1));
    attrs.push_back(XMLAttr(name2, value2));
    attrs.push_back(XMLAttr(name3, value3));
    attrs.push_back(XMLAttr(name4, value4));
    attrs.push_back(XMLAttr(name5, value5));
    attrs.push_back(XMLAttr(name6, value6));
    attrs.push_back(XMLAttr(name7, value7));
    return attrs;
}

inline std::vector<XMLAttr> MakeAttrs(
    const std::string& name1,
    const std::string& value1,
    const std::string& name2,
    const std::string& value2,
    const std::string& name3,
    const std::string& value3,
    const std::string& name4,
    const std::string& value4,
    const std::string& name5,
    const std::string& value5,
    const std::string& name6,
    const std::string& value6,
    const std::string& name7,
    const std::string& value7,
    const std::string& name8,
    const std::string& value8)
{
    std::vector<XMLAttr> attrs;
    attrs.reserve(8);
    attrs.push_back(XMLAttr(name1, value1));
    attrs.push_back(XMLAttr(name2, value2));
    attrs.push_back(XMLAttr(name3, value3));
    attrs.push_back(XMLAttr(name4, value4));
    attrs.push_back(XMLAttr(name5, value5));
    attrs.push_back(XMLAttr(name6, value6));
    attrs.push_back(XMLAttr(name7, value7));
    attrs.push_back(XMLAttr(name8, value8));
    return attrs;
}

XMLCXX_END

#endif /* _xmlcxx_xmlcxx_h */
