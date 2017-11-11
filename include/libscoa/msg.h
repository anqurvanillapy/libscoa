#pragma once

#include "common.h"

namespace scoa {

#define ATOM_MAX_SIZ 40
#define atom_size_check(p) do {                     \
		bool _atom_valid{};                         \
		for (int i = 0; i < ATOM_MAX_SIZ; ++i) {    \
			if (p[i] == '\0') _atom_valid = true;   \
		}                                           \
		if (!_atom_valid) assert(false);            \
	} while (0)


enum SCOA_MSG_TYPES {
	SCOA_MSG_ATOM_T,
	SCOA_MSG_INT32_T,
	SCOA_MSG_INT64_T,
	SCOA_MSG_FLOAT_T,
	SCOA_MSG_STRING_T,
};

template <typename T>
class scoa_msg_t {
public:
	scoa_msg_t(SCOA_MSG_TYPES ty, const T& val)
		: type_{ty}
	{
		switch (ty) {
		case SCOA_MSG_ATOM_T:
			val_atom_ = get_atom_(static_cast<std::string>(val));
		case SCOA_MSG_INT32_T:
			val_int32_ = static_cast<int_fast32_t>(val);
			break;
		case SCOA_MSG_INT64_T:
			val_int64_ = static_cast<int_fast64_t>(val);
			break;
		case SCOA_MSG_FLOAT_T:
			val_float_ = static_cast<double>(val);
			break;
		case SCOA_MSG_STRING_T:
			val_string_ = std::move(static_cast<std::string>(val));
			break;
		}
	}
	~scoa_msg_t() = default;

	scoa_msg_t(const scoa_msg_t&)               = delete;
	scoa_msg_t& operator=(const scoa_msg_t&)    = delete;
	scoa_msg_t(scoa_msg_t&&)                    = delete;
	scoa_msg_t& operator=(scoa_msg_t&&)         = delete;

	static size_t size() { return set_.size(); }
private:
	const char* get_atom_(const std::string& s);

	SCOA_MSG_TYPES type_;
	union {
		char*           val_atom_;
		int_fast32_t    val_int32_;
		int_fast64_t    val_int64_;
		double          val_float_;
		std::string     val_string_;
	};
	static std::unordered_map<std::string, const char*> set_;
};

} /* namespace scoa */
