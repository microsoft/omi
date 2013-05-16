#if !defined(HASHSTR_CHAR)
# define HASHSTR_CHAR char
#endif

#if !defined(HASHSTR_T)
# define HASHSTR_T(STR) STR
#endif

#if !defined(HASHSTR_STRCMP)
# define HASHSTR_STRCMP strcmp
#endif

int HashStr(const HASHSTR_CHAR* s, size_t n)
{

    switch (n)
    {
    case 0:
            if (HASHSTR_STRCMP(s, HASHSTR_T("")) == 0)
                return TAG46;
    break;
    case 4:
        switch (s[0])
        {
        case 78:
            if (HASHSTR_STRCMP(s, HASHSTR_T("None")) == 0)
                return WSMANTAG_ENUM_POLYMORPHISM_MODE_NONE;
        break;
        case 97:
            if (HASHSTR_STRCMP(s, HASHSTR_T("a:To")) == 0)
                return WSMANTAG_TO;
        break;
        }

    break;
    case 6:
            if (HASHSTR_STRCMP(s, HASHSTR_T("n:Pull")) == 0)
                return WSMANTAG_ENUM_PULL;
    break;
    case 7:
            if (HASHSTR_STRCMP(s, HASHSTR_T("Dialect")) == 0)
                return WSMANTAG_ENUM_DIALIECT;
    break;
    case 8:
        switch (s[0])
        {
        case 97:
            if (HASHSTR_STRCMP(s, HASHSTR_T("a:Action")) == 0)
                return WSMANTAG_ACTION;
        break;
        case 115:
            if (HASHSTR_STRCMP(s, HASHSTR_T("s:Header")) == 0)
                return WSMANTAG_HEADER;
        break;
        case 119:
            if (HASHSTR_STRCMP(s, HASHSTR_T("w:Filter")) == 0)
                return WSMANTAG_ENUM_FILTER;
        break;
        }

    break;
    case 9:
        switch (s[4])
        {
        case 100:
            if (HASHSTR_STRCMP(s, HASHSTR_T("a:Address")) == 0)
                return WSMANTAG_ADDRESS;
        break;
        case 108:
            if (HASHSTR_STRCMP(s, HASHSTR_T("n:Release")) == 0)
                return WSMANTAG_ENUM_RELEASE;
        break;
        case 112:
            if (HASHSTR_STRCMP(s, HASHSTR_T("a:ReplyTo")) == 0)
                return WSMANTAG_REPLY_TO;
        break;
        }

    break;
    case 10:
        switch (s[0])
        {
        case 105:
            if (HASHSTR_STRCMP(s, HASHSTR_T("i:Identify")) == 0)
                return WSMANTAG_IDENTIFY;
        break;
        case 119:
            if (HASHSTR_STRCMP(s, HASHSTR_T("w:Selector")) == 0)
                return WSMANTAG_SELECTOR;
        break;
        }

    break;
    case 11:
        switch (s[0])
        {
        case 97:
            if (HASHSTR_STRCMP(s, HASHSTR_T("a:MessageID")) == 0)
                return WSMANTAG_MESSAGE_ID;
        break;
        case 110:
            if (HASHSTR_STRCMP(s, HASHSTR_T("n:Enumerate")) == 0)
                return WSMANTAG_ENUM_ENUMERATE;
        break;
        }

    break;
    case 12:
            if (HASHSTR_STRCMP(s, HASHSTR_T("EnumerateEPR")) == 0)
                return WSMANTAG_ENUM_MODE_EPR;
    break;
    case 13:
        switch (s[2])
        {
        case 77:
            if (HASHSTR_STRCMP(s, HASHSTR_T("w:MaxElements")) == 0)
                return WSMANTAG_ENUM_MAX_ELEMENTS;
            if (HASHSTR_STRCMP(s, HASHSTR_T("n:MaxElements")) == 0)
                return WSMANTAG_PULL_MAX_ELEMENTS;
        break;
        case 82:
            if (HASHSTR_STRCMP(s, HASHSTR_T("w:ResourceURI")) == 0)
                return WSMANTAG_RESOURCE_URI;
        break;
        case 83:
            if (HASHSTR_STRCMP(s, HASHSTR_T("w:SelectorSet")) == 0)
                return WSMANTAG_SELECTOR_SET;
        break;
        }

    break;
    case 15:
            if (HASHSTR_STRCMP(s, HASHSTR_T("EnumerateObject")) == 0)
                return WSMANTAG_ENUM_MODE_OBJECT;
    break;
    case 17:
        switch (s[2])
        {
        case 69:
            if (HASHSTR_STRCMP(s, HASHSTR_T("w:EnumerationMode")) == 0)
                return WSMANTAG_ENUM_MODE;
        break;
        case 77:
            if (HASHSTR_STRCMP(s, HASHSTR_T("w:MaxEnvelopeSize")) == 0)
                return WSMANTAG_MAX_ENVELOPE_SIZE;
        break;
        }

    break;
    case 18:
            if (HASHSTR_STRCMP(s, HASHSTR_T("b:PolymorphismMode")) == 0)
                return WSMANTAG_ENUM_POLYMORPHISM_MODE;
    break;
    case 20:
            if (HASHSTR_STRCMP(s, HASHSTR_T("n:EnumerationContext")) == 0)
                return WSMANTAG_PULL_ENUMERATION_CONTEXT;
    break;
    case 21:
        switch (s[0])
        {
        case 69:
            if (HASHSTR_STRCMP(s, HASHSTR_T("EnumerateObjectAndEPR")) == 0)
                return WSMANTAG_ENUM_MODE_OBJECT_AND_EPR;
        break;
        case 119:
            if (HASHSTR_STRCMP(s, HASHSTR_T("w:OptimizeEnumeration")) == 0)
                return WSMANTAG_ENUM_OPTIMIZE_ENUMERATION;
        break;
        }

    break;
    case 25:
        switch (s[0])
        {
        case 69:
            if (HASHSTR_STRCMP(s, HASHSTR_T("ExcludeSubClassProperties")) == 0)
                return WSMANTAG_ENUM_POLYMORPHISM_MODE_EXCLUDE_PROPS;
        break;
        case 73:
            if (HASHSTR_STRCMP(s, HASHSTR_T("IncludeSubClassProperties")) == 0)
                return WSMANTAG_ENUM_POLYMORPHISM_MODE_INCLUDE_PROPS;
        break;
        }

    break;
    case 50:
        switch (s[47])
        {
        case 71:
            if (HASHSTR_STRCMP(s, HASHSTR_T("http://schemas.xmlsoap.org/ws/2004/09/transfer/Get")) == 0)
                return WSMANTAG_ACTION_GET;
        break;
        case 80:
            if (HASHSTR_STRCMP(s, HASHSTR_T("http://schemas.xmlsoap.org/ws/2004/09/transfer/Put")) == 0)
                return WSMANTAG_ACTION_PUT;
        break;
        }

    break;
    case 53:
        switch (s[47])
        {
        case 67:
            if (HASHSTR_STRCMP(s, HASHSTR_T("http://schemas.xmlsoap.org/ws/2004/09/transfer/Create")) == 0)
                return WSMANTAG_ACTION_CREATE;
        break;
        case 68:
            if (HASHSTR_STRCMP(s, HASHSTR_T("http://schemas.xmlsoap.org/ws/2004/09/transfer/Delete")) == 0)
                return WSMANTAG_ACTION_DELETE;
        break;
        }

    break;
    case 54:
            if (HASHSTR_STRCMP(s, HASHSTR_T("http://schemas.xmlsoap.org/ws/2004/09/enumeration/Pull")) == 0)
                return WSMANTAG_ACTION_PULL;
    break;
    case 57:
            if (HASHSTR_STRCMP(s, HASHSTR_T("http://schemas.xmlsoap.org/ws/2004/09/enumeration/Release")) == 0)
                return WSMANTAG_ACTION_RELEASE;
    break;
    case 59:
            if (HASHSTR_STRCMP(s, HASHSTR_T("http://schemas.xmlsoap.org/ws/2004/09/enumeration/Enumerate")) == 0)
                return WSMANTAG_ACTION_ENUMERATE;
    break;
    }
    /* Not found */
    return 0;
}
