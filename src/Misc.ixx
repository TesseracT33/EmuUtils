export module Util:Misc;

import :NumericalTypes;

import <array>;
import <concepts>;
import <type_traits>;

export
{
	template<size_t bound>
	constexpr std::array<size_t, bound> range = []
	{
		static_assert(bound > 0);
		std::array<size_t, bound> arr{};
		for (size_t i = 0; i < arr.size(); ++i) {
			arr[i] = i;
		}
		return arr;
	}();


	template <typename... T>
	constexpr bool AlwaysFalse = false;


	template<typename T, size_t size>
	constexpr std::array<T, size> MakeArray(const T& value)
	{
		std::array<T, size> arr{};
		arr.fill(value);
		return arr;
	}


	template<std::integral Int>
	constexpr auto MakeSigned(Int x)
	{
		return static_cast<std::make_signed_t<Int>>(x);
	}


	template<std::integral Int>
	constexpr auto MakeUnsigned(Int x)
	{
		return static_cast<std::make_unsigned_t<Int>>(x);
	}
}