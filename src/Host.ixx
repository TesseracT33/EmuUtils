export module Util:Host;

import <bit>;

export namespace Host
{
	constexpr std::endian endianness = std::endian::native;

	constexpr bool has_sse = [] { /* SSE 4.2 */
#ifdef _MSC_VER
#ifdef _M_AMD64 /* TODO: not sure how to check for SSE >= 3 specifically on x64. __cpuid is not constexpr. */
		return true;
#else
		return false;
#endif
#else
#ifdef __SSE4_2__
		return true;
#else
		return false;
#endif
#endif
	}();

	constexpr bool has_avx = [] {
#ifdef __AVX__
		return true;
#else
		return false;
#endif
	}();

	constexpr bool has_avx2 = [] {
#ifdef __AVX2__
		return true;
#else
		return false;
#endif
	}();

	constexpr bool has_avx512bw = [] {
#ifdef __AVX512BW__
		return true;
#else
		return false;
#endif
	}();

	constexpr bool has_avx512cd = [] {
#ifdef __AVX512CD__
		return true;
#else
		return false;
#endif
	}();

	constexpr bool has_avx512dq = [] {
#ifdef __AVX512DQ__
		return true;
#else
		return false;
#endif
	}();

	constexpr bool has_avx512f = [] {
#ifdef __AVX512F__
		return true;
#else
		return false;
#endif
	}();

	constexpr bool has_avx512vl = [] {
#ifdef __AVX512VL__
		return true;
#else
		return false;
#endif
	}();
}