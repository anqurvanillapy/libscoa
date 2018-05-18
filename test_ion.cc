#include "ion.h"

using namespace scoa::literals;

int
main()
{
	constexpr uint64_t a = "-_"_ion;
	constexpr uint64_t b = 0b000001'000010;
	static_assert(a == b, "misc ion literal failed");

	constexpr uint64_t c = "123"_ion;
	constexpr uint64_t d = 0b000100'000101'000110;
	static_assert(c == d, "numeric ion literal failed");

	constexpr uint64_t e = "Bam"_ion;
	constexpr uint64_t f = 0b001110'100111'110011;
	static_assert(e == f, "alphabetic ion literl failed");

#ifdef SCOA_TEST_STATIC_FAIL_CASES
	constexpr uint64_t g = ""_ion;
	constexpr uint64_t h = "*"_ion;
	constexpr uint64_t i = "00000000001"_ion;
	constexpr uint64_t j = u"foo"_ion;
#endif /* SCOA_TEST_STATIC_FAIL_CASES */

	return 0;
}
