#pragma once

namespace scoa {

template <typename... Ts>
struct match : Ts... {
	using Ts::operator()...;
};

template <typename... Ts>
match(Ts...) -> match<Ts...>;

} /* namespace scoa */
