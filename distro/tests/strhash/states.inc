int QuickStr(const char* s, size_t n)
{

    switch (n)
    {
    case 4:
        switch (s[0])
        {
        case 73:
            if (strcmp(s, "Iowa") == 0)
                return STATE_Iowa;
        break;
        case 79:
            if (strcmp(s, "Ohio") == 0)
                return STATE_Ohio;
        break;
        case 85:
            if (strcmp(s, "Utah") == 0)
                return STATE_Utah;
        break;
        }

    break;
    case 5:
        switch (s[0])
        {
        case 73:
            if (strcmp(s, "Idaho") == 0)
                return STATE_Idaho;
        break;
        case 77:
            if (strcmp(s, "Maine") == 0)
                return STATE_Maine;
        break;
        case 84:
            if (strcmp(s, "Texas") == 0)
                return STATE_Texas;
        break;
        }

    break;
    case 6:
        switch (s[0])
        {
        case 65:
            if (strcmp(s, "Alaska") == 0)
                return STATE_Alaska;
        break;
        case 72:
            if (strcmp(s, "Hawaii") == 0)
                return STATE_Hawaii;
        break;
        case 75:
            if (strcmp(s, "Kansas") == 0)
                return STATE_Kansas;
        break;
        case 78:
            if (strcmp(s, "Nevada") == 0)
                return STATE_Nevada;
        break;
        case 79:
            if (strcmp(s, "Oregon") == 0)
                return STATE_Oregon;
        break;
        }

    break;
    case 7:
        switch (s[0])
        {
        case 65:
            if (strcmp(s, "Alabama") == 0)
                return STATE_Alabama;
            if (strcmp(s, "Arizona") == 0)
                return STATE_Arizona;
        break;
        case 70:
            if (strcmp(s, "Florida") == 0)
                return STATE_Florida;
        break;
        case 71:
            if (strcmp(s, "Georgia") == 0)
                return STATE_Georgia;
        break;
        case 73:
            if (strcmp(s, "Indiana") == 0)
                return STATE_Indiana;
        break;
        case 77:
            if (strcmp(s, "Montana") == 0)
                return STATE_Montana;
        break;
        case 86:
            if (strcmp(s, "Vermont") == 0)
                return STATE_Vermont;
        break;
        case 87:
            if (strcmp(s, "Wyoming") == 0)
                return STATE_Wyoming;
        break;
        }

    break;
    case 8:
        switch (s[4])
        {
        case 89:
            if (strcmp(s, "New York") == 0)
                return STATE_New_York;
        break;
        case 97:
            if (strcmp(s, "Nebraska") == 0)
                return STATE_Nebraska;
        break;
        case 104:
            if (strcmp(s, "Oklahoma") == 0)
                return STATE_Oklahoma;
        break;
        case 105:
            if (strcmp(s, "Michigan") == 0)
                return STATE_Michigan;
            if (strcmp(s, "Virginia") == 0)
                return STATE_Virginia;
        break;
        case 108:
            if (strcmp(s, "Maryland") == 0)
                return STATE_Maryland;
        break;
        case 110:
            if (strcmp(s, "Arkansas") == 0)
                return STATE_Arkansas;
            if (strcmp(s, "Illinois") == 0)
                return STATE_Illinois;
        break;
        case 111:
            if (strcmp(s, "Missouri") == 0)
                return STATE_Missouri;
        break;
        case 114:
            if (strcmp(s, "Colorado") == 0)
                return STATE_Colorado;
        break;
        case 117:
            if (strcmp(s, "Kentucky") == 0)
                return STATE_Kentucky;
        break;
        case 119:
            if (strcmp(s, "Delaware") == 0)
                return STATE_Delaware;
        break;
        }

    break;
    case 9:
        switch (s[0])
        {
        case 76:
            if (strcmp(s, "Louisiana") == 0)
                return STATE_Louisiana;
        break;
        case 77:
            if (strcmp(s, "Minnesota") == 0)
                return STATE_Minnesota;
        break;
        case 84:
            if (strcmp(s, "Tennessee") == 0)
                return STATE_Tennessee;
        break;
        case 87:
            if (strcmp(s, "Wisconsin") == 0)
                return STATE_Wisconsin;
        break;
        }

    break;
    case 10:
        switch (s[4])
        {
        case 74:
            if (strcmp(s, "New Jersey") == 0)
                return STATE_New_Jersey;
        break;
        case 77:
            if (strcmp(s, "New Mexico") == 0)
                return STATE_New_Mexico;
        break;
        case 102:
            if (strcmp(s, "California") == 0)
                return STATE_California;
        break;
        case 105:
            if (strcmp(s, "Washington") == 0)
                return STATE_Washington;
        break;
        }

    break;
    case 11:
        switch (s[0])
        {
        case 67:
            if (strcmp(s, "Connecticut") == 0)
                return STATE_Connecticut;
        break;
        case 77:
            if (strcmp(s, "Mississippi") == 0)
                return STATE_Mississippi;
        break;
        }

    break;
    case 12:
        switch (s[0])
        {
        case 78:
            if (strcmp(s, "North Dakota") == 0)
                return STATE_North_Dakota;
        break;
        case 80:
            if (strcmp(s, "Pennsylvania") == 0)
                return STATE_Pennsylvania;
        break;
        case 82:
            if (strcmp(s, "Rhode Island") == 0)
                return STATE_Rhode_Island;
        break;
        case 83:
            if (strcmp(s, "South Dakota") == 0)
                return STATE_South_Dakota;
        break;
        }

    break;
    case 13:
        switch (s[0])
        {
        case 77:
            if (strcmp(s, "Massachusetts") == 0)
                return STATE_Massachusetts;
        break;
        case 78:
            if (strcmp(s, "New Hampshire") == 0)
                return STATE_New_Hampshire;
        break;
        case 87:
            if (strcmp(s, "West Virginia") == 0)
                return STATE_West_Virginia;
        break;
        }

    break;
    case 14:
        switch (s[0])
        {
        case 78:
            if (strcmp(s, "North Carolina") == 0)
                return STATE_North_Carolina;
        break;
        case 83:
            if (strcmp(s, "South Carolina") == 0)
                return STATE_South_Carolina;
        break;
        }

    break;
    case 20:
            if (strcmp(s, "District of Columbia") == 0)
                return STATE_District_of_Columbia;
    break;
    }
    /* Not found */
    return 0;
}
