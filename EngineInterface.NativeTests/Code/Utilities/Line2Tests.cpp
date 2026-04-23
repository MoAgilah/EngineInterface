#include "CppUnitTest.h"

#include <Utilities/Line2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(Line2Tests)
	{
	public:
		TEST_METHOD(Line2i_Constructor_PopulatesValues)
		{
			Line2i line({ 1, 2 }, { 3, 4 });

			Assert::AreEqual(1, line.start.x);
			Assert::AreEqual(2, line.start.y);
			Assert::AreEqual(3, line.end.x);
			Assert::AreEqual(4, line.end.y);
		}

		TEST_METHOD(Line2f_Constructor_PopulatesValues)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });

			Assert::AreEqual(1.f, line.start.x);
			Assert::AreEqual(2.f, line.start.y);
			Assert::AreEqual(3.f, line.end.x);
			Assert::AreEqual(4.f, line.end.y);
		}

		TEST_METHOD(Line2i_GetMidPoint_ReturnsCorrectValue)
		{
			Line2i line({ 1, 2 }, { 3, 4 });

			Vector2f midpoint = line.GetMidPoint();

			Assert::AreEqual(midpoint.x, 2.f);
			Assert::AreEqual(midpoint.y, 3.f);
		}

		TEST_METHOD(Line2f_GetMidPoint_ReturnsCorrectValue)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });

			Vector2f midpoint = line.GetMidPoint();

			Assert::AreEqual(midpoint.x, 2.f);
			Assert::AreEqual(midpoint.y, 3.f);
		}

		TEST_METHOD(Line2i_DistX_ReturnsCorrectValue)
		{
			Line2i line({ 1, 2 }, { 3, 4 });

			Assert::AreEqual(2, line.DistX());
		}

		TEST_METHOD(Line2i_DistY_ReturnsCorrectValue)
		{
			Line2i line({ 1, 2 }, { 3, 4 });

			Assert::AreEqual(2, line.DistX());
		}

		TEST_METHOD(Line2f_DistX_ReturnsCorrectValue)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });

			Assert::AreEqual(2.f, line.DistX());
		}

		TEST_METHOD(Line2f_DistY_ReturnsCorrectValue)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });

			Assert::AreEqual(2.f, line.DistX());
		}

		TEST_METHOD(Line2i_CalculateAngle_ReturnsCorrectValue)
		{
			Line2i line({ 1, 2 }, { 3, 4 });

			Assert::AreEqual(45.f, line.CalculateAngle());
		}

		TEST_METHOD(Line2f_CalculateAngle_ReturnsCorrectValue)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });

			Assert::AreEqual(45.f, line.CalculateAngle());
		}

		TEST_METHOD(Line2i_SqDistPointSegment_ReturnsCorrectValue)
		{
			Line2i line({ 1, 2 }, { 3, 4 });
			Vector2f vec({ 5.f, 6.f });

			Assert::AreEqual(8.f, line.SqDistPointSegment(vec));
		}

		TEST_METHOD(Line2f_SqDistPointSegment_ReturnsCorrectValue)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });
			Vector2f vec({ 5, 6 });

			Assert::AreEqual(8.f, line.SqDistPointSegment(vec));
		}

		TEST_METHOD(Line2i_ClosestPointOnLineSegment_ReturnsCorrectValue)
		{
			Line2i line({ 1, 2 }, { 3, 4 });
			Vector2f point({ 5.f, 6.f });

			Vector2f result = line.ClosestPointOnLineSegment(point);

			Assert::AreEqual(3.f, result.x);
			Assert::AreEqual(4.f, result.y);
		}

		TEST_METHOD(Line2f_ClosestPointOnLineSegment_ReturnsCorrectValue)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });
			Vector2f point({ 5.f, 6.f });

			Vector2f result = line.ClosestPointOnLineSegment(point);

			Assert::AreEqual(3.f, result.x);
			Assert::AreEqual(4.f, result.y);
		}

		TEST_METHOD(Line2i_IsPointAboveLine_PointAbove_ReturnsTrue)
		{
			Line2i line({ 1, 2 }, { 3, 4 });
			Vector2f point({ 1.f, 3.f });

			Assert::IsTrue(line.IsPointAboveLine(point));
		}

		TEST_METHOD(Line2i_IsPointAboveLine_PointBelow_ReturnsFalse)
		{
			Line2i line({ 1, 2 }, { 3, 4 });
			Vector2f point({ 1.f, 1.f });

			Assert::IsFalse(line.IsPointAboveLine(point));
		}

		TEST_METHOD(Line2f_IsPointAboveLine_PointAbove_ReturnsTrue)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });
			Vector2f point({ 1.f, 3.f });

			Assert::IsTrue(line.IsPointAboveLine(point));
		}

		TEST_METHOD(Line2f_IsPointAboveLine_PointBelow_ReturnsFalse)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });
			Vector2f point({ 1.f, 1.f });

			Assert::IsFalse(line.IsPointAboveLine(point));
		}

		TEST_METHOD(Line2i_IntersectsPoint_PointOnLine_ReturnsTrue)
		{
			Line2i line({ 1, 2 }, { 3, 4 });
			Vector2f point({ 2.f, 3.f });

			Assert::IsTrue(line.IntersectsPoint(point));
		}

		TEST_METHOD(Line2i_IntersectsPoint_PointOffLine_ReturnsFalse)
		{
			Line2i line({ 1, 2 }, { 3, 4 });
			Vector2f point({ 2.f, 2.f });

			Assert::IsFalse(line.IntersectsPoint(point));
		}

		TEST_METHOD(Line2f_IntersectsPoint_PointOnLine_ReturnsTrue)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });
			Vector2f point({ 2.f, 3.f });

			Assert::IsTrue(line.IntersectsPoint(point));
		}

		TEST_METHOD(Line2f_IntersectsPoint_PointOffLine_ReturnsFalse)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });
			Vector2f point({ 2.f, 2.f });

			Assert::IsFalse(line.IntersectsPoint(point));
		}

		TEST_METHOD(SolveQuadratic_ValidCoefficients_ReturnsCorrectRoots)
		{
			float r1 = 0.f, r2 = 0.f;

			bool result = SolveQuadratic(1.f, -5.f, 6.f, r1, r2);

			Assert::IsTrue(result);

			// order might vary, so check both possibilities
			bool correct =
				(fabs(r1 - 2.f) < 0.0001f && fabs(r2 - 3.f) < 0.0001f) ||
				(fabs(r1 - 3.f) < 0.0001f && fabs(r2 - 2.f) < 0.0001f);

			Assert::IsTrue(correct);
		}

		TEST_METHOD(SolveQuadratic_OneRoot_ReturnsCorrectRoot)
		{
			float r1 = 0.f, r2 = 0.f;

			bool result = SolveQuadratic(1.f, -4.f, 4.f, r1, r2);

			Assert::IsTrue(result);
			Assert::IsTrue(fabs(r1 - 2.f) < 0.0001f);
			Assert::IsTrue(fabs(r2 - 2.f) < 0.0001f);
		}

		TEST_METHOD(SolveQuadratic_NoRealRoots_ReturnsFalse)
		{
			float r1 = 0.f, r2 = 0.f;

			bool result = SolveQuadratic(1.f, 0.f, 1.f, r1, r2);

			Assert::IsFalse(result);
		}

		TEST_METHOD(Line2i_GetXDist_ReturnsCorrectValue)
		{
			Line2i line({ 1, 2 }, { 3, 4 });

			Assert::AreEqual(2, GetXDist(line.start, line.end));
		}

		TEST_METHOD(Line2f_GetXDist_ReturnsCorrectValue)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });

			Assert::AreEqual(2.f, GetXDist(line.start, line.end));
		}

		TEST_METHOD(Line2i_GetYDist_ReturnsCorrectValue)
		{
			Line2i line({ 1, 2 }, { 3, 4 });

			Assert::AreEqual(2, GetYDist(line.start, line.end));
		}

		TEST_METHOD(Line2f_GetYDist_ReturnsCorrectValue)
		{
			Line2f line({ 1.f, 2.f }, { 3.f, 4.f });

			Assert::AreEqual(2.f, GetYDist(line.start, line.end));
		}
	};
}