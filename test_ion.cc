#include "ion.h"

using namespace scoa::literals;

#ifdef SCOA_TEST_SINGLE
int
main()
#else
void
test_ion()
#endif /* SCOA_TEST_SINGLE */
{
	constexpr uint64_t a = "-_"_ion;
	constexpr uint64_t b = 0b000000'000001;
	static_assert(a == b, "misc ion literal failed");

	constexpr uint64_t c = "123"_ion;
	constexpr uint64_t d = 0b000011'000100'000101;
	static_assert(c == d, "numeric ion literal failed");

	constexpr uint64_t e = "Bam"_ion;
	constexpr uint64_t f = 0b001101'100110'110010;
	static_assert(e == f, "alphabetic ion literl failed");

#ifdef SCOA_TEST_STATIC_FAIL_CASES
	constexpr uint64_t g = ""_ion;
	constexpr uint64_t h = "*"_ion;
	constexpr uint64_t i = "00000000001"_ion;
	constexpr uint64_t j = u"foo"_ion;
#endif /* SCOA_TEST_STATIC_FAIL_CASES */
}
