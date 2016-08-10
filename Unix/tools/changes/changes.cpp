/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <sys/stat.h>
#include <openssl/md5.h>

using namespace std;

const char* arg0;

// Key=path, Value=MD5:
typedef pair<string, string> Pair;
typedef map<string, string> Map;

static bool LoadFile(
    const char* path, 
    vector<char>& data)
{
    FILE* is;

    data.clear();

    /* Open the file */
    if (!(is = fopen(path, "rb")))
    {
        return false;
    }

    /* Read the file into the buffer */
    {
        size_t n;
        char buf[BUFSIZ];

        while ((n = fread(buf, 1, sizeof(buf), is)) > 0)
        {
            data.insert(data.end(), buf, buf + n);
        }

        if (ferror(is) != 0)
        {
            fclose(is);
            return -1;
        }
    }

    /* Close the file */
    fclose(is);

    return true;
}

static bool FindMD5(
    const char* path,
    string& md5)
{
    vector<char> data;

    if (!LoadFile(path, data))
        return false;

    {
        MD5_CTX ctx;
        MD5_Init(&ctx);
        MD5_Update(&ctx, &data[0], data.size());
        unsigned char digest[MD5_DIGEST_LENGTH];
        MD5_Final(digest, &ctx);

        for (size_t i = 0; i < MD5_DIGEST_LENGTH; i++)
        {
            char buf[3];
            sprintf(buf, "%02X", digest[i]);
            md5 += buf;
        }
    }

    return true;
}

static bool IsDir(const char* path)
{
    struct stat st;

    if (stat(path, &st) != 0)
        return false;

    return st.st_mode & S_IFDIR;
}

static void Scan(
    const string& root, 
    Map& files)
{
    vector<string> dirs;

    // Open directory:

    DIR* dir = opendir(root.c_str());

    if (!dir)
    {
        fprintf(stderr, "%s: warning: failed to open directory: %s\n", 
            arg0, root.c_str());
        return;
    }

    // Scan directory:

    struct dirent* ent;

    while ((ent = readdir(dir)))
    {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;

        string path = root + "/" + ent->d_name;

        struct stat st;

        if (stat(path.c_str(), &st) != 0)
        {
            fprintf(stderr, "%s: warning: failed to stat: %s\n", 
                arg0, path.c_str());
            continue;
        }

        if (st.st_mode & S_IFDIR)
        {
            dirs.push_back(path);

            string md5 = "00000000000000000000000000000000";
            files.insert(Pair(path, md5));
        }
        else
        {
            string md5;

            if (!FindMD5(path.c_str(), md5))
            {
                fprintf(stderr, "%s: failed to find MD5: %s\n",
                    arg0, path.c_str());
            }

            files.insert(Pair(path, md5));
        }
    }

    // Close directory:

    closedir(dir);

    // Scan child directories:

    for (size_t i = 0; i < dirs.size(); i++)
    {
        Scan(dirs[i], files);
    }
}

bool Exists(const char* path)
{
    struct stat st;

    if (stat(path, &st) == 0)
        return true;

    return false;
}

static bool WriteChangesFile(
    const char* path,
    const Map& files)
{
    FILE* os = fopen(path, "w");

    if (!os)
    {
        return false;
    }

    Map::const_iterator p = files.begin();
    Map::const_iterator end = files.end();

    while (p != end)
    {
        string path = (*p).first;
        string md5 = (*p).second;

        fprintf(os, "%s:%s\n", md5.c_str(), path.c_str());
        p++;
    }

    fclose(os);
    return true;
}

static bool LoadChangesFile(
    const char* path,
    Map& files)
{
    FILE* is = fopen(path, "r");

    if (!is)
        return false;

    char buf[4096];

    while (fgets(buf, sizeof(buf), is) != NULL)
    {
        char* end = buf + strlen(buf);

        while (end != buf && isspace(end[-1]))
            *--end = '\0';

        const char* colon = strchr(buf, ':');

        if (!colon)
        {
            fclose(is);
            return false;
        }

        string md5 = string(buf, colon - buf);
        string path = string(colon + 1);

#if 0
        printf("md5{%s}\n", md5.c_str());
        printf("path{%s}\n", path.c_str());
#endif

        files.insert(Pair(path, md5));
    }

    fclose(is);

    return true;
}

struct Change
{
    // 'A' (added), 'D' (deleted), or 'M' (modified)
    char type;
    string path;
};

void DiffChanges(
    const string& path,
    const Map& oldFiles,
    const Map& newFiles,
    vector<Change>& changes)
{
    // Identify changed file and new newFiles:
    {
        Map::const_iterator p = newFiles.begin();
        Map::const_iterator end = newFiles.end();

        for (; p != end; p++)
        {
            if ((*p).first == path)
                continue;

#if 0
            printf("PATH{%s}\n", (*p).first.c_str());
#endif

            Map::const_iterator pos = oldFiles.find((*p).first);

            if (pos == oldFiles.end())
            {
                Change tmp;
                tmp.type = 'A';
                tmp.path = (*p).first.c_str();
                changes.push_back(tmp);
            }
            else
            {
                string md5a = (*p).second;
                string md5b = (*pos).second;

                if (md5a != md5b)
                {
                    Change tmp;
                    tmp.type = 'M';
                    tmp.path = (*p).first.c_str();
                    changes.push_back(tmp);
                }
            }
        }
    }

    // Identify deleted newFiles:
    {
        Map::const_iterator p = oldFiles.begin();
        Map::const_iterator end = oldFiles.end();

        for (; p != end; p++)
        {
            if ((*p).first == path)
                continue;

#if 0
            printf("PATH{%s}\n", (*p).first.c_str());
#endif

            Map::const_iterator pos = newFiles.find((*p).first);

            if (pos == newFiles.end())
            {
                Change tmp;
                tmp.type = 'D';
                tmp.path = (*p).first.c_str();
                changes.push_back(tmp);
            }
        }
    }
}

string MakeDosPath(const string& path)
{
    string dospath = path;

    // Reverse the slashes:
    for (size_t i = 0; i < dospath.size(); i++)
    {
        if (dospath[i] == '/')
            dospath[i] = '\\';
    }

    // Remove the ".\" prefix:
    if (dospath.substr(0, 2) == ".\\")
        dospath = dospath.substr(2);

    return dospath;
}

void WritePatchFile(const vector<Change>& changes)
{
    const char PATH[] = "patch.bat";

    // Open patch file:

    FILE* os = fopen(PATH, "wb");

    if (!os)
    {
        fprintf(stderr, "%s: failed to open %s\n", arg0, PATH);
        exit(1);
    }

    // Write patch file:

    fprintf(os, "@echo off\r\n");

    fprintf(os, "if \"%%SDXROOT%%\" == \"\" (\r\n");
    fprintf(os, "    echo %%0: SDXROOT environment variable undefined\r\n");
    fprintf(os, "    goto done\r\n");
    fprintf(os, ")\r\n");
    fprintf(os, "\r\n");
    fprintf(os, "set WINOMIROOT=%%SDXROOT%%\\admin\\wmi\\winomi\r\n");
    fprintf(os, "set ROOT=%%CD%%\r\n");
    fprintf(os, "cd %%WINOMIROOT%%\r\n");
    fprintf(os, "\r\n");

    fprintf(os, "cd %%WINOMIROOT%%\r\n");
    fprintf(os, "if %%ERRORLEVEL%% NEQ 0 (\r\n");
    fprintf(os, "    echo %%0: No such directory: %%WINOMIROOT%%\\admin\\wmi\\winomi\r\n");
    fprintf(os, "    goto done\r\n");
    fprintf(os, ")\r\n");
    fprintf(os, "\r\n");

    // Modified files:
    for (size_t i = 0; i < changes.size(); i++)
    {
        string dospath = MakeDosPath(changes[i].path);

        if (changes[i].type == 'M')
        {
            fprintf(os, "sd edit %%WINOMIROOT%%\\%s\r\n", dospath.c_str());
            fprintf(os, "copy %%ROOT%%\\%s %%WINOMIROOT%%\\%s\r\n", 
                dospath.c_str(), dospath.c_str());
        }
    }

    fprintf(os, "\r\n");

    // Added files:
    for (size_t i = 0; i < changes.size(); i++)
    {
        string dospath = MakeDosPath(changes[i].path);

        if (dospath == PATH)
            continue;

        if (changes[i].type == 'A')
        {
            if (IsDir(changes[i].path.c_str()))
            {
                fprintf(os, "mkdir %%WINOMIROOT%%\\%s\r\n", dospath.c_str());
            }
            else
            {
                fprintf(os, "copy %%ROOT%%\\%s %%WINOMIROOT%%\\%s\r\n", 
                    dospath.c_str(), dospath.c_str());
                fprintf(os, "sd add %%WINOMIROOT%%\\%s\r\n", dospath.c_str());
            }
        }
    }

    fprintf(os, "\r\n");

    // Deleted files:
    for (size_t i = 0; i < changes.size(); i++)
    {
        string dospath = MakeDosPath(changes[i].path);

        if (changes[i].type == 'D')
        {
            fprintf(os, "sd delete %%WINOMIROOT%%\\%s\r\n", dospath.c_str());
        }
    }

    fprintf(os, "\r\n");

    // Done label:
    fprintf(os, ":done\r\n");

    // Close file:
    fclose(os);
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    if (argc != 1)
    {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(1);
    }

    Map newFiles;

    Scan(".", newFiles);

    const char PATH[] = "./.changes";

    if (Exists(PATH))
    {
        Map oldFiles;

        if (!LoadChangesFile(PATH, oldFiles))
        {
            fprintf(stderr, "%s: failed to load: %s\n", arg0, PATH);
            exit(1);
        }

        vector<Change> changes;
        DiffChanges(PATH, oldFiles, newFiles, changes);

        for (size_t i = 0; i < changes.size(); i++)
        {
            const Change& tmp = changes[i];
            printf("%c %s\n", tmp.type, tmp.path.c_str());
        }

        WritePatchFile(changes);
    }
    else
    {
        if (!WriteChangesFile(PATH, newFiles))
        {
            fprintf(stderr, "%s: failed to write: %s\n", arg0, PATH);
            exit(1);
        }

        printf("Created %s\n", PATH);
    }

    return 0;
}
