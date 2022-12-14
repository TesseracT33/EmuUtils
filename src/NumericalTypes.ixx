export module Util:NumericalTypes;

import <cstddef>;
import <cstdint>;

export
{
	using s8 = int8_t;
	using s16 = int16_t;
	using s32 = int32_t;
	using s64 = int64_t;

	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;

	using uint = unsigned;

	using f32 = float;
	using f64 = double;

#if defined __GNUC__ || defined __clang__
	using s128 = __int128;
	using u128 = unsigned __int128;
#endif

	using std::size_t;
}