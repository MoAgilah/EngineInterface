#include "CppUnitTest.h"

#include <Utilities/Rect.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(RectTests)
	{
	public:
		TEST_METHOD(FloatRect_Constructor_PopulatesValues)
		{
			FloatRect rect(1.f, 2.f, 3.f, 4.f);

			Assert::AreEqual(1.f, rect.m_left);
			Assert::AreEqual(2.f, rect.m_top);
			Assert::AreEqual(3.f, rect.m_width);
			Assert::AreEqual(4.f, rect.m_height);
		}

		TEST_METHOD(IntRect_Constructor_PopulatesValues)
		{
			IntRect rect(1, 2, 3, 4);

			Assert::AreEqual(1, rect.m_left);
			Assert::AreEqual(2, rect.m_top);
			Assert::AreEqual(3, rect.m_width);
			Assert::AreEqual(4, rect.m_height);
		}

		TEST_METHOD(FloatRect_Min_ReturnsCorrectValue)
		{
			FloatRect rect(1.f, 2.f, 3.f, 4.f);

			auto min = rect.Min();

			Assert::AreEqual(1.f, min.x);
			Assert::AreEqual(2.f, min.y);
		}

		TEST_METHOD(IntRect_Min_ReturnsCorrectValue)
		{
			IntRect rect(1, 2, 3, 4);

			auto min = rect.Min();

			Assert::AreEqual(1, min.x);
			Assert::AreEqual(2, min.y);
		}

		TEST_METHOD(FloatRect_Max_ReturnsCorrectValue)
		{
			FloatRect rect(1, 2, 3, 4);

			auto max = rect.Max();

			Assert::AreEqual(4.f, max.x);
			Assert::AreEqual(6.f, max.y);
		}

		TEST_METHOD(IntRect_Max_ReturnsCorrectValue)
		{
			IntRect rect(1, 2, 3, 4);

			auto max = rect.Max();

			Assert::AreEqual(4, max.x);
			Assert::AreEqual(6, max.y);
		}

		TEST_METHOD(FloatRect_GetCentre_ReturnsCorrectValue)
		{
			IntRect rect(0, 0, 3, 3);

			auto centre = rect.GetCentre();

			Assert::AreEqual(1.5f, centre.x);
			Assert::AreEqual(1.5f, centre.y);
		}

		TEST_METHOD(IntRect_GetCentre_ReturnsCorrectFloatValue)
		{
			FloatRect rect(0.f, 0.f, 4.f, 4.f);

			auto centre = rect.GetCentre();

			Assert::AreEqual(2.f, centre.x);
			Assert::AreEqual(2.f, centre.y);
		}
	};
}