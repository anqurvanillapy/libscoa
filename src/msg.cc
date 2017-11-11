#include "libscoa/msg.h"

namespace scoa {

template <typename T>
std::unordered_map<std::string, const char*> scoa_msg_t<T>::set_{};

template <typename T>
const char*
scoa_msg_t<T>::get_atom_(const std::string& s)
{
	auto const p = s.c_str();
	atom_size_check(p);
	return p;
}

} /* namespace scoa */
