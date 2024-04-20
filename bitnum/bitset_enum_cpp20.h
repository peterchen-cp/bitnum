#pragma once

#include <type_traits>

/** \file

Bitset operations for any enum type can be enabled by declaring a function
<code>void enable_bitset_enum(T);</code> (no definition required).
*/
namespace bitnum
{
	/** concept for checking if "bitset operations" are enabled for enum type T. */
	template <typename T>
	concept is_enabled = std::is_enum_v<T> && requires(T v) { enable_bitset_enum(v); };

	/// helper: cast to underlying type
	template <typename T>
	constexpr auto ut(const T value)
	{
		return static_cast<std::underlying_type_t<T>>(value);
	}

	/// helper: cast to enum type
	template <typename T>
	constexpr T en(const std::underlying_type_t<T> value)
	{
		return static_cast<T>(value);
	}
}

// ----- operator |, |=

template <typename T>
requires bitnum::is_enabled<T>
constexpr  T operator |(const T lhs, const T rhs)
{
	using namespace bitnum;
	return en<T>(ut(lhs) | ut(rhs));
}

template <typename T>
	requires bitnum::is_enabled<T>
constexpr  T& operator |=(T & lhs, const T rhs)
{
	lhs = lhs | rhs;
	return lhs;
}

// ----- operator &, &=

template <typename T>
	requires bitnum::is_enabled<T>
constexpr  T operator &(const T lhs, const T rhs)
{
	using namespace bitnum;
	return en<T>(ut(lhs) & ut(rhs));
}

template <typename T>
	requires bitnum::is_enabled<T>
constexpr  T& operator &=(T& lhs, const T rhs)
{
	lhs = lhs & rhs;
	return lhs;
}

// ----- operator ^, =

template <typename T>
	requires bitnum::is_enabled<T>
constexpr  T operator ^(const T lhs, const T rhs)
{
	using namespace bitnum;
	return en<T>(ut(lhs) ^ ut(rhs));
}

template <typename T>
	requires bitnum::is_enabled<T>
constexpr  T& operator ^=(T& lhs, const T rhs)
{
	lhs = lhs ^ rhs;
	return lhs;
}

// ----- operator -, -= (implementing &~, &=~)

template <typename T>
	requires bitnum::is_enabled<T>
constexpr  T operator -(const T lhs, const T rhs)
{
	using namespace bitnum;
	return en<T>(ut(lhs) & ~ut(rhs));
}

template <typename T>
	requires bitnum::is_enabled<T>
constexpr  T& operator -=(T& lhs, const T rhs)
{
	lhs = lhs - rhs;
	return lhs;
}
