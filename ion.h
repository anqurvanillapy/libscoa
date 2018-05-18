#pragma once

#include <type_traits>
#include <cstdint>

namespace scoa {
namespace literals {

namespace {

template <char C>
constexpr std::uint64_t
to_ion_val_()
{
	if constexpr (C == 45) {            // hyphen
		return 1;                       // (1)
	} else if (C == 95) {               // underscore
		return 2;                       // (2)
	} else if (C >= 48 && C <= 57) {    // nums
		return C - 45;                  // (3 - 12)
	} else if (C >= 65 && C <= 90) {    // upper
		return C - 52;                  // (13 - 38)
	} else if (C >= 97 && C <= 122) {   // lower
		return C - 58;                  // (39 - 64)
	} else {
		return 0;
	}
}

template <char...> struct ion_constant_;

template <>
struct ion_constant_<> {
	static const std::uint64_t value = 0;
	static const unsigned n = 0;
};

template <char C, char... Cs>
struct ion_constant_<C, Cs...> {
	static const std::uint64_t value = [] {
		static_assert(to_ion_val_<C>() > 0, "unsupported character(s) found");
		return (to_ion_val_<C>() << ion_constant_<Cs...>::n)
			| ion_constant_<Cs...>::value;
	}();
	static const unsigned n = ion_constant_<Cs...>::n + 6;
};

} /* namespace */

// XXX: String literal operator template is not in standard.  Supported as an
// extension in GCC/Clang.
template <typename CharT, CharT ...String>
constexpr std::uint64_t
operator""_ion()
{
	static_assert(sizeof...(String) <= 10, "str should not be longer than 10");
	static_assert(sizeof...(String) > 0, "ion literal cannot be empty");
	static_assert(std::is_same_v<CharT, char>, "a char sequence is required");
	std::uint64_t ret = ion_constant_<String...>::value;
	return ret;
}

} /* namespace literals */
} /* namespace scoa */
