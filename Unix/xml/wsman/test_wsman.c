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

#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xml/xml.h>

const char* arg0;

int Inhale(const char* path, char** dataOut, size_t* sizeOut)
{
    FILE* is;
    char* data;
    size_t size;
    size_t n;

    /* Get file size */
    {
        struct stat st;

        if (stat(path, &st) != 0)
            return -1;

        size = st.st_size;
    }

    /* Open file */
    {
        is = fopen(path, "rb");

        if (!is)
            return -1;
    }

    /* Allocate buffer */
    {
        data = (char*)PAL_Malloc(size + 1);

        if (!data)
        {
            fclose(is);
            return -1;
        }

        *dataOut = data;
        *sizeOut = size;
    }

    /* Read file into buffer */
    while ((n = fread(data, 1, size, is)) != 0)
    {
        data += n;
        size -= n;
    }

    data[0] = '\0';
    fclose(is);

    return 0;
}

static int ParseSoapEnvelope(XML* xml)
{
    XML_Elem e;

    /* Ignore the processing instruction (if any) */
    {
        if (XML_Next(xml, &e) != 0)
        {
            XML_Raise(xml, "missing root element");
            return -1;
        }

        if (e.type != XML_INST)
        {
            if (XML_PutBack(xml, &e) != 0)
                return -1;
        }
    }

    /* Expect <s:Envelope> */
    if (XML_Expect(xml, &e, XML_START, "s:Envelope") != 0)
        return -1;

    /* Expect <s:Header> */
    if (XML_Expect(xml, &e, XML_START, "s:Header") != 0)
        return -1;

    for (;;)
    {
        if (XML_Next(xml, &e) != 0)
            return -1;

        if (e.type == XML_END && strcmp(e.data, "s:Header") == 0)
        {
            printf("DONE\n");
            break;
        }
        else if (e.type == XML_START && strcmp(e.data, "a:To") == 0)
        {
            if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                return -1;

            printf("a:To{%s}\n", e.data);

            if (XML_Expect(xml, &e, XML_END, "a:To") != 0)
                return -1;
        }
        else if (e.type == XML_START && strcmp(e.data, "w:ResourceURI") == 0)
        {
            if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                return -1;

            printf("w:ResourceURI{%s}\n", e.data);

            if (XML_Expect(xml, &e, XML_END, "w:ResourceURI") != 0)
                return -1;
        }
        else if (e.type == XML_START && strcmp(e.data, "a:ReplyTo") == 0)
        {
            if (XML_Expect(xml, &e, XML_START, "a:Address") != 0)
                return -1;

            if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                return -1;

            printf("a:Address{%s}\n", e.data);

            if (XML_Expect(xml, &e, XML_END, "a:Address") != 0)
                return -1;

            if (XML_Expect(xml, &e, XML_END, "a:ReplyTo") != 0)
                return -1;
        }
        else if (e.type == XML_START && strcmp(e.data, "a:Action") == 0)
        {
            if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                return -1;

            printf("a:Action{%s}\n", e.data);

            if (XML_Expect(xml, &e, XML_END, "a:Action") != 0)
                return -1;
        }
        else if (e.type == XML_START && strcmp(e.data, "a:MessageID") == 0)
        {
            if (XML_Expect(xml, &e, XML_CHARS, NULL) != 0)
                return -1;

            printf("a:MessageID{%s}\n", e.data);

            if (XML_Expect(xml, &e, XML_END, "a:MessageID") != 0)
                return -1;
        }
        else
        {
            if (XML_Skip(xml) != 0)
                return -1;
        }
    }

    /* Expect </s:Body> */
    if (XML_Expect(xml, &e, XML_START, "s:Body") != 0)
        return -1;

    if (XML_Skip(xml) != 0)
        return -1;

    /* Expect </s:Body> */
//    if (XML_Expect(xml, &e, XML_END, "s:Body") != 0)
//        return -1;

    /* Expect </s:Envelope> */
    if (XML_Expect(xml, &e, XML_END, "s:Envelope") != 0)
        return -1;

    return 0;
}

static void Parse(const char* path)
{
    XML xml;
    char* data;
    size_t size;

    if (Inhale(path, &data, &size) != 0)
    {
        fprintf(stderr, "%s: failed to open file: %s\n", arg0, path);
        exit(1);
    }

    XML_Init(&xml, &data[0]);

    XML_RegisterNameSpace(&xml, 's', 
        "http://www.w3.org/2003/05/soap-envelope");

    XML_RegisterNameSpace(&xml, 'a', 
        "http://schemas.xmlsoap.org/ws/2004/08/addressing");

    XML_RegisterNameSpace(&xml, 'w', 
        "http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd");

    ParseSoapEnvelope(&xml);

    if (xml.status)
    {
        XML_PutError(&xml);
        exit(1);
    }

#if 0
    while ((r = XML_Next(&xml, &e)) == 0)
    {
        XML_Elem_Dump(&e);
    }

    if (r != 1)
    {
        char msg[1024];
        XML_FormatError(&xml, msg, sizeof(msg));
        printf("%s:%s\n", path, msg);
        exit(1);
    }
#endif
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    /* Check arguments */
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s path\n", arg0);
        exit(1);
    }

    /* Parse the file */
    Parse(argv[1]);

    return 0;
}
