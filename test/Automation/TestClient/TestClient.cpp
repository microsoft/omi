#include <climits>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include<string>
#include <omiclient/client.h>
#include <base/args.h>
#include <base/result.h>
#include<wql/wql.h>
#include <base/strings.h>
#include <base/paths.h>
#include <base/conf.h>
#include <base/env.h>
#include <base/getopt.h>
#include <base/io.h>
#include <base/time.h>

#include "TestClient.h"
#include "ExpectedContext.h"


#if (MI_CHAR_TYPE == 1)
#define STRF "%s"
#else
#define STRF "%S"
#endif

using namespace mi;

const char* arg0;

enum boolean
{
	False = 0,
	True = 1
};

typedef Array<boolean> booleanA;

struct Options
{
	bool help;
	bool quiet;
	bool suppressResults;
	bool trace;
	bool deep;
	int repeat;
	String assocClass;
	String resultClass;
	String role;
	String resultRole;
	String user;
	String password;
	Uint64 timeOut;
	unsigned int httpport;
	unsigned int httpsport;
	bool nulls;
	String querylang;
	String queryexpr;

	Options()
	{
		Clear();
	}

	void Clear()
	{
		help = false;
		quiet = false;
		suppressResults = false;
		trace = false;
		deep = false;
		repeat = 1;
		assocClass.Clear();
		resultClass.Clear();
		role.Clear();
		resultRole.Clear();
		user.Clear();
		password.Clear();
		timeOut = 90 * 1000 * 1000;
		httpport = CONFIG_HTTPPORT;
		httpsport = CONFIG_HTTPSPORT;
		nulls = false;
		querylang.Clear();
		queryexpr.Clear();
	}
};

static Options opts;

static FILE* sout = stdout;
static FILE* serr = stderr;

PRINTF_FORMAT(1, 2)
	static void err(const char* fmt, ...)
{
	fprintf(serr, "%s: ", arg0);

	va_list ap;
	va_start(ap, fmt);
	vfprintf(serr, fmt, ap);
	va_end(ap);

	fputc('\n', serr);
}

String MakeString(const char* str)
{
	String s;
	while (*str)
		s += MI_Char(*str++);

	return s;
}

bool StringToBoolean(const mi::String& isKey)
{
    return isKey.Equal(T("True"));
}

// Replaces all occurrences of a specified string in the source string, with another specified string.  
mi::String Replace(const mi::String& source, mi::String sub, const mi::String rep)
{
    if (source.GetSize() == 0 || sub.GetSize() == 0)
    {
        return source;
    }

    const MI_Char* pSource = source.Str(); 
    const MI_Char* pSub = sub.Str(); 
    const MI_Char* pRep = rep.Str();

    const MI_Char *pSourceTmp,*pSubTmp; 
    String result;


    // Go through every char of source string.
    while ('\0' != *pSource)
    {
        pSourceTmp = pSource;
        pSubTmp = pSub;

        while(*pSourceTmp==*pSubTmp && '\0'!=*pSubTmp && '\0'!=*pSourceTmp)
        {
            pSourceTmp++;pSubTmp++;
        }

        // Found matched string, else copy source char to result string. 
        if('\0' == *pSubTmp)
        { 
            pSubTmp = pRep;

            // Append replaced string to result string.
            while('\0' != *pSubTmp)
            {
                result += *pSubTmp++;
            }

            // if source string match sub string, Start compare from next char of source string.
            // pc1 is end of sub string
            pSourceTmp--;
            pSource=pSourceTmp;
        }
        else
        {
            result += *pSource;
        }

        // Move to next char.
        pSource++; 
    } 

    return result;
}

mi::Type StringToType(const mi::String& dataType)
{
    mi::Type typeValue = MI_STRING;

    if (dataType.Equal(T("STRING")))
    {
        typeValue = MI_STRING;
    }
    else if (dataType.Equal(T("REAL32"))) 
    {
        typeValue = MI_REAL32;
    }
    else if (dataType.Equal(T("REAL64"))) 
    {
        typeValue = MI_REAL64;
    }
    else if (dataType.Equal(T("SINT16"))) 
    {
        typeValue = MI_SINT16;
    }
    else if (dataType.Equal(T("SINT8"))) 
    {
        typeValue = MI_SINT8;
    }
    else if (dataType.Equal(T("SINT32"))) 
    {
        typeValue = MI_SINT32;
    }
    else if (dataType.Equal(T("SINT64"))) 
    {
        typeValue = MI_SINT64;
    }
    else if (dataType.Equal(T("BOOLEAN"))) 
    {
        typeValue = MI_BOOLEAN;
    } 
    else if (dataType.Equal(T("CHAR16"))) 
    {
        typeValue = MI_CHAR16;
    }    
    else if (dataType.Equal(T("UINT8"))) 
    {
        typeValue = MI_UINT8;
    }
    else if (dataType.Equal(T("UINT16"))) 
    {
        typeValue = MI_UINT16;
    }
    else if (dataType.Equal(T("UINT32"))) 
    {
        typeValue = MI_UINT32;
    }
    else if (dataType.Equal(T("UINT64"))) 
    {
        typeValue = MI_UINT64;
    }
    else if (dataType.Equal(T("DATETIME")))
    {
        typeValue = MI_DATETIME;
    }

    return typeValue;
}

static std::string ZToStr(const MI_Char* str)
{
    std::string r;

    while (*str)
        r += char(*str++);

    return r;
}

static int FindConfigFile(char path[MAX_PATH_SIZE])
{
	/* Look in current directory */
	{
		Strlcpy(path, "./.omiclirc", MAX_PATH_SIZE);

		if (access(path, R_OK) == 0)
			return 0;
	}

	/* Look in HOME directory */
	char* home = Dupenv("HOME");
	if (home)
	{
		Strlcpy(path, home, MAX_PATH_SIZE);
		Strlcat(path, "/.omiclirc", MAX_PATH_SIZE);

		if (access(path, R_OK) == 0)
		{
			free(home);
			return 0;
		}
		free(home);
	}

	/* Look in system config directory */
	{
		Strlcpy(path, GetPath(ID_SYSCONFDIR), MAX_PATH_SIZE);
		Strlcat(path, "/omicli.conf", MAX_PATH_SIZE);

		if (access(path, R_OK) == 0)
			return 0;
	}

	/* Not found */
	return -1;
}

static int GetConfigFileOptions()
{
	char path[MAX_PATH_SIZE];
	Conf* conf;

	/* Form the configuration file path (silently ignore if not found) */
	if (FindConfigFile(path) != 0)
		return 0;

	/* Open the configuration file */
	conf = Conf_Open(path);
	if (!conf)
	{
		err("failed to open configuration file: %s", path);
		return 1;
	}

	/* For each key=value pair in configuration file */
	for (;;)
	{
		const char* key;
		const char* value;
		int r = Conf_Read(conf, &key, &value);

		if (r == -1)
		{
			err("%s: %s\n", path, Conf_Error(conf));
			return 1;
		}

		if (r == 1)
			break;

		if (strcmp(key, "httpport") == 0)
		{
			char* end;
			unsigned long x = Strtoul(value, &end, 10);

			if (*end != '\0' || x > USHRT_MAX)
			{
				err("%s(%u): invalid value for '%s': %s", path, 
					Conf_Line(conf), key, value);
				return 1;
			}

			opts.httpport = (unsigned short)x;
		}
		else if (strcmp(key, "httpsport") == 0)
		{
			char* end;
			unsigned long x = Strtoul(value, &end, 10);

			if (*end != '\0' || x > USHRT_MAX)
			{
				err("%s(%u): invalid value for '%s': %s", path, 
					Conf_Line(conf), key, value);
				return 1;
			}

			opts.httpsport = (unsigned short)x;
		}
		else if (strcmp(key, "trace") == 0)
		{
			if (Strcasecmp(value, "true") == 0)
			{
				opts.trace = MI_TRUE;
			}
			else if (Strcasecmp(value, "false") == 0)
			{
				opts.trace = MI_FALSE;
			}
			else
			{
				err("%s(%u): invalid value for '%s': %s", path, 
					Conf_Line(conf), key, value);
				return 1;
			}
		}
		else if (IsNickname(key))
		{
			if (SetPathFromNickname(key, value) != 0)
			{
				err("SetPathFromNickname() failed");
				return 1;
			}
		}
		else
		{
			err("%s(%u): unknown key: %s", path, Conf_Line(conf), key);
			return 1;
		}
	}

	/* Close configuration file */
	Conf_Close(conf);
	return 0;
}

static void GetCommandLineDestDirOption(
    int* argc_,
    const char* argv[])
{
    int argc = *argc_;
    int i;
    const char* destdir = NULL;

    for (i = 1; i < argc; )
    {
        if (strcmp(argv[i], "--destdir") == 0)
        {
            if (i + 1 == argc)
                err("missing argument for --destdir option");

            destdir = argv[i+1];
            memmove((char*)&argv[i], (char*)&argv[i+2], 
                sizeof(char*) * (argc-i-1));
            argc -= 2;
        }
        else if (strncmp(argv[i], "--destdir=", 10) == 0)
        {
            destdir = argv[i] + 10;
            memmove((char*)&argv[i], (char*)&argv[i+1], 
                sizeof(char*) * (argc-i));

            argc -= 1;
        }
        else
            i++;
    }

    if (destdir)
    {
        if (SetPath(ID_DESTDIR, destdir) != 0)
            err("failed to set destdir");
    }

    *argc_ = argc;
}

static int GetCommandLineOptions(
	int& argc,
	const char* argv[],
	Options& options)
{
	GetOptState state = GETOPTSTATE_INITIALIZER;
	const char* supportedOptions[] =
	{
		"-h",
		"-q",
		"-t",
		"-s",
		"-deep",
		"-n",
		"-R:",
		"-ac:",
		"-rc:",
		"-r:",
		"-rr:",
		"-rc:",
		"-u:",
		"-p:",
		"--prefix:",
		"--libdir:",
		"--bindir:",
		"--localstatedir:",
		"--sysconfdir:",
		"--providerdir:",
		"--certsdir:",
		"--rundir:",
		"--logdir:",
		"--pidfile:",
		"--logfile:",
		"--registerdir:",
		"--socketfile:",
		"--pemfile:",
		"--keyfile:",
		"--agentprogram:",
		"--serverprogram:",
		"--stdout:",
		"--stderr:",
		 "--querylang:",
		 "--queryexpr:",
		NULL,
	};

	for (;;)
	{
		int r = GetOpt(&argc, argv, supportedOptions, &state);

		if (r == 1)
			break;

		if (r == -1)
		{
			fprintf(serr, "error: %s\n", state.err);
			fprintf(serr, "Try -h for help\n");
			return 1;
		}

		if (strcmp(state.opt, "-h") == 0)
		{
			options.help = true;
		}
		else if (strcmp(state.opt, "-q") == 0)
		{
			options.quiet = true;
		}
		else if (strcmp(state.opt, "-t") == 0)
		{
			options.trace = true;
		}
		else if (strcmp(state.opt, "-s") == 0)
		{
			options.suppressResults = true;
		}
		else if (strcmp(state.opt, "-deep") == 0)
		{
			options.deep = true;
		}
		else if (strcmp(state.opt, "-n") == 0)
		{
			options.nulls = true;
		}
		else if (strcmp(state.opt, "-R") == 0)
		{
			options.repeat = atoi(state.arg);

			if (options.repeat <= 0)
			{
				err("bad value for -R: %s", state.arg);
				return 1;
			}
		}
		else if (strcmp(state.opt, "-ac") == 0)
		{
			options.assocClass = MakeString(state.arg);
		}
		else if (strcmp(state.opt, "-rc") == 0)
		{
			options.resultClass = MakeString(state.arg);
		}
		else if (strcmp(state.opt, "-r") == 0)
		{
			options.role = MakeString(state.arg);
		}
		else if (strcmp(state.opt, "-rr") == 0)
		{
			options.resultRole = MakeString(state.arg);
		}
		else if (strcmp(state.opt, "-u") == 0)
		{
			options.user = MakeString(state.arg);
		}
		else if (strcmp(state.opt, "-p") == 0)
		{
			options.password = MakeString(state.arg);
		}
		else if (strcmp(state.opt, "--stdout") == 0)
		{
			FILE* os = Fopen(state.arg, "wb");

			if (!os)
				err("failed to open: %s", state.arg);

			sout = os;
		}
		else if (strcmp(state.opt, "--stderr") == 0)
		{
			FILE* os = Fopen(state.arg, "wb");

			if (!os)
				err("failed to open: %s", state.arg);

			serr = os;
		}
		else if (strcmp(state.opt, "--querylang") == 0)
		{
			options.querylang = MakeString(state.arg);
		}
		else if (strcmp(state.opt, "--queryexpr") == 0)
		{
			options.queryexpr = MakeString(state.arg);
		}
		else if (strncmp(state.opt, "--", 2) == 0 && IsNickname(state.opt+2))
		{
			if (SetPathFromNickname(state.opt+2, state.arg) != 0)
				err("SetPathFromNickname() failed");
		}
	}

	return 0;
}

const char USAGE[] = "\
					 Usage: %s [OPTIONS] COMMAND ...\n\
					 \n\
					 This tool sends requests to the CIM server.\n\
					 \n\
					 OPTIONS:\n\
					 -h                  Print this help message.\n\
					 -q                  Operate quietly.\n\
					 -t                  Enable diagnostic tracing.\n\
					 -R N                Repeat command N times.\n\
					 -deep               Use deep inheritance (see 'ei' command).\n\
					 -ac CLASSNAME       Association class (see 'a' and 'r' commands).\n\
					 -rc CLASSNAME       Result class (see 'a' command).\n\
					 -r ROLE             Role (see 'a' and 'r' commands).\n\
					 -rr ROLE            Result role (see 'a' command).\n\
					 -n                  Show null properties.\n\
					 -u USERNAME         Username.\n\
					 -p PASSWORD         User's password.\n\
					 -id			Send identify request.\n\
					 --socketfile PATH   Talk to the server server whose socket file resides\n\
					 at the location given by the path argument.\n\
					 --httpport		Connect on this port instead of default.\n\
					 --httpsport		Connect on this secure port instead of default.\n\
					 \n\
					 COMMANDS:\n\
					 xeis XMLPATH\n\
					 XML enumerate instances with shell. Collect expected value according to PropertiesMaps.xml\n\
					 noop\n\
					 Perform a no-op operation.\n\
					 gi NAMESPACE INSTANCENAME\n\
					 Peform a CIM [g]et [i]nstance operation.\n\
					 ci NAMESPACE NEWINSTANCE\n\
					 Peform a CIM [c]create [i]nstance operation.\n\
					 mi NAMESPACE MODIFIEDINSTANCE\n\
					 Peform a CIM [m]odify [i]nstance operation.\n\
					 di NAMESPACE INSTANCENAME\n\
					 Peform a CIM [d]elete [i]nstance operation.\n\
					 ei [-deep] NAMESPACE CLASSNAME\n\
					 Peform a CIM [e]numerate [i]nstances operation.\n\
					 eic NAMESPACE CLASSNAME,CLASSNAME,...\n\
					 Peform a CIM [e]numerate multiple [i]nstances accoding to calss collection operation.\n\
					 iv NAMESPACE INSTANCENAME METHODNAME PARAMETERS\n\
					 Peform a CIM extrinisic method [i]nvocation operation.\n\
					 a [-ac -rc -r -rr ] NAMESPACE INSTANCENAME\n\
					 Perform a CIM [a]ssociator instances operation.\n\
					 r [-ac -r] NAMESPACE INSTANCENAME (references)\n\
					 Perform a CIM [r]eference instances operation.\n\
					 enc INSTANCE\n\
					 Attempt to encode and print the given instance representation.\n\
					 wql NAMESPACE WQLQUERY\n\
					 Peform a WQL query operation.\n\
					 \n";

// ATTN: support arrays.
static bool ArgsToInstance(
	const char**& p, 
	const char** end, 
	DInstance::MetaType metaType,
	bool key,
	DInstance& instanceOut)
{
	if (p == end)
		return false;

	// Consume opening brace:
	if (strcmp(*p++, "{") != 0)
		return false;

	if (p == end)
		return false;

	// Call the 'empty' constructor so that we can use placement operator.
	DInstance instance;

	if (metaType == DInstance::METHOD)
	{
		instance = DInstance(T("Parameters"), DInstance::METHOD);
	}
	else
	{
		instance = DInstance(MakeString(*p++), DInstance::CLASS);

		if (p == end)
			return false;
	}

	// Consume name/value pairs:
	for (;;)
	{
		if (strcmp(*p, "}") == 0)
		{
			p++;
			break;
		}

		// Get name:
		String name = MakeString(*p++);

		if (p == end)
			return false;


		// Get value:
		if (strcmp(*p, "{") == 0)
		{
			int nesting = 1;
			const char** q = p;
			q++;

			// Find closing brace:
			while (*q)
			{
				if (strcmp(*q, "{") == 0)
					nesting++;
				else if (strcmp(*q, "}") == 0)
					nesting--;

				q++;

				if (nesting == 0)
					break;
			}

			// Handle missing closing brace:
			if (q == end)
				return false;

			// Recursively call to obtain reference or embedded instance.
			DInstance tmpInstance;
			if (!ArgsToInstance(p, q, DInstance::CLASS, key, tmpInstance))
			{
				return false;
			}

			if (!instance.AddInstance(name, tmpInstance, false, key))
				return false;
		}
		else if (strcmp(*p, "[") == 0)
		{
			Array<String> array;
			p++;

			// Find closing brace:
			while (*p && strcmp(*p, "]") != 0)
			{
				array.PushBack(MakeString(*p++));
			}

			// Handle missing closing brace:
			if (p == end)
				return false;

			if (!instance.AddStringA(name, array, false, key))
				return false;

			p++;
		}
		else
		{
			// Get value:
			String value = MakeString(*p++);

			// Add property:
			if (!instance.AddString(name, value, false, key))
				return false;

			if (p == end)
				break;
		}
	}

	instanceOut = instance;
	return true;
}

static int NoOp(Client& client, int argc, const char* argv[])
{
	MI_UNUSED(argv);

	if (argc != 2)
	{
		fprintf(serr, "Usage: %s noop\n\n", arg0);
		return 1;
	}

	if (!client.NoOp(opts.timeOut))
	{
		err("noop request failed");
		return 1;
	}

	if (!opts.quiet)
		fprintf(sout, "got noop response\n");

	return 0;
}

static void ConvertDataTypeToString(const MI_Type& type, String& ret)
{
	switch(type)
	{
	case MI_BOOLEAN:
		// Implict Convert, use String(const MI_Char*) construct
		ret=T("BOOLEAN");
		break;
	case MI_UINT8:
		ret=T("UINT8");
		break;
	case MI_SINT8:
		ret=T("SINT8");
		break;
	case MI_UINT16:
		ret=T("UINT16");
		break;
	case MI_SINT16:
		ret=T("SINT16");
		break;
	case MI_UINT32:
		ret=T("UINT32");
		break;
	case MI_SINT32:
		ret=T("SINT32");
		break;
	case MI_UINT64:
		ret=T("UINT64");
		break;
	case MI_SINT64:
		ret=T("SINT64");
		break;
	case MI_REAL32:
		ret=T("REAL32");
		break;
	case MI_REAL64:
		ret=T("REAL64");
		break;
	case MI_CHAR16:
		ret=T("CHAR16");
		break;
	case MI_DATETIME:
		ret=T("DATETIME");
		break;
	case MI_STRING:
		ret=T("STRING");
		break;
	case MI_REFERENCE:
		ret=T("REFERENCE");
		break;
	case MI_INSTANCE:
		ret=T("INSTANCE");
		break;
	case MI_BOOLEANA:
		ret=T("BOOLEANA");
		break;
	case MI_UINT8A:
		ret=T("UINT8A");
		break;
	case MI_SINT8A:
		ret=T("SINT8A");
		break;
	case MI_UINT16A:
		ret=T("UINT16A");
		break;
	case MI_SINT16A:
		ret=T("SINT16A");
		break;
	case MI_UINT32A:
		ret=T("UINT32A");
		break;
	case MI_SINT32A:
		ret=T("SINT32A");
		break;
	case MI_UINT64A:
		ret=T("UINT64A");
		break;
	case MI_SINT64A:
		ret=T("SINT64A");
		break;
	case MI_REAL32A:
		ret=T("REAL32A");
		break;
	case MI_REAL64A:
		ret=T("REAL64A");
		break;
	case MI_CHAR16A:
		ret=T("CHAR16A");
		break;
	case MI_DATETIMEA:
		ret=T("DATETIMEA");
		break;
	case MI_STRINGA:
		ret=T("STRINGA");
		break;
	case MI_REFERENCEA:
		ret=T("REFERENCEA");
		break;
	case MI_INSTANCEA:
		ret=T("INSTANCEA");
		break;
	default:
		ret=T("UNKNOWN");
	}
}

template <class FieldType>
static void PrintFieldDetailInfo(const FieldType& field, const String& fieldName, const String& fieldTypeToString, const bool& isFieldKey,const bool& fieldNull,  const MI_Char* format=NULL)
{
	if(!fieldNull)
	{
		Fzprintf(sout, T("<CimProperty Name=\"%s\" PropertyType=\"%s\" IsKey=\"%s\">"), fieldName.Str(), fieldTypeToString.Str(), isFieldKey ? T("true") : T("false"));
		Fzprintf(sout, format, field);
		Fzprintf(sout, T("</CimProperty>\n"));
	}
}

template <>
void PrintFieldDetailInfo<boolean>(const boolean& field, const String& fieldName, const String& fieldTypeToString, const bool& isFieldKey,const bool& fieldNull, const MI_Char* format)
{
	if(!fieldNull)
	{
		Fzprintf(sout, T("<CimProperty Name=\"%s\" PropertyType=\"%s\" IsKey=\"%s\">"), fieldName.Str(), fieldTypeToString.Str(), isFieldKey ? T("true") : T("false"));
		Fzprintf(sout, format, field ? T("TRUE") : T("FALSE"));
		Fzprintf(sout, T("</CimProperty>\n"));
	}
}

template <>
void PrintFieldDetailInfo<String>(const String& field, const String& fieldName, const String& fieldTypeToString, const bool& isFieldKey,const bool& fieldNull, const MI_Char* format)
{	
	if(!fieldNull)
	{
		Fzprintf(sout, T("<CimProperty Name=\"%s\" PropertyType=\"%s\" IsKey=\"%s\">"), fieldName.Str(), fieldTypeToString.Str(), isFieldKey ? T("true") : T("false"));
        
		// Replace all special char in the text.
		mi::String text = Replace(field, "<", "&lt;");
		text = Replace(text, ">", "&gt;");
		text = Replace(text, "&", "&amp;");
		text = Replace(text, "\'", "&apos;");
		text = Replace(text, "\"", "&quot;");

		Fzprintf(sout, format, text.Str());
		Fzprintf(sout, T("</CimProperty>\n"));
	}
}

template <>
void PrintFieldDetailInfo<Datetime>(const Datetime& field, const String& fieldName, const String& fieldTypeToString, const bool& isFieldKey,const bool& fieldNull, const MI_Char* format)
{
	if(!fieldNull)
	{
		if(format!=NULL)
		{
			err("We don't need format parameter when we print Datetime Type");
			return;
		}

		Fzprintf(sout, T("<CimProperty Name=\"%s\" PropertyType=\"%s\" IsKey=\"%s\">"), fieldName.Str(), fieldTypeToString.Str(), isFieldKey ? T("true") : T("false"));
		field.Print();
		Fzprintf(sout, T("</CimProperty>\n"));
	}
}

static MI_Result PrintSingleInstanceToXml(const DInstance& inst, bool isCallBack);

template <>
void PrintFieldDetailInfo<DInstance>(const DInstance& field, const String& fieldName, const String& fieldTypeToString, const bool& isFieldKey,const bool& fieldNull, const MI_Char* format)
{
	if(!fieldNull)
	{
		if(format!=NULL)
		{
			err("We don't need format parameter when we print Instance or Reference Type");
			return;
		}

		Fzprintf(sout, T("<CimProperty Name=\"%s\" PropertyType=\"%s\" IsKey=\"%s\" IsRef=\"%s\" IsArray=\"false\">\n"), fieldName.Str(),fieldTypeToString.Str(), isFieldKey ? T("true") : T("false"),fieldTypeToString==T("REFERENCE")? T("true"):T("false"));
		PrintSingleInstanceToXml(field,false);
		Fzprintf(sout, T("</CimProperty>\n"));
	}
}

template <class ElementType>
static void PrintFieldArrayDetailInfo(const Array<ElementType>& fieldArray, const String& fieldName, const String& fieldTypeToString, const bool& isFieldKey,const bool& fieldNull, const MI_Char* format=NULL)
{
	if(!fieldNull)
	{
		Fzprintf(sout, T("<CimProperty Name=\"%s\" PropertyType=\"%s\" IsKey=\"%s\">"), fieldName.Str(), fieldTypeToString.Str(), isFieldKey ? T("true") : T("false"));
		MI_Uint32 arrayCount=fieldArray.GetSize();
		for(Uint32 i=0;i<arrayCount;i++)
		{
			Fzprintf(sout, T("<ArrayElement>"));
			Fzprintf(sout, format, fieldArray[i]);
			Fzprintf(sout, T("</ArrayElement>"));
		}

		Fzprintf(sout, T("</CimProperty>\n"));
	}
}

template <>
void PrintFieldArrayDetailInfo<boolean>(const Array<boolean>& fieldArray, const String& fieldName, const String& fieldTypeToString, const bool& isFieldKey,const bool& fieldNull, const MI_Char* format)
{	
	if(!fieldNull)
	{
		Fzprintf(sout, T("<CimProperty Name=\"%s\" PropertyType=\"%s\" IsKey=\"%s\">"), fieldName.Str(), fieldTypeToString.Str(), isFieldKey ? T("true") : T("false"));
		MI_Uint32 arrayCount=fieldArray.GetSize();
		for(Uint32 i=0;i<arrayCount;i++)
		{
			Fzprintf(sout, T("<ArrayElement>"));
			Fzprintf(sout, format, fieldArray[i] ? "TRUE" : "FALSE");
			Fzprintf(sout, T("</ArrayElement>"));
		}

		Fzprintf(sout, T("</CimProperty>\n"));
	}
}

template <>
void PrintFieldArrayDetailInfo<String>(const Array<String>& fieldArray, const String& fieldName, const String& fieldTypeToString, const bool& isFieldKey, const bool& fieldNull,const MI_Char* format)
{
	if(!fieldNull)
	{
		Fzprintf(sout, T("<CimProperty Name=\"%s\" PropertyType=\"%s\" IsKey=\"%s\">"), fieldName.Str(), fieldTypeToString.Str(), isFieldKey ? T("true") : T("false"));
		MI_Uint32 arrayCount=fieldArray.GetSize();
		for(Uint32 i=0;i<arrayCount;i++)
		{
			Fzprintf(sout, T("<ArrayElement>"));
			Fzprintf(sout, format, fieldArray[i].Str());
			Fzprintf(sout, T("</ArrayElement>"));	
		}

		Fzprintf(sout, T("</CimProperty>\n"));
	}
}

template <>
void PrintFieldArrayDetailInfo<Datetime>(const Array<Datetime>& fieldArray, const String& fieldName, const String& fieldTypeToString, const bool& isFieldKey,const bool& fieldNull, const MI_Char* format)
{
	if(!fieldNull)
	{
		if(format!=NULL)
		{
			err("We don't need format parameter when we print Datetime Type");
			return;
		}
		Fzprintf(sout, T("<CimProperty Name=\"%s\" PropertyType=\"%s\" IsKey=\"%s\">"), fieldName.Str(), fieldTypeToString.Str(), isFieldKey ? "true" : "false");
		MI_Uint32 arrayCount=fieldArray.GetSize();
		for(Uint32 i=0;i<arrayCount;i++)
		{
			Fzprintf(sout, T("<ArrayElement>"));
			fieldArray[i].Print();
			Fzprintf(sout, T("</ArrayElement>"));
		}

		Fzprintf(sout, T("</CimProperty>\n"));
	}
}

template <>
void PrintFieldArrayDetailInfo<DInstance>(const Array<DInstance>& fieldArray, const String& fieldName, const String& fieldTypeToString, const bool& isFieldKey,const bool& fieldNull, const MI_Char* format)
{
	if(!fieldNull)
	{
		if(format!=NULL)
		{
			err("We don't need format parameter when we print DInstance Type");
			return;
		}
		Fzprintf(sout, T("<CimProperty Name=\"%s\" PropertyType=\"%s\" IsKey=\"%s\">"), fieldName.Str(), fieldTypeToString.Str(), isFieldKey ? "true" : "false");
		MI_Uint32 arrayCount=fieldArray.GetSize();
		for(Uint32 i=0;i<arrayCount;i++)
		{
			Fzprintf(sout, T("<ArrayElement>"));
			PrintSingleInstanceToXml(fieldArray[i],false);
			Fzprintf(sout, T("</ArrayElement>"));
		}

		Fzprintf(sout, T("</CimProperty>\n"));
	}
}

static void PrintFieldToXml(const DInstance& inst)
{
	String fieldName;
	MI_Type fieldType;
	String fieldTypeToString;
	bool isFieldKey, fieldNull;
	Uint32 fieldCount = inst.Count();

	for (Uint32 i = 0; i < fieldCount;i++)
	{
		inst.GetName(i, fieldName);
		inst.GetType(i,fieldType);
		ConvertDataTypeToString(fieldType,fieldTypeToString);
		switch (fieldType)
		{
		case MI_BOOLEAN:
			{
				MI_Boolean boolFieldValue;
				inst.GetBoolean(fieldName, boolFieldValue, fieldNull, isFieldKey);
				boolean booleanFiledValue =  boolFieldValue ? True : False;
				PrintFieldDetailInfo(booleanFiledValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%s"));
				break;
			}
		case MI_SINT8:
			{
				MI_Sint8 sint8FieldValue;
				inst.GetSint8(fieldName, sint8FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(sint8FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%d"));
				break;
			}
		case MI_UINT8:
			{
				MI_Uint8 uint8FieldValue;
				inst.GetUint8(fieldName, uint8FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(uint8FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%u"));
				break;
			}
		case MI_SINT16:
			{
				MI_Sint16 sint16FieldValue;
				inst.GetSint16(fieldName, sint16FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(sint16FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%d"));
				break;
			}
		case MI_UINT16:
			{
				MI_Uint16 uint16FieldValue;
				inst.GetUint16(fieldName, uint16FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(uint16FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%u"));
				break;
			}
		case MI_SINT32:
			{
				MI_Sint32 sint32FieldValue;
				inst.GetSint32(fieldName, sint32FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(sint32FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%d"));
				break;
			}
		case MI_UINT32:
			{
				MI_Uint32 uint32FieldValue;
				inst.GetUint32(fieldName, uint32FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(uint32FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%u"));
				break;
			}
		case MI_SINT64:
			{
				MI_Sint64 sint64FieldValue;
				inst.GetSint64(fieldName, sint64FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(sint64FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,SINT64_FMT_T);
				break;
			}
		case MI_UINT64:
			{
				MI_Uint64 uint64FieldValue;
				inst.GetUint64(fieldName, uint64FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(uint64FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,UINT64_FMT_T);
				break;
			}
		case MI_REAL32:
			{
				MI_Real32 real32FieldValue;
				inst.GetReal32(fieldName, real32FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(real32FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%g"));
				break;
			}
		case MI_REAL64:
			{
				MI_Real64 real64FieldValue;
				inst.GetReal64(fieldName, real64FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(real64FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%g"));
				break;
			}
		case MI_CHAR16:
			{
				MI_Char16 char16FieldValue;
				inst.GetChar16(fieldName, char16FieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(char16FieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%u"));
				break;
			}
		case MI_DATETIME:
			{
				Datetime datetimeFieldValue;
				inst.GetDatetime(fieldName, datetimeFieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(datetimeFieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull);
				break;
			}
		case MI_STRING:
			{
				String stringFieldValue;
				inst.GetString(fieldName, stringFieldValue, fieldNull, isFieldKey);
				PrintFieldDetailInfo(stringFieldValue,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%s"));
				break;
			}
		case MI_INSTANCE:
			{
				DInstance dInstance;
				inst.GetInstance(fieldName,dInstance,fieldNull,isFieldKey);
				PrintFieldDetailInfo(dInstance,fieldName,fieldTypeToString,isFieldKey,fieldNull);
				break;
			}
		case MI_REFERENCE:
			{
				DInstance referenceDInstance;
				inst.GetReference(fieldName,referenceDInstance,fieldNull,isFieldKey);
				PrintFieldDetailInfo(referenceDInstance,fieldName,fieldTypeToString,isFieldKey,fieldNull);
				break;
			}
		case MI_BOOLEANA:
			{
				BooleanA booleanArray;
				inst.GetBooleanA(fieldName,booleanArray,fieldNull,isFieldKey);				
				//convert to boolean type
				MI_Uint32 arrayCount=booleanArray.GetSize();
				booleanA booleanFieldArray;
				for(Uint32 i=0;i<arrayCount;i++)
				{
					boolean tmpBoolean = booleanArray[i] ? True:False;
					booleanFieldArray.PushBack(tmpBoolean);
				}
				PrintFieldArrayDetailInfo(booleanFieldArray,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%s"));
				break;
			}					
		case MI_SINT8A:
			{
				Sint8A sint8Array;
				inst.GetSint8A(fieldName,sint8Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(sint8Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%d"));
				break;
			}
		case MI_UINT8A:
			{
				Uint8A uint8Array;
				inst.GetUint8A(fieldName,uint8Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(uint8Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%u"));
				break;
			}
		case MI_SINT16A:				
			{
				Sint16A sint16Array;
				inst.GetSint16A(fieldName,sint16Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(sint16Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%d"));
				break;
			}
		case MI_UINT16A:
			{
				Uint16A uint16Array;
				inst.GetUint16A(fieldName,uint16Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(uint16Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%u"));
				break;
			}
		case MI_SINT32A:
			{
				Sint32A sint32Array;
				inst.GetSint32A(fieldName,sint32Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(sint32Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%d"));
				break;
			}
		case MI_UINT32A:				
			{
				Uint32A uint32Array;
				inst.GetUint32A(fieldName,uint32Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(uint32Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%u"));
				break;
			}
		case MI_SINT64A:
			{
				Sint64A sint64Array;
				inst.GetSint64A(fieldName,sint64Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(sint64Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,SINT64_FMT_T);
				break;
			}
		case MI_UINT64A:
			{
				Uint64A uint64Array;
				inst.GetUint64A(fieldName,uint64Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(uint64Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,UINT64_FMT_T);
				break;
			}
		case MI_REAL32A:
			{
				Real32A real32Array;
				inst.GetReal32A(fieldName,real32Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(real32Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%g"));
				break;
			}
		case MI_REAL64A:
			{
				Real64A real64Array;
				inst.GetReal64A(fieldName,real64Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(real64Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%g"));
				break;
			}
		case MI_CHAR16A:
			{
				Char16A char16Array;
				inst.GetChar16A(fieldName,char16Array,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(char16Array,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%u"));
				break;
			}
		case MI_DATETIMEA:
			{
				DatetimeA datetimeArray;
				inst.GetDatetimeA(fieldName,datetimeArray,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(datetimeArray,fieldName,fieldTypeToString,isFieldKey,fieldNull);
				break;
			}
		case MI_STRINGA:				
			{
				StringA stringArray;
				inst.GetStringA(fieldName,stringArray,fieldNull,isFieldKey);
				PrintFieldArrayDetailInfo(stringArray,fieldName,fieldTypeToString,isFieldKey,fieldNull,T("%s"));
				break;
			}
		case MI_INSTANCEA:
			{
				DInstanceA instanceArray;
				inst.GetInstanceA(fieldName,instanceArray,fieldNull,isFieldKey);				
				PrintFieldArrayDetailInfo(instanceArray,fieldName,fieldTypeToString,isFieldKey,fieldNull);
				break;
			}
		case MI_REFERENCEA:
		default:
			{
				Fzprintf(sout, T("We don't support this type currently"));
				break;
			}
		}
	}
}

static MI_Result PrintSingleInstanceToXml(const DInstance& inst, bool isAddRootElement)
{
	String className = inst.GetClassName();
	String instanceNamespace=inst.GetNamespace();
	if(isAddRootElement)
	{
		Fzprintf(sout, T("<Root>"));
	}

	Fzprintf(sout, T("<CimInstance Namespace=\"%s\" ClassName=\"%s\">\n"),instanceNamespace.Str(), className.Str());
	Fzprintf(sout, T("<Properties>"));
	PrintFieldToXml(inst);
	Fzprintf(sout, T("</Properties>"));
	Fzprintf(sout, T("</CimInstance>\n"));
	if(isAddRootElement)
	{
		Fzprintf(sout, T("</Root>\n"));
	}

	MI_RETURN(MI_RESULT_OK);
}

static MI_Result PrintInstanceArrayToXml(const DInstanceA& instances, bool isAddRootElement)
{
	if(isAddRootElement)
	{
		Fzprintf(sout, T("<Root>"));
	}

	for (Uint32 i = 0; i < instances.GetSize(); i++)
			PrintSingleInstanceToXml(instances[i],false);

	if(isAddRootElement)
	{
		Fzprintf(sout, T("</Root>\n"));
	}

	MI_RETURN(MI_RESULT_OK);
}

static void PrintInstance(const DInstance& inst, bool nulls)
{
	inst.Print(sout, 0, nulls);
}

static int Encode(int argc, const char* argv[])
{
	if (argc < 3)
	{
		fprintf(serr, "Usage: %s noop CLASSNAME KEYBINDING\n\n", arg0);
		return 1;
	}

	DInstance inst;
	argc -= 2;
	argv += 2;

	if (!ArgsToInstance(argv, argv + argc, DInstance::CLASS, false, inst))
	{
		err("invalid instance name specification");
		return 1;
	}

	if (!opts.quiet)
	{
		PrintInstance(inst, opts.nulls);
	}

	return 0;
}

static MI_Result s_result;
static bool s_done;

static int EnumerateInstances(Client& client, int argc, const char* argv[])
{
	if (argc != 4)
	{
		fprintf(serr, "Usage: %s ei NAMESPACE CLASSNAME\n\n", arg0);
		return 1;
	}

	// Default to WQL query language.
	if (opts.querylang.GetSize() && opts.queryexpr.GetSize() == 0)
	{
		opts.querylang = T("WQL");
	}

	// Reject if --querylang option present but not --queryexpr option.
	if (opts.querylang.GetSize() && opts.queryexpr.GetSize() == 0)
	{
		err("--querylang options requires --queryexpr option");
		return 1;
	}

	const String nameSpace = MakeString(argv[2]);
	const String className = MakeString(argv[3]);
	Array<DInstance> instances;
	MI_Result result;

	if (!client.EnumerateInstances(nameSpace,className,opts.deep,opts.timeOut,instances,opts.querylang,opts.queryexpr,result))
	{
		err("Enumerate instances failed.");
		return 1;
	}

	if (result == MI_RESULT_OK)
	{
		 PrintInstanceArrayToXml(instances,true);
	}
	else
	{
		if (!opts.suppressResults)
			err("result: " STRF, Result_ToString(result));
		return 2;
	}

	return 0;
}

//Split each class name from classesNames, save it in classNameCollection.
void MakeClassCollection(const String& classesNames,char delim, Array<String> &classNameCollection)
{
    const MI_Char *p=classesNames.Str();
	String result;

	while(*p!=0)
	{
		if(*p==delim)
		{	
			//Return one class name, save it in classNameCollection.
			classNameCollection.PushBack(result);
			result=String();
		}
		else
		{
			result+=*p;
		}
		++p;
	}

	classNameCollection.PushBack(result);
}

static int EnumerateInstancesWithClassCollection(Client& client, const String& nameSpace, const String& classesName)
{
	// Default to WQL query language.
	if (opts.querylang.GetSize() != 0
        && opts.queryexpr.GetSize() == 0)
	{
		opts.querylang = T("WQL");
	}

	// Reject if --querylang option present but not --queryexpr option.
	if (opts.querylang.GetSize() != 0
        && opts.queryexpr.GetSize() == 0)
	{
		err("--querylang options requires --queryexpr option");
		return 1;
	}

	Array<String> classNameCollection;
	MakeClassCollection(classesName, ',' ,classNameCollection);

    Array<DInstance> allInstances;
	MI_Result result;

	for(MI_Uint32 i=0;i<classNameCollection.GetSize();i++)
	{
	    Array<DInstance> instances;
		if (!client.EnumerateInstances(nameSpace,classNameCollection[i],opts.deep,opts.timeOut,instances,opts.querylang,opts.queryexpr,result))
		{
			err("communication failed (cannot connect/initiate command)");
			return 1;
		}   

		if (result == MI_RESULT_OK)
		{
            for (MI_Uint32 j=0;j<instances.GetSize();j++)
            {
              allInstances.PushBack(instances[j]);
            }   
		}
		else
		{
			continue;
		}
	}

    PrintInstanceArrayToXml(allInstances,true);    
	return 0;
}

static int Query(Client& client, int argc, const char* argv[])
{
    // Check arguments
    if (argc != 4)
    {
        fprintf(serr, "Usage: %s wql NAMESPACE QUERY\n\n", arg0);
        return 1;
    }

    // Extract query options.
    opts.querylang = T("WQL");
    opts.queryexpr = MakeString(argv[3]);

    // Always perform deep query.
    opts.deep = true;

    // Pre-compile the query (to get className).
    std::string className;
    {
        WQL* wql = WQL_Parse(opts.queryexpr.Str(), NULL);

        if (!wql)
        {
            fprintf(serr, "%s : invalid query: %s\n\n", arg0, argv[3]);
            return 1;
        }

        className = ZToStr(wql->className);
        WQL_Delete(wql);
    }

    // Invoke enumerate with these arguments.
    const char* args[5];
    args[0] = argv[0];
    args[1] = "ei";
    args[2] = argv[2]; /* namespace */
    args[3] = className.c_str();
    args[4] = NULL;

    return EnumerateInstances(client, 4, args);
}

static int GetInstance(Client& client, int argc, const char* argv[])
{
	if (argc < 4)
	{
		fprintf(serr, "Usage: %s gi NAMESPACE INSTANCENAME\n\n", arg0);
		return 1;
	}

	const String nameSpace = MakeString(argv[2]);

	DInstance instanceName;

	argc -= 3;
	argv += 3;
	const char** p = argv;
	const char** end = p + argc;

	if (!ArgsToInstance(p, end, DInstance::CLASS, true, instanceName))
	{
		err("invalid instance name specification");
		return 1;
	}

	if (p != end)
	{
		err("extraneous arguments after instance name");
		return 1;
	}

	DInstance instance;
	MI_Result result;

	if (!client.GetInstance(nameSpace, instanceName, opts.timeOut, instance, 
		result))
	{
		err("communication failed");
		return 1;
	}

	if (!opts.quiet && result == MI_RESULT_OK)
		PrintSingleInstanceToXml(instance,true);

	if (result != MI_RESULT_OK)
	{
		if (!opts.suppressResults)
			err("result: " STRF , Result_ToString(result));
		return 2;
	}

	return 0;
}

static int CreateInstance(Client& client, int argc, const char* argv[])
{
	if (argc < 4)
	{
		fprintf(serr, "Usage: %s ci NAMESPACE INSTANCE\n\n", arg0);
		return 1;
	}

	const String nameSpace = MakeString(argv[2]);

	DInstance instance;

	argc -= 3;
	argv += 3;
	const char** p = argv;
	const char** end = p + argc;

	if (!ArgsToInstance(p, end, DInstance::CLASS, true, instance))
	{
		err("invalid instanceName name specification");
		return 1;
	}

	if (p != end)
	{
		err("extraneous arguments after instanceName name");
		return 1;
	}

	DInstance instanceName;
	MI_Result result;

	if (!client.CreateInstance(nameSpace, instance, opts.timeOut, instanceName, 
		result))
	{
		err("communication failed");
		return 1;
	}

	if (!opts.quiet && result == MI_RESULT_OK)
		PrintInstance(instanceName, true);

	if (result != MI_RESULT_OK)
	{
		if (!opts.suppressResults)
			err("result: " STRF, Result_ToString(result));
		return 2;
	}

	return 0;
}

static int ModifyInstance(Client& client, int argc, const char* argv[])
{
	if (argc < 4)
	{
		fprintf(serr, "Usage: %s mi NAMESPACE INSTANCE\n\n", arg0);
		return 1;
	}

	const String nameSpace = MakeString(argv[2]);

	DInstance instance;

	argc -= 3;
	argv += 3;
	const char** p = argv;
	const char** end = p + argc;

	if (!ArgsToInstance(p, end, DInstance::CLASS, true, instance))
	{
		err("invalid instanceName name specification");
		return 1;
	}

	if (p != end)
	{
		err("extraneous arguments after instanceName name");
		return 1;
	}

	MI_Result result;

	if (!client.ModifyInstance(nameSpace, instance, opts.timeOut, result))
	{
		err("communication failed");
		return 1;
	}

	if (result != MI_RESULT_OK)
	{
		if (!opts.suppressResults)
			err("result: " STRF, Result_ToString(result));
		return 2;
	}

	return 0;
}

static int DeleteInstance(Client& client, int argc, const char* argv[])
{
	if (argc < 4)
	{
		fprintf(serr, "Usage: %s gi NAMESPACE INSTANCENAME\n\n", arg0);
		return 1;
	}

	const String nameSpace = MakeString(argv[2]);

	DInstance instanceName;

	argc -= 3;
	argv += 3;
	const char** p = argv;
	const char** end = p + argc;

	if (!ArgsToInstance(p, end, DInstance::CLASS, true, instanceName))
	{
		err("invalid instance name specification");
		return 1;
	}

	if (p != end)
	{
		err("extraneous arguments after instance name");
		return 1;
	}

	DInstance instance;
	MI_Result result;

	if (!client.DeleteInstance(nameSpace, instanceName, opts.timeOut, result))
	{
		err("communication failed");
		return 1;
	}

	if (result != MI_RESULT_OK)
	{
		if (!opts.suppressResults)
			err("result: " STRF, Result_ToString(result));
		return 2;
	}

	return 0;
}

static int Associators(Client& client, int argc, const char* argv[])
{
	if (argc < 4)
	{
		fprintf(serr, "Usage: %s a NAMESPACE INSTANCENAME\n\n", arg0);
		return 1;
	}

	const String nameSpace = MakeString(argv[2]);

	DInstance instanceName;

	argc -= 3;
	argv += 3;
	const char** p = argv;
	const char** end = p + argc;

	if (!ArgsToInstance(p, end, DInstance::CLASS, true, instanceName))
	{
		err("invalid instance name specification");
		return 1;
	}

	if (p != end)
	{
		err("extraneous arguments after instance name");
		return 1;
	}

	Array<DInstance> instances;
	MI_Result result;

	if (!client.AssociatorInstances(
		nameSpace, 
		instanceName, 
		opts.assocClass,
		opts.resultClass,
		opts.role,
		opts.resultRole,
		opts.timeOut, 
		instances, 
		result))
	{
		err("communication failed");
		return 1;
	}

	if (!opts.quiet)
	{
		for (Uint32 i = 0; i < instances.GetSize(); i++)
			PrintInstance(instances[i], opts.nulls);
	}

	if (result != MI_RESULT_OK)
	{
		if (!opts.suppressResults)
			err("result: " STRF, Result_ToString(result));
		return 2;
	}

	return 0;
}

static int References(Client& client, int argc, const char* argv[])
{
	if (argc < 4)
	{
		fprintf(serr, "Usage: %s a NAMESPACE INSTANCENAME\n\n", arg0);
		return 1;
	}

	const String nameSpace = MakeString(argv[2]);

	DInstance instanceName;

	argc -= 3;
	argv += 3;
	const char** p = argv;
	const char** end = p + argc;

	if (!ArgsToInstance(p, end, DInstance::CLASS, true, instanceName))
	{
		err("invalid instance name specification");
		return 1;
	}

	if (p != end)
	{
		err("extraneous arguments after instance name");
		return 1;
	}

	Array<DInstance> instances;
	MI_Result result;

	if (!client.ReferenceInstances(
		nameSpace, 
		instanceName, 
		opts.assocClass,
		opts.role,
		opts.timeOut, 
		instances, 
		result))
	{
		err("communication failed");
		return 1;
	}

	if (!opts.quiet)
	{
		for (Uint32 i = 0; i < instances.GetSize(); i++)
			PrintInstance(instances[i], opts.nulls);
	}

	if (result != MI_RESULT_OK)
	{
		if (!opts.suppressResults)
			err("result: " STRF, Result_ToString(result));
		return 2;
	}

	return 0;
}

static int Invoke(Client& client, int argc, const char* argv[])
{
	if (argc < 5)
	{
		fprintf(serr, 
			"Usage: %s iv NAMESPACE INSTANCENAME METHODNAME PARAMETERS\n\n", 
			arg0);
		return 1;
	}

	const String nameSpace = MakeString(argv[2]);

	// Skip over first 3 args:
	argc -= 3;
	argv += 3;
	const char** p = argv;
	const char** end = p + argc;

	// Get instanceName parameter:
	DInstance instanceName;
	{
		if (!ArgsToInstance(p, end, DInstance::CLASS, true, instanceName))
		{
			err("invalid instance name specification");
			return 1;
		}
	}

	// Get methodName parameter:
	if (p == end)
	{
		err("expected method name");
		return 1;
	}

	String methodName = MakeString(*p);
	p++;

	// Get method parameters:
	DInstance in(T("Parameters"), DInstance::METHOD);

	if (p != end)
	{
		if (!ArgsToInstance(p, end, DInstance::METHOD, true, in))
		{
			err("invalid parameters specification");
			return 1;
		}
	}

	// Invoke the method:
	DInstance out;
	MI_Result result;

	if (!client.Invoke(nameSpace, instanceName, methodName, in, opts.timeOut, 
		out, result))
	{
		err("communication failed");
		return 1;
	}

	if (!opts.quiet && result == MI_RESULT_OK)
		PrintSingleInstanceToXml(out,true);

	if (result != MI_RESULT_OK)
	{
		if (!opts.suppressResults)
			err("result: " STRF, Result_ToString(result));
		return 2;
	}

	return 0;
}

class CliHandler : public Handler
{
public:

	/*virtual void HandleConnect();


	virtual void HandleNoOp(Uint64 msgID);*/
	virtual void HandleConnectFailed()
	{
		if (!opts.suppressResults)
			err("connect failed...");
		s_result = MI_RESULT_FAILED;
		s_done = true;
	}

	virtual void HandleDisconnect()
	{
		if (!opts.suppressResults)
			err("disconnected...");
		s_result = MI_RESULT_FAILED;
		s_done = true;
	}

	virtual void HandleInstance(Uint64 msgID, const DInstance& instance)
	{
		MI_UNUSED(msgID);

		if (!opts.quiet)
		{
			PrintInstance(instance, opts.nulls);
		}
	}

	virtual void HandleResult(Uint64 msgID, MI_Result result)
	{
		MI_UNUSED(msgID);

		if (result != MI_RESULT_OK)
		{
			if (!opts.suppressResults)
				err("result: " STRF, Result_ToString(result));
		}
		s_result = result;
		s_done = true;
	}
};

int climain(int argc, const char* argv[])
{
	arg0 = argv[0];
	const Uint64 CONNECT_TIMEOUT_USEC = 10 * 1000 * 1000;
	int r = 0;
	Client client( new CliHandler );

	// Setup default stderr and stdout streams:
	serr = stderr;
	sout = stdout;

	// Initialize options:
	opts.Clear();

	// Get the options:
	GetCommandLineDestDirOption(&argc, argv);

	// Get configuration file options:
	if (GetConfigFileOptions() != 0)
	{
		r = 1;
		goto done;
	}

	// Get the options:
	if (GetCommandLineOptions(argc, argv, opts) != 0)
	{
		r = 1;
		goto done;
    }
	
	// There must be at least 1 argument left:
	if (argc < 2)
	{
		fprintf(sout, "%s", USAGE);
		r = 1;
		goto done;
	}
    
    // Execute Linux command to get expected value 
    if (strcmp(argv[1], "xeis") == 0)
    {
        Array<DInstance> allInstances;
        ExpectedContext context = ExpectedContext(allInstances, *sout);
        context.Parse(argv[2]);
        context.GetExpectedInstance();
        PrintInstanceArrayToXml(allInstances,true);

        goto done;
    }
    
    // Connect to server:
	if (strcmp(argv[1], "enc") != 0)
	{
#if defined(CONFIG_OS_WINDOWS)
		if (!client.Connect(T("7777"), opts.user, opts.password, CONNECT_TIMEOUT_USEC))
#else
		if (!client.Connect(GetPath(ID_SOCKETFILE), opts.user, opts.password, CONNECT_TIMEOUT_USEC))
#endif
		{
#if defined(CONFIG_OS_WINDOWS)
			err("failed to connect on port 7777");
#else
			err("failed to connect to %s", GetPath(ID_SOCKETFILE));
#endif
			r = 1;
			goto done;
		}
	}

	if (strcmp(argv[1], "noop") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
			r = NoOp(client, argc, argv);
			if (r != 0)
				goto done;
		}
	}
	else if (strcmp(argv[1], "enc") == 0)
	{
		r = Encode(argc, argv);
		goto done;
	}
	else if (strcmp(argv[1], "ei") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
			r = EnumerateInstances(client, argc, argv);
			if (r != 0)
				goto done;
		}
	}
    else if (strcmp(argv[1], "eic") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
            String nameSpace = MakeString(argv[2]);
            String classesName = MakeString(argv[3]);
			r = EnumerateInstancesWithClassCollection(client, nameSpace, classesName);

			if (r != 0)
				goto done;
		}
	}
	else if (strcmp(argv[1], "id") == 0)
	{
		if (argc != 2)
		{
			fprintf(serr, "Usage: %s id\n\n", arg0);
			r = 1;
			goto done;
		}

		const char* args[5];
		args[0]= argv[0];
		args[1]= (char*)"ei";
		args[2]= (char*)"root/omi";
		args[3]= (char*)"OMI_Identify";
		args[4]= NULL;

		for (int i = 0; i < opts.repeat; i++)
		{
			r = EnumerateInstances(client, 4, args);
			if (r != 0)
				goto done;
		}
	}
	else if (strcmp(argv[1], "gi") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
			r = GetInstance(client, argc, argv);
			if (r != 0)
				goto done;
		}
	}
	else if (strcmp(argv[1], "ci") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
			r = CreateInstance(client, argc, argv);
			if (r != 0)
				goto done;
		}
	}
	else if (strcmp(argv[1], "mi") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
			r = ModifyInstance(client, argc, argv);
			if (r != 0)
				goto done;
		}
	}
	else if (strcmp(argv[1], "di") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
			r = DeleteInstance(client, argc, argv);
			if (r != 0)
				goto done;
		}
	}
	else if (strcmp(argv[1], "iv") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
			r = Invoke(client, argc, argv);
			if (r != 0)
				goto done;
		}
	}
	else if (strcmp(argv[1], "a") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
			r = Associators(client, argc, argv);
			if (r != 0)
				goto done;
		}
	}
	else if (strcmp(argv[1], "r") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
			r = References(client, argc, argv);
			if (r != 0)
				goto done;
		}
	}
	else if (strcmp(argv[1], "wql") == 0)
	{
		for (int i = 0; i < opts.repeat; i++)
		{
			r = Query(client, argc, argv);
			if (r != 0)
				goto done;
		}
	}
	else
	{
		err("unknown command: %s", argv[1]);
		r = 1;
		goto done;
	}

done:

	if (sout != stdout)
		fclose(sout);

	if (serr != stdout)
		fclose(serr);

	return r;
}

