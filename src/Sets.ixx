export module Util:Sets;

export
{
	template<typename K, typename V1, typename... V2>
	constexpr bool OneOf(K key, V1 first, V2... rest)
	{
		if constexpr (sizeof...(rest) == 0) {
			return key == first;
		}
		else {
			return key == first || OneOf(key, rest...);
		}
	}
}

/////////// Tests /////////////
static_assert(OneOf(0, 0));
static_assert(!OneOf(0, 1));
static_assert(OneOf(0, 1, 2, 0, 3));
static_assert(OneOf(0, 1, 2, 3, 0));
static_assert(!OneOf(0, 1, 2, 3, 4));