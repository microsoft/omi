#ifndef _nitsstubs_h
#define _nitsstubs_h

#include <cassert>

#define NitsTest(FUNC) static void FUNC() {
#define NitsEndTest }
#define NitsAssert(COND, STR) assert(COND)

#endif /* _nitsstubs_h */
