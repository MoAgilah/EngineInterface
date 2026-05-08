#include "CppUnitTest.h"

#include <Utilities/Colour.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(ColourTests)
	{
	public:

		// ======================================================
		// Constructor
		// ======================================================

		TEST_METHOD(Colour_Constructor_SetsRGBValuesCorrectly)
		{
			Colour c(10, 20, 30);

			Assert::AreEqual((uint8_t)10, c.r);
			Assert::AreEqual((uint8_t)20, c.g);
			Assert::AreEqual((uint8_t)30, c.b);
		}

		TEST_METHOD(Colour_Constructor_DefaultAlpha_Is255)
		{
			Colour c(10, 20, 30);
			Assert::AreEqual((uint8_t)255, c.a);
		}

		TEST_METHOD(Colour_Constructor_WithAlpha_SetsAllValues)
		{
			Colour c(10, 20, 30, 40);

			Assert::AreEqual((uint8_t)10, c.r);
			Assert::AreEqual((uint8_t)20, c.g);
			Assert::AreEqual((uint8_t)30, c.b);
			Assert::AreEqual((uint8_t)40, c.a);
		}

		// ======================================================
		// Named Colours
		// ======================================================

		TEST_METHOD(Colour_Black_IsCorrect)
		{
			Colour c = Colour::Black;

			Assert::AreEqual((uint8_t)0, c.r);
			Assert::AreEqual((uint8_t)0, c.g);
			Assert::AreEqual((uint8_t)0, c.b);
			Assert::AreEqual((uint8_t)255, c.a);
		}

		TEST_METHOD(Colour_White_IsCorrect)
		{
			Colour c = Colour::White;

			Assert::AreEqual((uint8_t)255, c.r);
			Assert::AreEqual((uint8_t)255, c.g);
			Assert::AreEqual((uint8_t)255, c.b);
			Assert::AreEqual((uint8_t)255, c.a);
		}

		TEST_METHOD(Colour_Red_IsCorrect)
		{
			Colour c = Colour::Red;

			Assert::AreEqual((uint8_t)255, c.r);
			Assert::AreEqual((uint8_t)0, c.g);
			Assert::AreEqual((uint8_t)0, c.b);
			Assert::AreEqual((uint8_t)255, c.a);
		}

		TEST_METHOD(Colour_Green_IsCorrect)
		{
			Colour c = Colour::Green;

			Assert::AreEqual((uint8_t)0, c.r);
			Assert::AreEqual((uint8_t)255, c.g);
			Assert::AreEqual((uint8_t)0, c.b);
			Assert::AreEqual((uint8_t)255, c.a);
		}

		TEST_METHOD(Colour_Blue_IsCorrect)
		{
			Colour c = Colour::Blue;

			Assert::AreEqual((uint8_t)0, c.r);
			Assert::AreEqual((uint8_t)0, c.g);
			Assert::AreEqual((uint8_t)255, c.b);
			Assert::AreEqual((uint8_t)255, c.a);
		}

		TEST_METHOD(Colour_Yellow_IsCorrect)
		{
			Colour c = Colour::Yellow;

			Assert::AreEqual((uint8_t)255, c.r);
			Assert::AreEqual((uint8_t)255, c.g);
			Assert::AreEqual((uint8_t)0, c.b);
			Assert::AreEqual((uint8_t)255, c.a);
		}

		TEST_METHOD(Colour_Magenta_IsCorrect)
		{
			Colour c = Colour::Magenta;

			Assert::AreEqual((uint8_t)255, c.r);
			Assert::AreEqual((uint8_t)0, c.g);
			Assert::AreEqual((uint8_t)255, c.b);
			Assert::AreEqual((uint8_t)255, c.a);
		}

		TEST_METHOD(Colour_Cyan_IsCorrect)
		{
			Colour c = Colour::Cyan;

			Assert::AreEqual((uint8_t)0, c.r);
			Assert::AreEqual((uint8_t)255, c.g);
			Assert::AreEqual((uint8_t)255, c.b);
			Assert::AreEqual((uint8_t)255, c.a);
		}

		TEST_METHOD(Colour_Transparent_IsCorrect)
		{
			Colour c = Colour::Transparent;

			Assert::AreEqual((uint8_t)0, c.r);
			Assert::AreEqual((uint8_t)0, c.g);
			Assert::AreEqual((uint8_t)0, c.b);
			Assert::AreEqual((uint8_t)0, c.a);
		}
	};
}