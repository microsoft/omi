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

#include "xmlcxx.h"
#include <xml/xml.h>
#include <base/buf.h>
#include <vector>
#include <memory.h>
#include <cctype>

using namespace std;

//==============================================================================
//
// class XMLElement
//
//==============================================================================

XMLCXX_BEGIN

class XMLElementRep
{
public:
    XML_Elem elem;
};

XMLElement::XMLElement()
{
    _rep = new XMLElementRep;
    Clear();
}

XMLElement::XMLElement(const XMLElement& x)
{
    _rep = new XMLElementRep;
    memcpy(_rep, x._rep, sizeof(XMLElementRep));
}

XMLElement::~XMLElement()
{
    delete _rep;
}

XMLElement& XMLElement::operator=(const XMLElement& x)
{
    if (&x != this)
        memcpy(_rep, x._rep, sizeof(XMLElementRep));

    return *this;
}

void XMLElement::Clear()
{
    // Element will have XMLElement::NONE type.
    memset(_rep, 0, sizeof(XMLElementRep));
}

XMLElement::Type XMLElement::GetType() const
{
    switch (_rep->elem.type)
    {
        case XML_NONE:
            return NONE;
        case XML_START:
            return START;
        case XML_END:
            return END;
        case XML_CHARS:
            return CHARS;
        case XML_INSTRUCTION:
            return INSTRUCTION;
        case XML_COMMENT:
            return COMMENT;
        default:
            return NONE;
    }
}

const char* XMLElement::GetData() const
{
    return _rep->elem.data ? _rep->elem.data : "";
}

size_t XMLElement::GetAttributeCount() const
{
    return _rep->elem.attrsSize;
}

const char* XMLElement::GetAttributeName(size_t index) const
{
    if (index < _rep->elem.attrsSize)
        return _rep->elem.attrs[index].name;
    else
        return NULL;
}

const char* XMLElement::GetAttributeValue(size_t index) const
{
    if (index < _rep->elem.attrsSize)
        return _rep->elem.attrs[index].value;
    else
        return NULL;
}

const char* XMLElement::FindAttributeValue(const char* name) const
{
    for (size_t i = 0; i < _rep->elem.attrsSize; i++)
    {
        if (strcmp(_rep->elem.attrs[i].name, name) == 0)
            return _rep->elem.attrs[i].value;
    }

    // Not found!
    return NULL;
}

void XMLElement::Dump() const
{
    XML_Elem_Dump(&_rep->elem);
}

XMLCXX_END

//==============================================================================
//
// class XMLReader
//
//==============================================================================

XMLCXX_BEGIN

class XMLReaderRep
{
public:
    vector<char> text;
    XML xml;

    XMLReaderRep()
    {
        text.push_back('\0');
        XML_Init(&xml);
    }

    void SetText(const char* text_)
    {
        text.clear();
        text.insert(text.end(), text_, text_ + strlen(text_));
        text.push_back('\0');
        XML_SetText(&xml, &text[0]);
    }
};

XMLReader::XMLReader()
{
    _rep = new XMLReaderRep;
}

XMLReader::XMLReader(const char* text)
{
    _rep = new XMLReaderRep;
    _rep->SetText(text);
}

XMLReader::~XMLReader()
{
    delete _rep;
}

size_t XMLReader::GetLineNumber() const
{
    return _rep->xml.line;
}

void XMLReader::SetText(const char* text)
{
    _rep->SetText(text);
}

bool XMLReader::GetNext(XMLElement& elem)
{
    return XML_Next(&_rep->xml, &elem._rep->elem) == 0 ? true : false;
}

bool XMLReader::Skip()
{
    return XML_Skip(&_rep->xml) == 0 ? true : false;
}

bool XMLReader::PutBack(XMLElement& elem)
{
    return XML_PutBack(&_rep->xml, &elem._rep->elem) == 0 ? true : false;
}

void XMLReader::Dump() const
{
    XML_Dump(&_rep->xml);
}

string XMLReader::GetErrorMessage() const
{
    char buf[512];
    XML_FormatError(&_rep->xml, buf, sizeof(buf));
    return string(buf);
}

void XMLReader::GetErrorMessage(char* buffer, size_t size)
{
    XML_FormatError(&_rep->xml, buffer, size);
}

bool XMLReader::GetError() const
{
    return _rep->xml.status == -1;
}

bool XMLReader::RegisterNameSpace(char id, const char* uri)
{
    return XML_RegisterNameSpace(&_rep->xml, id, uri) == 0 ? true : false;
}

XMLCXX_END

//==============================================================================
//
// class XMLWriter
//
//==============================================================================

XMLCXX_BEGIN

class XMLWriterRep
{
public:
    Buf buf;
    bool enableLineSeparators;

    XMLWriterRep() : enableLineSeparators(false)
    {
        Buf_Init(&buf, 4096);
    }

    ~XMLWriterRep()
    {
        Buf_Destroy(&buf);
    }
};

static const struct 
{
    const char* str;
    size_t len;
}
_encode[256] =
{
    { "&#0;", sizeof("&#0;")-1 },
    { "&#1;", sizeof("&#1;")-1 },
    { "&#2;", sizeof("&#2;")-1 },
    { "&#3;", sizeof("&#3;")-1 },
    { "&#4;", sizeof("&#4;")-1 },
    { "&#5;", sizeof("&#5;")-1 },
    { "&#6;", sizeof("&#6;")-1 },
    { "&#7;", sizeof("&#7;")-1 },
    { "&#8;", sizeof("&#8;")-1 },
    { "&#9;", sizeof("&#9;")-1 },
    { "&#10;", sizeof("&#10;")-1 },
    { "&#11;", sizeof("&#11;")-1 },
    { "&#12;", sizeof("&#12;")-1 },
    { "&#13;", sizeof("&#13;")-1 },
    { "&#14;", sizeof("&#14;")-1 },
    { "&#15;", sizeof("&#15;")-1 },
    { "&#16;", sizeof("&#16;")-1 },
    { "&#17;", sizeof("&#17;")-1 },
    { "&#18;", sizeof("&#18;")-1 },
    { "&#19;", sizeof("&#19;")-1 },
    { "&#20;", sizeof("&#20;")-1 },
    { "&#21;", sizeof("&#21;")-1 },
    { "&#22;", sizeof("&#22;")-1 },
    { "&#23;", sizeof("&#23;")-1 },
    { "&#24;", sizeof("&#24;")-1 },
    { "&#25;", sizeof("&#25;")-1 },
    { "&#26;", sizeof("&#26;")-1 },
    { "&#27;", sizeof("&#27;")-1 },
    { "&#28;", sizeof("&#28;")-1 },
    { "&#29;", sizeof("&#29;")-1 },
    { "&#30;", sizeof("&#30;")-1 },
    { "&#31;", sizeof("&#31;")-1 },
    { " ", sizeof(" ")-1 },
    { "!", sizeof("!")-1 },
    { "&quot;", sizeof("&quot;")-1 },
    { "#", sizeof("#")-1 },
    { "$", sizeof("$")-1 },
    { "%", sizeof("%")-1 },
    { "&amp;", sizeof("&amp;")-1 },
    { "&apos;", sizeof("&apos;")-1 },
    { "(", sizeof("(")-1 },
    { ")", sizeof(")")-1 },
    { "*", sizeof("*")-1 },
    { "+", sizeof("+")-1 },
    { ",", sizeof(",")-1 },
    { "-", sizeof("-")-1 },
    { ".", sizeof(".")-1 },
    { "/", sizeof("/")-1 },
    { "0", sizeof("0")-1 },
    { "1", sizeof("1")-1 },
    { "2", sizeof("2")-1 },
    { "3", sizeof("3")-1 },
    { "4", sizeof("4")-1 },
    { "5", sizeof("5")-1 },
    { "6", sizeof("6")-1 },
    { "7", sizeof("7")-1 },
    { "8", sizeof("8")-1 },
    { "9", sizeof("9")-1 },
    { ":", sizeof(":")-1 },
    { ";", sizeof(";")-1 },
    { "&lt;", sizeof("&lt;")-1 },
    { "=", sizeof("=")-1 },
    { "&gt;", sizeof("&gt;")-1 },
    { "?", sizeof("?")-1 },
    { "@", sizeof("@")-1 },
    { "A", sizeof("A")-1 },
    { "B", sizeof("B")-1 },
    { "C", sizeof("C")-1 },
    { "D", sizeof("D")-1 },
    { "E", sizeof("E")-1 },
    { "F", sizeof("F")-1 },
    { "G", sizeof("G")-1 },
    { "H", sizeof("H")-1 },
    { "I", sizeof("I")-1 },
    { "J", sizeof("J")-1 },
    { "K", sizeof("K")-1 },
    { "L", sizeof("L")-1 },
    { "M", sizeof("M")-1 },
    { "N", sizeof("N")-1 },
    { "O", sizeof("O")-1 },
    { "P", sizeof("P")-1 },
    { "Q", sizeof("Q")-1 },
    { "R", sizeof("R")-1 },
    { "S", sizeof("S")-1 },
    { "T", sizeof("T")-1 },
    { "U", sizeof("U")-1 },
    { "V", sizeof("V")-1 },
    { "W", sizeof("W")-1 },
    { "X", sizeof("X")-1 },
    { "Y", sizeof("Y")-1 },
    { "Z", sizeof("Z")-1 },
    { "[", sizeof("[")-1 },
    { "\\", sizeof("\\")-1 },
    { "]", sizeof("]")-1 },
    { "^", sizeof("^")-1 },
    { "_", sizeof("_")-1 },
    { "`", sizeof("`")-1 },
    { "a", sizeof("a")-1 },
    { "b", sizeof("b")-1 },
    { "c", sizeof("c")-1 },
    { "d", sizeof("d")-1 },
    { "e", sizeof("e")-1 },
    { "f", sizeof("f")-1 },
    { "g", sizeof("g")-1 },
    { "h", sizeof("h")-1 },
    { "i", sizeof("i")-1 },
    { "j", sizeof("j")-1 },
    { "k", sizeof("k")-1 },
    { "l", sizeof("l")-1 },
    { "m", sizeof("m")-1 },
    { "n", sizeof("n")-1 },
    { "o", sizeof("o")-1 },
    { "p", sizeof("p")-1 },
    { "q", sizeof("q")-1 },
    { "r", sizeof("r")-1 },
    { "s", sizeof("s")-1 },
    { "t", sizeof("t")-1 },
    { "u", sizeof("u")-1 },
    { "v", sizeof("v")-1 },
    { "w", sizeof("w")-1 },
    { "x", sizeof("x")-1 },
    { "y", sizeof("y")-1 },
    { "z", sizeof("z")-1 },
    { "{", sizeof("{")-1 },
    { "|", sizeof("|")-1 },
    { "}", sizeof("}")-1 },
    { "~", sizeof("~")-1 },
    { "&#127;", sizeof("&#127;")-1 },
    { "&#128;", sizeof("&#128;")-1 },
    { "&#129;", sizeof("&#129;")-1 },
    { "&#130;", sizeof("&#130;")-1 },
    { "&#131;", sizeof("&#131;")-1 },
    { "&#132;", sizeof("&#132;")-1 },
    { "&#133;", sizeof("&#133;")-1 },
    { "&#134;", sizeof("&#134;")-1 },
    { "&#135;", sizeof("&#135;")-1 },
    { "&#136;", sizeof("&#136;")-1 },
    { "&#137;", sizeof("&#137;")-1 },
    { "&#138;", sizeof("&#138;")-1 },
    { "&#139;", sizeof("&#139;")-1 },
    { "&#140;", sizeof("&#140;")-1 },
    { "&#141;", sizeof("&#141;")-1 },
    { "&#142;", sizeof("&#142;")-1 },
    { "&#143;", sizeof("&#143;")-1 },
    { "&#144;", sizeof("&#144;")-1 },
    { "&#145;", sizeof("&#145;")-1 },
    { "&#146;", sizeof("&#146;")-1 },
    { "&#147;", sizeof("&#147;")-1 },
    { "&#148;", sizeof("&#148;")-1 },
    { "&#149;", sizeof("&#149;")-1 },
    { "&#150;", sizeof("&#150;")-1 },
    { "&#151;", sizeof("&#151;")-1 },
    { "&#152;", sizeof("&#152;")-1 },
    { "&#153;", sizeof("&#153;")-1 },
    { "&#154;", sizeof("&#154;")-1 },
    { "&#155;", sizeof("&#155;")-1 },
    { "&#156;", sizeof("&#156;")-1 },
    { "&#157;", sizeof("&#157;")-1 },
    { "&#158;", sizeof("&#158;")-1 },
    { "&#159;", sizeof("&#159;")-1 },
    { "&#160;", sizeof("&#160;")-1 },
    { "&#161;", sizeof("&#161;")-1 },
    { "&#162;", sizeof("&#162;")-1 },
    { "&#163;", sizeof("&#163;")-1 },
    { "&#164;", sizeof("&#164;")-1 },
    { "&#165;", sizeof("&#165;")-1 },
    { "&#166;", sizeof("&#166;")-1 },
    { "&#167;", sizeof("&#167;")-1 },
    { "&#168;", sizeof("&#168;")-1 },
    { "&#169;", sizeof("&#169;")-1 },
    { "&#170;", sizeof("&#170;")-1 },
    { "&#171;", sizeof("&#171;")-1 },
    { "&#172;", sizeof("&#172;")-1 },
    { "&#173;", sizeof("&#173;")-1 },
    { "&#174;", sizeof("&#174;")-1 },
    { "&#175;", sizeof("&#175;")-1 },
    { "&#176;", sizeof("&#176;")-1 },
    { "&#177;", sizeof("&#177;")-1 },
    { "&#178;", sizeof("&#178;")-1 },
    { "&#179;", sizeof("&#179;")-1 },
    { "&#180;", sizeof("&#180;")-1 },
    { "&#181;", sizeof("&#181;")-1 },
    { "&#182;", sizeof("&#182;")-1 },
    { "&#183;", sizeof("&#183;")-1 },
    { "&#184;", sizeof("&#184;")-1 },
    { "&#185;", sizeof("&#185;")-1 },
    { "&#186;", sizeof("&#186;")-1 },
    { "&#187;", sizeof("&#187;")-1 },
    { "&#188;", sizeof("&#188;")-1 },
    { "&#189;", sizeof("&#189;")-1 },
    { "&#190;", sizeof("&#190;")-1 },
    { "&#191;", sizeof("&#191;")-1 },
    { "&#192;", sizeof("&#192;")-1 },
    { "&#193;", sizeof("&#193;")-1 },
    { "&#194;", sizeof("&#194;")-1 },
    { "&#195;", sizeof("&#195;")-1 },
    { "&#196;", sizeof("&#196;")-1 },
    { "&#197;", sizeof("&#197;")-1 },
    { "&#198;", sizeof("&#198;")-1 },
    { "&#199;", sizeof("&#199;")-1 },
    { "&#200;", sizeof("&#200;")-1 },
    { "&#201;", sizeof("&#201;")-1 },
    { "&#202;", sizeof("&#202;")-1 },
    { "&#203;", sizeof("&#203;")-1 },
    { "&#204;", sizeof("&#204;")-1 },
    { "&#205;", sizeof("&#205;")-1 },
    { "&#206;", sizeof("&#206;")-1 },
    { "&#207;", sizeof("&#207;")-1 },
    { "&#208;", sizeof("&#208;")-1 },
    { "&#209;", sizeof("&#209;")-1 },
    { "&#210;", sizeof("&#210;")-1 },
    { "&#211;", sizeof("&#211;")-1 },
    { "&#212;", sizeof("&#212;")-1 },
    { "&#213;", sizeof("&#213;")-1 },
    { "&#214;", sizeof("&#214;")-1 },
    { "&#215;", sizeof("&#215;")-1 },
    { "&#216;", sizeof("&#216;")-1 },
    { "&#217;", sizeof("&#217;")-1 },
    { "&#218;", sizeof("&#218;")-1 },
    { "&#219;", sizeof("&#219;")-1 },
    { "&#220;", sizeof("&#220;")-1 },
    { "&#221;", sizeof("&#221;")-1 },
    { "&#222;", sizeof("&#222;")-1 },
    { "&#223;", sizeof("&#223;")-1 },
    { "&#224;", sizeof("&#224;")-1 },
    { "&#225;", sizeof("&#225;")-1 },
    { "&#226;", sizeof("&#226;")-1 },
    { "&#227;", sizeof("&#227;")-1 },
    { "&#228;", sizeof("&#228;")-1 },
    { "&#229;", sizeof("&#229;")-1 },
    { "&#230;", sizeof("&#230;")-1 },
    { "&#231;", sizeof("&#231;")-1 },
    { "&#232;", sizeof("&#232;")-1 },
    { "&#233;", sizeof("&#233;")-1 },
    { "&#234;", sizeof("&#234;")-1 },
    { "&#235;", sizeof("&#235;")-1 },
    { "&#236;", sizeof("&#236;")-1 },
    { "&#237;", sizeof("&#237;")-1 },
    { "&#238;", sizeof("&#238;")-1 },
    { "&#239;", sizeof("&#239;")-1 },
    { "&#240;", sizeof("&#240;")-1 },
    { "&#241;", sizeof("&#241;")-1 },
    { "&#242;", sizeof("&#242;")-1 },
    { "&#243;", sizeof("&#243;")-1 },
    { "&#244;", sizeof("&#244;")-1 },
    { "&#245;", sizeof("&#245;")-1 },
    { "&#246;", sizeof("&#246;")-1 },
    { "&#247;", sizeof("&#247;")-1 },
    { "&#248;", sizeof("&#248;")-1 },
    { "&#249;", sizeof("&#249;")-1 },
    { "&#250;", sizeof("&#250;")-1 },
    { "&#251;", sizeof("&#251;")-1 },
    { "&#252;", sizeof("&#252;")-1 },
    { "&#253;", sizeof("&#253;")-1 },
    { "&#254;", sizeof("&#254;")-1 },
    { "&#255;", sizeof("&#255;")-1 },
};


/* [A-Za-z_] */
static inline bool _IsFirst(char c)
{
    if (isalpha(c) || c == '_')
        return true;

    return false;
    //return (_nameChar[(unsigned int)c] & 2) ? true : false;
}

/* [A-Za-z0-9_-.:] */
static inline bool _IsInner(char c)
{
    if (isalpha(c) || isdigit(c) || c=='_' || c=='-' || c=='.' || c==':')
        return true;

    return false;
}

static bool _ValidIdentifier(const char* p)
{
    if (!_IsFirst(*p))
        return false;

    p++;

    while (*p)
    {
        if (!_IsInner(*p))
            return false;

        p++;
    }

    return true;
}

static void _PutRaw(XMLWriterRep* rep, const char* str)
{
    size_t len = strlen(str);

    if (len)
        Buf_App(&rep->buf, str, len);
}

static void _PutChars(XMLWriterRep* _rep, const char* str)
{
    const unsigned char* p = reinterpret_cast<const unsigned char*>(str);

    while (*p)
    {
        Buf_App(&_rep->buf, _encode[*p].str, _encode[*p].len);
        p++;
    }
}

//
// Helper function to put start tag, empty tag, or processing instruction.
//
// The 'type' parameter is one of these:
//     's' -- start tag
//     'e' -- empty tag
//     'p' -- processing instruction.
//
bool _PutTag(
    XMLWriterRep* _rep,
    const char* tagName,
    const std::vector<XMLAttr>& attrs,
    char type)
{
    if (!_ValidIdentifier(tagName))
        return false;

    if (type == 'p')
        _PutRaw(_rep, "<?");
    else
        _PutRaw(_rep, "<");

    _PutRaw(_rep, tagName);

    for (size_t i = 0; i < attrs.size(); i++)
    {
        const XMLAttr& a = attrs[i];

        if (!_ValidIdentifier(a.name.c_str()))
            return false;

        _PutRaw(_rep, " ");
        _PutRaw(_rep, a.name.c_str());
        _PutRaw(_rep, "=\"");
        _PutChars(_rep, a.value.c_str());
        _PutRaw(_rep, "\"");
    }

    if (type == 'p')
        _PutRaw(_rep, "?>");
    else if (type == 'e')
        _PutRaw(_rep, "/>");
    else
        _PutRaw(_rep, ">");

    return true;
}

XMLWriter::XMLWriter()
{
    _rep = new XMLWriterRep();
}

XMLWriter::~XMLWriter()
{
    delete _rep;
}

std::string XMLWriter::GetText() const
{
    return string(
        reinterpret_cast<const char*>(_rep->buf.data), _rep->buf.size);
}

void XMLWriter::EnableLineSeparators()
{
    _rep->enableLineSeparators = true;
}

void XMLWriter::DisableLineSeparators()
{
    _rep->enableLineSeparators = false;
}

bool XMLWriter::PutStartTag(
    const char* tagName,
    const std::vector<XMLAttr>& attrs)
{
    if (!_PutTag(_rep, tagName, attrs, 's'))
        return false;

    if (_rep->enableLineSeparators)
        PutLineSeparator();

    return true;
}

bool XMLWriter::PutStartTag(const char* tagName)
{
    vector<XMLAttr> attrs;

    if (!_PutTag(_rep, tagName, attrs, 's'))
        return false;

    if (_rep->enableLineSeparators)
        PutLineSeparator();

    return true;
}

bool XMLWriter::PutEmptyTag(
    const char* tagName,
    const std::vector<XMLAttr>& attrs)
{
    if (!_PutTag(_rep, tagName, attrs, 'e'))
        return false;

    if (_rep->enableLineSeparators)
        PutLineSeparator();

    return true;
}

bool XMLWriter::PutProcessingInstruction(
    const char* tagName,
    const std::vector<XMLAttr>& attrs)
{
    if (!_PutTag(_rep, tagName, attrs, 'p'))
        return false;

    if (_rep->enableLineSeparators)
        PutLineSeparator();

    return true;
}

bool XMLWriter::PutEndTag(const char* tagName)
{
    if (!_ValidIdentifier(tagName))
        return false;

    _PutRaw(_rep, "</");
    _PutRaw(_rep, tagName);
    _PutRaw(_rep, ">");

    if (_rep->enableLineSeparators)
        PutLineSeparator();

    return true;
}

void XMLWriter::PutCharacterData(const char* str)
{
    _PutChars(_rep, str);

    if (_rep->enableLineSeparators)
        PutLineSeparator();
}

void XMLWriter::PutComment(const char* str)
{
    _PutRaw(_rep, "<!--");
    _PutChars(_rep, str);
    _PutRaw(_rep, "-->");

    if (_rep->enableLineSeparators)
        PutLineSeparator();
}

void XMLWriter::PutCDATA(const char* str)
{
    _PutRaw(_rep, "<![CDATA[");
    _PutRaw(_rep, str);
    _PutRaw(_rep, "]]>");

    if (_rep->enableLineSeparators)
        PutLineSeparator();
}

void XMLWriter::PutLineSeparator()
{
    _PutRaw(_rep, "\r\n");
}

XMLCXX_END
