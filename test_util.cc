#include "util.h"

scoa::owner<int*>
foo()
{
	return nullptr;
}

#ifdef SCOA_TEST_STATIC_FAIL_CASES
scoa::owner<int>
bar()
{
	return 42;
}
#endif /* SCOA_TEST_STATIC_FAIL_CASES */

int
main()
{
	return 0;
}
