#include "like.h"
#include <ctype.h>
#include <pal/intsafe.h>

#if defined(CONFIG_POSIX)
# include <wctype.h>
#endif

#include <pal/strings.h>

#define WILDCARD MI_T('%')
#define ANYSINGLECHAR MI_T('_')

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26018)
#pragma prefast (disable: 26001)
#endif

enum
{
    NO_MATCH = 0,
    MATCHED_WITH_WILDCARD_CHAR = 1,
    MATCHED_WITH_ONE_CHAR = 2,
};

MI_INLINE ZChar _Toupper(ZChar c)
{
#if (MI_CHAR_TYPE == 1)
    return toupper(c);
#else
    return towupper(c);
#endif
}

MI_INLINE void _FinalizeMatchState(
    unsigned char** matchState)
{
    if (*matchState != NULL)
    {
        PAL_Free(*matchState);
        *matchState = NULL;
    }
}

static int _EnsureMatchState(
    size_t stringLength,
    unsigned char** matchState)
{
    size_t buffersize = 0;

    _FinalizeMatchState(matchState);

    if (SizeTMult(stringLength + (size_t) 1, 2, &buffersize) != S_OK)
        return MI_FALSE;

    if (SizeTMult(buffersize, sizeof(unsigned char), &buffersize) != S_OK)
        return MI_FALSE;

    /* allocate buffer, which is 2 times (the string length + 1) */
    *matchState = PAL_Malloc(buffersize);

    if ( *matchState == NULL )
        return MI_FALSE;

    /* cleanup the memory */
    memset(*matchState, 0, sizeof(unsigned char) * buffersize);

    /* start from [0,0], which is always matched */
    (*matchState)[0] = MATCHED_WITH_ONE_CHAR;

    return MI_TRUE;
}

static void _SwitchRow(
    size_t rowSize,
    unsigned char** currentRow,
    unsigned char** previousRow)
{
    unsigned char* tempRow = *currentRow;

    *currentRow = *previousRow;
    *previousRow = tempRow;
    /* cleanup the current row */
    memset(*currentRow, 0, rowSize);
}

static int _MatchSet (
    const ZChar* pattern,
    const ZChar* string,
    int *skip)
{
    int bFnd;
    const ZChar* pos;
    int notinset;
    int matched;
    ZChar lastchar;

    /*this tells whether ']' is found or not */
    bFnd = MI_FALSE;

    /* Skip the opening '['. */
    pos = pattern+1;

    /* See if we are matching a [^] set. */
    notinset = (*pos == '^');
    if (notinset)
        pos++;

    /* See if the target character matches any character in the set. */
    matched = MI_FALSE;
    lastchar = '\0';

    while (*pos && *pos != ']' && !matched)
    {
        /* A range of characters is indicated by a '-' unless it's the first */
        /* character in the set (in which case it's just a character to be */
        /* matched. */
        if (*pos == '-' && lastchar != '\0')
        {
            pos++;
            if (*pos && *pos != ']')
            {
                matched = (_Toupper(*string) >= lastchar &&
                    _Toupper(*string) <= _Toupper(*pos));
                lastchar = _Toupper(*pos);
                pos++;
            }
        }
        else
        {
            /* Match a normal character in the set. */
            lastchar = _Toupper(*pos);
            matched = (_Toupper(*pos) == _Toupper(*string));
            if (!matched)
                pos++;
        }
    }

    /* Find the trailing ']'.  If the set did not contain a closing ']' */
    /* we return a failed match. */
    while (*pos && *pos != ']') pos++;
    if (*pos == ']')
    {
        pos++;
        bFnd = MI_TRUE;
    }
    /*If ']' is not found and we reach end of string match is false */
    /*since this is invalid pattern */
    if (!*pos && !bFnd)
        matched = MI_FALSE;

    /* Done. */
    *skip = (int)(pos-pattern);
    return matched == !notinset;
}

MI_Boolean WQL_MatchLike(
    _In_z_ const ZChar* pattern,
    _In_z_ const ZChar* string,
    ZChar escape)
{
    size_t stringLength;
    size_t rowLength;
    const ZChar* orgString;
    unsigned char* matchState = NULL;
    unsigned char* currentRow;
    unsigned char* previousRow;

    if (!(*pattern) || !(*string))
    {
        /* skip any trailing wildcard characters */
        while (*pattern == WILDCARD) pattern++;
        if (!(*pattern) && !(*string))
            return MI_TRUE;
        return MI_FALSE;
    }

    stringLength = Tcslen(string);
    rowLength = stringLength + 1;
    orgString = string;

    if (!_EnsureMatchState(stringLength, &matchState))
        return MI_FALSE;

    currentRow = matchState + rowLength;
    previousRow = matchState;
    while (*pattern)
    {
        /* Wildcard match. */
        if (*pattern == WILDCARD)
        {
            size_t c;

            /* skip any continuous wildcard characters */
            while (*(pattern + 1) == WILDCARD) pattern++;

            for (c = 0; c <= stringLength; c++)
            {
                unsigned char match = previousRow[c];
                size_t matchedPos;

                if (match == NO_MATCH)
                {
                    continue;
                }
                /* found a prior pattern char matched, */
                /* then mark that the current wildcard */
                /* matching the remaining part of target string */
                if (match == MATCHED_WITH_ONE_CHAR)
                {
                    matchedPos = c + 1;
                    /* current wild char still match, but it should be */
                    /* the same as its preivous pattern char, I.E., */
                    /* matched one char */
                    currentRow[c] = MATCHED_WITH_ONE_CHAR;
                }
                else
                {
                    /* if previous one is a wildcard match, */
                    /* then this wildcard has the same matching result */
                    /* with preivous char */
                    matchedPos = c;
                }
                for (; matchedPos <= stringLength; matchedPos++)
                {
                    currentRow[matchedPos] = MATCHED_WITH_WILDCARD_CHAR;
                }
                break;
            }
            _SwitchRow(rowLength, &currentRow, &previousRow);
            pattern++;
        }
        /* Set match. */
        else if (*pattern == '[')
        {
            size_t c;
            int foundMatch = MI_FALSE;
            int foundSkip = 0;

            /* find all matching points based on the */
            /* previous matching result */
            for (c = 0; c <= stringLength; c++)
            {
                unsigned char match = previousRow[c];
                int skip;
                const ZChar* currentString;

                if (match == NO_MATCH)
                {
                    continue;
                }
                currentString = orgString + c;
                if (match == MATCHED_WITH_WILDCARD_CHAR)
                {
                    /* match the current char if preivous is a wildchar match */
                    /* otherwise match the next char */
                    currentString --;
                }
                else if (c == stringLength)
                {
                    /* no match since no char left in target string */
                    break;
                }
                if (_MatchSet (pattern, currentString, &skip))
                {
                    size_t matchedPos;

                    if (!foundMatch)
                    {
                        foundMatch = MI_TRUE;
                        foundSkip = skip;
                    }
                    /* mark the current pattern char mataching result */
                    matchedPos = (size_t)(currentString - orgString) + 1;
                    currentRow[matchedPos] = MATCHED_WITH_ONE_CHAR;
                }
            }
            _SwitchRow(rowLength, &currentRow, &previousRow);
            /* no match */
            if (!foundMatch)
            {
                break;
            }
            pattern += foundSkip;
        }
        /* Single character match. */
        else
        {
            size_t c;
            int foundMatch = MI_FALSE;

            if (escape != '\0' && *pattern == escape)
            {
                pattern++;
            }

            /* find all matching points based on the */
            /* previous matching result */
            for (c = 0; c <= stringLength; c++)
            {
                unsigned char match = previousRow[c];
                const ZChar* currentString;

                if (match == NO_MATCH)
                {
                    continue;
                }
                currentString = orgString + c;
                if (match == MATCHED_WITH_WILDCARD_CHAR)
                {
                    /* match the current char if preivous is a wildchar match, */
                    /* otherwise match the next char */
                    currentString --;
                }
                else if (c == stringLength)
                {
                    /* no match since no char left in target string */
                    break;
                }

                if (_Toupper(*pattern) == _Toupper(*currentString) ||
                    *pattern == ANYSINGLECHAR)
                {
                    size_t matchedPos;

                    if (!foundMatch)
                    {
                        foundMatch = MI_TRUE;
                    }

                    /* mark the current pattern char mataching result */
                    matchedPos = (size_t)(currentString - orgString) + 1;
                    currentRow[matchedPos] = MATCHED_WITH_ONE_CHAR;
                }
            }
            _SwitchRow(rowLength, &currentRow, &previousRow);
            /* no match */
            if (!foundMatch)
            {
                break;
            }

            pattern ++;
        }
    }

    /* Matched if the last pattern char mattached the last target string char */
    /* NoMatch otherwise */
    {
        MI_Boolean flag = (previousRow[stringLength] != 0) ? MI_TRUE : MI_FALSE;
        PAL_Free(matchState);
        return flag;
    }
}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif
