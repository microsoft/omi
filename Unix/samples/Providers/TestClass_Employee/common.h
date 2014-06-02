#define POST_ERROR(_context, _result, _type, _contextualMessage) \
{    \
    MI_PostError(_context, _result, _type, _contextualMessage);        \
    return;    \
}
