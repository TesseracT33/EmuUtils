export module Util:Bit;

import :NumericalTypes;

import <concepts>;
import <type_traits>;

export
{
	template<std::integral Int> [[nodiscard]] constexpr bool GetBit(Int num, uint pos)
	{
		return num & 1ull << pos;
	}

	template<std::integral Int> [[nodiscard]] constexpr bool GetBit(const Int* num, uint pos)
	{
		return *num & 1ull << pos;
	}

	template<std::integral Int> constexpr void SetBit(Int& num, uint pos)
	{
		num |= 1ull << pos;
	}

	template<std::integral Int> constexpr void SetBit(Int* num, uint pos)
	{
		*num |= 1ull << pos;
	}

	template<std::integral Int> constexpr void ClearBit(Int& num, uint pos)
	{
		num &= ~(1ull << pos);
	}

	template<std::integral Int> constexpr void ClearBit(Int* num, uint pos)
	{
		*num &= ~(1ull << pos);
	}

	template<std::integral Int> constexpr void ToggleBit(Int& num, uint pos)
	{
		num ^= ~(1ull << pos);
	}

	template<std::integral Int> constexpr void ToggleBit(Int* num, uint pos)
	{
		*num ^= ~(1ull << pos);
	}

	[[nodiscard]] constexpr u8 GetByte(auto& obj, uint byte_index)
	{
		return *(reinterpret_cast<u8*>(&obj) + byte_index);
	}

	constexpr void SetByte(auto& obj, uint byte_index, u8 value)
	{
		*(reinterpret_cast<u8*>(&obj) + byte_index) = value;
	}

	/* Sign extends 'value' consisting of 'num_bits' bits to the width given by 'Int' */
	template<std::integral Int, uint num_bits>
	[[nodiscard]] constexpr Int SignExtend(auto value)
	{
		static_assert(num_bits > 0);
		static_assert(sizeof(Int) * 8 >= num_bits);
		static_assert(sizeof(Int) <= 8);

		if constexpr (num_bits == 8) {
			return Int(s8(value));
		}
		else if constexpr (num_bits == 16) {
			return Int(s16(value));
		}
		else if constexpr (num_bits == 32) {
			return Int(s32(value));
		}
		else if constexpr (num_bits == 64) {
			return value;
		}
		else {
			using sInt = std::make_signed_t<Int>;
			constexpr static auto shift_amount = 8 * sizeof(Int) - num_bits;
			auto signed_int = static_cast<sInt>(value);
			return static_cast<Int>(static_cast<sInt>(signed_int << shift_amount) >> shift_amount);
		}
	}

	template<std::integral IntOut, std::integral IntIn>
	[[nodiscard]] constexpr IntOut ZeroExtend(IntIn value)
	{
		static_assert(sizeof(IntOut) >= sizeof(IntIn));
		using uIntIn = std::make_unsigned_t<IntIn>;
		return static_cast<IntOut>(static_cast<uIntIn>(value));
	}
}