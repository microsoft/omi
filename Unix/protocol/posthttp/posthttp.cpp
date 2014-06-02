#include <sock/sock.h>
#include <protocol/protocol.h>
#include <pal/format.h>
#include <pal/file.h>
#include <string>
#include <vector>

using namespace std;

Sock Connect(unsigned short port)
{
    Sock_Start();

    Addr addr;

    if (Addr_Init(&addr, "127.0.0.1", port) != MI_RESULT_OK)
    {
        return INVALID_SOCK;
    }

    Sock sock;

    if (Sock_Create(&sock) != MI_RESULT_OK)
    {
        return INVALID_SOCK;
    }
 
    if (Sock_Connect(sock, &addr) != MI_RESULT_OK)
    {
        return INVALID_SOCK;
    }

    return sock;
}

bool PostHTTP(
    Sock sock,
    const string& content,
    string& responseHeaders,
    string& responseContent)
{
    // Format the HTTP headers:

    char headers[4096];
    size_t size;
    {
        const char FMT[] = 
            "POST /wsman HTTP/1.1\r\n" \
            "Content-Length: %d\r\n"\
            "Connection: Keep-Alive\r\n"\
            "Content-Type: application/soap+xml;charset=UTF-8\r\n"\
            "Authorization:    Basic \t \tcm9vdDpPcHNNZ3IyMDA3UjI=\t \r\n"\
            "\r\n";

        size = (size_t)Snprintf(headers, sizeof(headers), FMT,
            (int)content.size());
    }

    // Write the request to the server:
    {
        size_t sent;
        MI_Result r = Sock_Write(sock, headers, size, &sent);

        if (r != MI_RESULT_OK)
        {
            printf("RETURN{%u}\n", __LINE__);
            return false;
        }

        if (size != sent)
        {
            printf("RETURN{%u}\n", __LINE__);
            return false;
        }
    }

    // Write body if present:

    if (content.size())
    {
        size_t n;
        MI_Result r = Sock_Write(sock, content.c_str(), content.size(), &n);

        if (r != MI_RESULT_OK)
        {
            printf("RETURN{%u}\n", __LINE__);
            return false;
        }

        if (n != content.size())
        {
            printf("RETURN{%u}\n", __LINE__);
            return false;
        }
    }

    // Read headers (and possibly a few bytes of the buffer:

    responseHeaders.resize(16 * 1024);
    size_t n = 0;
    size_t pos_crcr;

    for (;;)
    {
        size_t m;

        MI_Result r = Sock_Read(
            sock, 
            &responseHeaders[0], 
            responseHeaders.size() - n, 
            &m);

        if (r != MI_RESULT_OK)
        {
            printf("RETURN{%u}\n", __LINE__);
            return false;
        }

        n += m;

        pos_crcr = responseHeaders.find("\r\n\r\n");

        if (pos_crcr != string::npos)
        {
            responseHeaders.resize(n);
            break;
        }
    }

    // Get partial content:

    responseContent = responseHeaders.substr(pos_crcr + 4);
    responseHeaders = responseHeaders.substr(0, pos_crcr);

    const char CONTENT_LENGTH[] = "Content-Length:";

    string::size_type pos_cl = responseHeaders.find(CONTENT_LENGTH);
    size_t contentLength = 0;

    if (string::npos != pos_cl)
    {
        contentLength = atol(
            responseHeaders.c_str() + pos_cl + sizeof(CONTENT_LENGTH)-1);
    }

    while (responseContent.size() < contentLength)
    {
        size_t n = responseContent.size();
        responseContent.resize(contentLength);
        size_t m;

        MI_Result r = Sock_Read(
            sock, 
            &responseContent[0] + n, 
            contentLength - n, 
            &m);

        if (r != MI_RESULT_OK)
        {
            printf("RETURN{%u}\n", __LINE__);
            return false;
        }

        responseContent.resize(n + m);
    }

    return true;
}

static bool Inhale(const char* path, vector<char>& data)
{
    FILE* is = File_Open(path, "r");

    if (!is)
        return false;

    size_t n;
    char buf[4096];

    while ((n = fread(buf, 1, sizeof(buf), is)) != 0)
    {
        data.insert(data.end(), buf, buf + n);
    }

    data.push_back('\0');

    fclose(is);

    return true;
}

int main(int argc, char** argv)
{
    // Connect to the server:

    Sock sock = Connect(CONFIG_HTTPPORT);

    if (sock == INVALID_SOCK)
    {
        fprintf(stderr, "%s: Connect() failed\n", argv[0]);
        exit(1);
    }

    // Read request into memory:

    string content;
    {
        vector<char> data;

        if (!Inhale(argv[1], data))
        {
            fprintf(stderr, "%s: Inhale() failed\n", argv[0]);
            exit(1);
        }

        data.push_back('\0');
        content = &data[0];
    }

    // Post the request:

    string responseHeaders;
    string responseContent;

    bool flag = PostHTTP(sock, content, responseHeaders, responseContent);

    if (!flag)
    {
        fprintf(stderr, "%s: PostHTTP() failed\n", argv[0]);
        exit(1);
    }

    // Dump output:

    printf("responseHeaders{%s}\n", responseHeaders.c_str());

    printf("responseContent{%s}\n", responseContent.c_str());

    return 0;
}
