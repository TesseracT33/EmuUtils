export module Util:Bit;

import :NumericalTypes;

import <concepts>;
import <type_traits>;

export
{
	template<std::integral T> constexpr bool GetBit(T num, uint pos)
	{
		return num & 1ull << pos;
	}

	template<std::integral T> constexpr bool GetBit(const T* num, uint pos)
	{
		return *num & 1ull << pos;
	}

	template<std::integral T> constexpr void SetBit(T& num, uint pos)
	{
		num |= 1ull << pos;
	}

	template<std::integral T> constexpr void SetBit(T* num, uint pos)
	{
		*num |= 1ull << pos;
	}

	template<std::integral T> constexpr void ClearBit(T& num, uint pos)
	{
		num &= ~(1ull << pos);
	}

	template<std::integral T> constexpr void ClearBit(T* num, uint pos)
	{
		*num &= ~(1ull << pos);
	}

	template<std::integral T> constexpr void ToggleBit(T& num, uint pos)
	{
		num ^= ~(1ull << pos);
	}

	template<std::integral T> constexpr void ToggleBit(T* num, uint pos)
	{
		*num ^= ~(1ull << pos);
	}

	constexpr u8 GetByte(auto& obj, uint byte_index)
	{
		return *(reinterpret_cast<u8*>(&obj) + byte_index);
	}

	constexpr u8 SetByte(auto& obj, uint byte_index, u8 value)
	{
		*(reinterpret_cast<u8*>(&obj) + byte_index) = value;
	}

	/* Sign extends 'value' consisting of 'num_bits' bits to the width given by 'Int' */
	template<std::integral Int, uint num_bits>
	constexpr Int SignExtend(auto value)
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
			using sInt = std::make_signed<Int>::type;
			constexpr auto shift_amount = 8 * sizeof(Int) - num_bits;
			auto signed_int = static_cast<sInt>(value);
			return static_cast<Int>(static_cast<sInt>(signed_int << shift_amount) >> shift_amount);
		}
	}
}