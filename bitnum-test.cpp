#include "bitnum/bitset_enum_cpp17.h"
#include <assert.h>


namespace Test
{

enum class ETest
{
	Left = 1,
	Right = 2,
	Middle = 4,
};

void enable_bitset_enum(ETest);

}

#pragma warning(disable:26813) // "use & to test if a flag is set in bitwise enums"


int main()
{
	using namespace Test;
	{
		constexpr auto x = ETest::Left | ETest::Right;

		static_assert(std::is_same_v<decltype(x), const ETest>);
		static_assert((int)x == 3);
	}

	{
		auto x = ETest::Left | ETest::Right;
		assert((int) x == 3);

		x |= ETest::Middle;
		assert((int)x == 7);

		x -= ETest::Right;
		assert((int)x == 5);

		x &= ETest::Left;
		assert((int)x == 1);
	}

	{
		auto x = ETest::Left | ETest::Right;
		assert((int)x == 3);

		auto y = x | ETest::Middle;
		assert((int)y == 7);

		auto z = y - ETest::Right;
		assert((int)z == 5);

		auto _ = z & ETest::Left;
		assert((int)_ == 1);
	}

}
