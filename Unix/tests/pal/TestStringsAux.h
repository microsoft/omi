static void FUNCTION()
{
    CHAR buf[1024];
    size_t n;

    memset(buf, 0xFF, sizeof(buf));
    n = STRLCPY(buf, LIT("abc"), 8);
    TEST_ASSERT(STRCMP(buf, LIT("abc")) == 0);
    TEST_ASSERT(n == 3);
    PAL_UNUSED(n);

    memset(buf, 0xFF, sizeof(buf));
    n = STRLCPY(buf, LIT("abc"), 3);
    TEST_ASSERT(STRCMP(buf, LIT("ab")) == 0);
    TEST_ASSERT(n == 3);
    PAL_UNUSED(n);

    memset(buf, 0xFF, sizeof(buf));
    n = STRLCPY(buf, LIT(""), 1);
    TEST_ASSERT(STRCMP(buf, LIT("")) == 0);
    TEST_ASSERT(n == 0);
    PAL_UNUSED(n);

    memset(buf, 0xFF, sizeof(buf));
    n = STRLCPY(buf, LIT("a"), 2);
    TEST_ASSERT(STRCMP(buf, LIT("a")) == 0);
    TEST_ASSERT(n == 1);
    PAL_UNUSED(n);

    memset(buf, 0xFF, sizeof(buf));
    STRLCPY(buf, LIT("aaa"), 8);
    STRLCAT(buf, LIT("bbb"), 8);
    n = STRLCAT(buf, LIT("ccc"), 8);
    TEST_ASSERT(STRCMP(buf, LIT("aaabbbc")) == 0);
    TEST_ASSERT(n == 3);
    PAL_UNUSED(n);

    n = STRLCAT(buf, LIT("ccddd"), 10);
    TEST_ASSERT(STRCMP(buf, LIT("aaabbbccc")) == 0);
    TEST_ASSERT(n == 5);
    PAL_UNUSED(n);
}
