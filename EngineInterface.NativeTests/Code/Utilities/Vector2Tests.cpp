#include "CppUnitTest.h"

#include <Utilities/Vector2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(Vector2Tests)
	{
	public:
		// =======================
		// Constructors
		// =======================

		TEST_METHOD(Vector2i_DefaultConstruction_DefaultsValues)
		{
			Vector2i vec;
			Assert::AreEqual(0, vec.x);
			Assert::AreEqual(0, vec.y);
		}

		TEST_METHOD(Vector2u_DefaultConstruction_DefaultsValues)
		{
			Vector2u vec;
			Assert::AreEqual(0u, vec.x);
			Assert::AreEqual(0u, vec.y);
		}

		TEST_METHOD(Vector2f_DefaultConstruction_DefaultsValues)
		{
			Vector2f vec;
			Assert::AreEqual(0.f, vec.x);
			Assert::AreEqual(0.f, vec.y);
		}

		TEST_METHOD(Vector2i_ValueConstruction_PopulatesValues)
		{
			Vector2i vec(1, 1);
			Assert::AreEqual(1, vec.x);
			Assert::AreEqual(1, vec.y);
		}

		TEST_METHOD(Vector2u_ValueConstruction_PopulatesValues)
		{
			Vector2u vec(1, 1);
			Assert::AreEqual(1u, vec.x);
			Assert::AreEqual(1u, vec.y);
		}

		TEST_METHOD(Vector2f_ValueConstruction_PopulatesValues)
		{
			Vector2f vec(1.f, 1.f);
			Assert::AreEqual(1.f, vec.x);
			Assert::AreEqual(1.f, vec.y);
		}

		TEST_METHOD(Vector2i_ValueConstructionWithNegatives_PopulatesValues)
		{
			Vector2i vec(-1, -1);
			Assert::AreEqual(-1, vec.x);
			Assert::AreEqual(-1, vec.y);
		}

		TEST_METHOD(Vector2f_ValueConstructionWithNegatives_PopulatesValues)
		{
			Vector2f vec(-1.f, -1.f);
			Assert::AreEqual(-1.f, vec.x);
			Assert::AreEqual(-1.f, vec.y);
		}

		TEST_METHOD(Vector2u_ValueConstructionWithNegativeInputs_UsesImplicitConversion)
		{
			Vector2u vec(-1, -1);
			Assert::AreEqual(static_cast<unsigned int>(-1), vec.x);
			Assert::AreEqual(static_cast<unsigned int>(-1), vec.y);
		}

		// =======================
		// Copy
		// =======================

		TEST_METHOD(Vector2i_CopyConstruction_CopiesValues)
		{
			Vector2i vec1(1, 1);
			Vector2i vec2(vec1);

			Assert::AreEqual(vec1.x, vec2.x);
			Assert::AreEqual(vec1.y, vec2.y);
		}

		TEST_METHOD(Vector2u_CopyConstruction_CopiesValues)
		{
			Vector2u vec1(1, 1);
			Vector2u vec2(vec1);

			Assert::AreEqual(vec1.x, vec2.x);
			Assert::AreEqual(vec1.y, vec2.y);
		}

		TEST_METHOD(Vector2f_CopyConstruction_CopiesValues)
		{
			Vector2f vec1(1.f, 1.f);
			Vector2f vec2(vec1);

			Assert::AreEqual(vec1.x, vec2.x);
			Assert::AreEqual(vec1.y, vec2.y);
		}

		// =======================
		// Equality
		// =======================

		TEST_METHOD(Vector2i_EqualityOperator_AreEqual)
		{
			Vector2i vec1(1, 1);
			Vector2i vec2(1, 1);

			Assert::IsTrue(vec1 == vec2);
		}

		TEST_METHOD(Vector2u_EqualityOperator_AreEqual)
		{
			Vector2u vec1(1, 1);
			Vector2u vec2(1, 1);

			Assert::IsTrue(vec1 == vec2);
		}

		TEST_METHOD(Vector2f_EqualityOperator_AreEqual)
		{
			Vector2f vec1(1.f, 1.f);
			Vector2f vec2(1.f, 1.f);

			Assert::IsTrue(vec1 == vec2);
		}

		TEST_METHOD(Vector2i_InequalityOperator_AreNotEqual)
		{
			Vector2i vec1(1, 1);
			Vector2i vec2(2, 2);

			Assert::IsTrue(vec1 != vec2);
		}

		TEST_METHOD(Vector2u_InequalityOperator_AreNotEqual)
		{
			Vector2u vec1(1, 1);
			Vector2u vec2(2, 2);

			Assert::IsTrue(vec1 != vec2);
		}

		TEST_METHOD(Vector2f_InequalityOperator_AreNotEqual)
		{
			Vector2f vec1(1.f, 1.f);
			Vector2f vec2(2.f, 2.f);

			Assert::IsTrue(vec1 != vec2);
		}

		TEST_METHOD(Vector2i_InequalityOperator_DifferentX_AreNotEqual)
		{
			Vector2i vec1(1, 1);
			Vector2i vec2(2, 1);

			Assert::IsTrue(vec1 != vec2);
		}

		TEST_METHOD(Vector2i_InequalityOperator_DifferentY_AreNotEqual)
		{
			Vector2i vec1(1, 1);
			Vector2i vec2(1, 2);

			Assert::IsTrue(vec1 != vec2);
		}

		// =======================
		// Indexing
		// =======================

		TEST_METHOD(Vector2i_IndexOperator_GetsCorrectComponent)
		{
			Vector2i vec(1, 2);

			Assert::AreEqual(vec.x, vec[0]);
			Assert::AreEqual(vec.y, vec[1]);
		}

		TEST_METHOD(Vector2u_IndexOperator_GetsCorrectComponent)
		{
			Vector2u vec(1, 2);

			Assert::AreEqual(vec.x, vec[0]);
			Assert::AreEqual(vec.y, vec[1]);
		}

		TEST_METHOD(Vector2f_IndexOperator_GetsCorrectComponent)
		{
			Vector2f vec(1.f, 2.f);

			Assert::AreEqual(vec.x, vec[0]);
			Assert::AreEqual(vec.y, vec[1]);
		}

		TEST_METHOD(Vector2i_IndexOperator_SetsCorrectComponent)
		{
			Vector2i vec(1, 2);

			vec[0] = 10;
			vec[1] = 20;

			Assert::AreEqual(10, vec.x);
			Assert::AreEqual(20, vec.y);
		}

		TEST_METHOD(Vector2i_ConstIndexOperator_GetsCorrectComponent)
		{
			const Vector2i vec(1, 2);

			Assert::AreEqual(vec.x, vec[0]);
			Assert::AreEqual(vec.y, vec[1]);
		}

		TEST_METHOD(Vector2i_IndexOperator_InvalidIndex_ThrowsOutOfRange)
		{
			Vector2i vec(1, 2);

			Assert::ExpectException<std::out_of_range>([&]()
				{
					vec[2];
				});
		}

		TEST_METHOD(Vector2i_ConstIndexOperator_InvalidIndex_ThrowsOutOfRange)
		{
			const Vector2i vec(1, 2);

			Assert::ExpectException<std::out_of_range>([&]()
				{
					vec[2];
				});
		}

		// =======================
		// Compound assignment (vector)
		// =======================

		TEST_METHOD(Vector2i_AddAssignVector_PopulatesValues)
		{
			Vector2i vec1(1, 1);
			Vector2i vec2(1, 1);

			vec1 += vec2;

			Assert::AreEqual(2, vec1.x);
			Assert::AreEqual(2, vec1.y);
		}

		TEST_METHOD(Vector2u_AddAssignVector_PopulatesValues)
		{
			Vector2u vec1(1, 1);
			Vector2u vec2(1, 1);

			vec1 += vec2;

			Assert::AreEqual(2u, vec1.x);
			Assert::AreEqual(2u, vec1.y);
		}

		TEST_METHOD(Vector2f_AddAssignVector_PopulatesValues)
		{
			Vector2f vec1(1.f, 1.f);
			Vector2f vec2(1.f, 1.f);

			vec1 += vec2;

			Assert::AreEqual(2.f, vec1.x);
			Assert::AreEqual(2.f, vec1.y);
		}

		TEST_METHOD(Vector2i_SubAssignVector_PopulatesValues)
		{
			Vector2i vec1(3, 3);
			Vector2i vec2(1, 1);

			vec1 -= vec2;

			Assert::AreEqual(2, vec1.x);
			Assert::AreEqual(2, vec1.y);
		}

		TEST_METHOD(Vector2u_SubAssignVector_PopulatesValues)
		{
			Vector2u vec1(3, 3);
			Vector2u vec2(1, 1);

			vec1 -= vec2;

			Assert::AreEqual(2u, vec1.x);
			Assert::AreEqual(2u, vec1.y);
		}

		TEST_METHOD(Vector2f_SubAssignVector_PopulatesValues)
		{
			Vector2f vec1(3.f, 3.f);
			Vector2f vec2(1.f, 1.f);

			vec1 -= vec2;

			Assert::AreEqual(2.f, vec1.x);
			Assert::AreEqual(2.f, vec1.y);
		}

		TEST_METHOD(Vector2i_MulAssignVector_PopulatesValues)
		{
			Vector2i vec1(2, 2);
			Vector2i vec2(2, 2);

			vec1 *= vec2;

			Assert::AreEqual(4, vec1.x);
			Assert::AreEqual(4, vec1.y);
		}

		TEST_METHOD(Vector2u_MulAssignVector_PopulatesValues)
		{
			Vector2u vec1(2, 2);
			Vector2u vec2(2, 2);

			vec1 *= vec2;

			Assert::AreEqual(4u, vec1.x);
			Assert::AreEqual(4u, vec1.y);
		}

		TEST_METHOD(Vector2f_MulAssignVector_PopulatesValues)
		{
			Vector2f vec1(2.f, 2.f);
			Vector2f vec2(2.f, 2.f);

			vec1 *= vec2;

			Assert::AreEqual(4.f, vec1.x);
			Assert::AreEqual(4.f, vec1.y);
		}

		TEST_METHOD(Vector2i_DivAssignVector_PopulatesValues)
		{
			Vector2i vec1(2, 2);
			Vector2i vec2(2, 2);

			vec1 /= vec2;

			Assert::AreEqual(1, vec1.x);
			Assert::AreEqual(1, vec1.y);
		}

		TEST_METHOD(Vector2u_DivAssignVector_PopulatesValues)
		{
			Vector2u vec1(2, 2);
			Vector2u vec2(2, 2);

			vec1 /= vec2;

			Assert::AreEqual(1u, vec1.x);
			Assert::AreEqual(1u, vec1.y);
		}

		TEST_METHOD(Vector2f_DivAssignVector_PopulatesValues)
		{
			Vector2f vec1(2.f, 2.f);
			Vector2f vec2(2.f, 2.f);

			vec1 /= vec2;

			Assert::AreEqual(1.f, vec1.x);
			Assert::AreEqual(1.f, vec1.y);
		}

		TEST_METHOD(Vector2i_MulAssignVector_ByZero_ZeroesValues)
		{
			Vector2i vec1(2, 2);
			Vector2i vec2(0, 0);

			vec1 *= vec2;

			Assert::AreEqual(0, vec1.x);
			Assert::AreEqual(0, vec1.y);
		}

		TEST_METHOD(Vector2u_MulAssignVector_ByZero_ZeroesValues)
		{
			Vector2u vec1(2, 2);
			Vector2u vec2(0, 0);

			vec1 *= vec2;

			Assert::AreEqual(0u, vec1.x);
			Assert::AreEqual(0u, vec1.y);
		}

		TEST_METHOD(Vector2f_MulAssignVector_ByZero_ZeroesValues)
		{
			Vector2f vec1(2.f, 2.f);
			Vector2f vec2(0.f, 0.f);

			vec1 *= vec2;

			Assert::AreEqual(0.f, vec1.x);
			Assert::AreEqual(0.f, vec1.y);
		}

		// =======================
		// Compound assignment (scalar)
		// =======================

		TEST_METHOD(Vector2i_MulAssignScalar_PopulatesValues)
		{
			Vector2i vec(2, 2);

			vec *= 2;

			Assert::AreEqual(4, vec.x);
			Assert::AreEqual(4, vec.y);
		}

		TEST_METHOD(Vector2u_MulAssignScalar_PopulatesValues)
		{
			Vector2u vec(2, 2);

			vec *= 2u;

			Assert::AreEqual(4u, vec.x);
			Assert::AreEqual(4u, vec.y);
		}

		TEST_METHOD(Vector2f_MulAssignScalar_PopulatesValues)
		{
			Vector2f vec(2.f, 2.f);

			vec *= 2.f;

			Assert::AreEqual(4.f, vec.x);
			Assert::AreEqual(4.f, vec.y);
		}

		TEST_METHOD(Vector2i_DivAssignScalar_PopulatesValues)
		{
			Vector2i vec(2, 2);

			vec /= 2;

			Assert::AreEqual(1, vec.x);
			Assert::AreEqual(1, vec.y);
		}

		TEST_METHOD(Vector2u_DivAssignScalar_PopulatesValues)
		{
			Vector2u vec(2, 2);

			vec /= 2u;

			Assert::AreEqual(1u, vec.x);
			Assert::AreEqual(1u, vec.y);
		}

		TEST_METHOD(Vector2f_DivAssignScalar_PopulatesValues)
		{
			Vector2f vec(2.f, 2.f);

			vec /= 2.f;

			Assert::AreEqual(1.f, vec.x);
			Assert::AreEqual(1.f, vec.y);
		}

		TEST_METHOD(Vector2i_MulAssignScalar_ByZero_ZeroesValues)
		{
			Vector2i vec(2, 2);

			vec *= 0;

			Assert::AreEqual(0, vec.x);
			Assert::AreEqual(0, vec.y);
		}

		TEST_METHOD(Vector2u_MulAssignScalar_ByZero_ZeroesValues)
		{
			Vector2u vec(2, 2);

			vec *= 0u;

			Assert::AreEqual(0u, vec.x);
			Assert::AreEqual(0u, vec.y);
		}

		TEST_METHOD(Vector2f_MulAssignScalar_ByZero_ZeroesValues)
		{
			Vector2f vec(2.f, 2.f);

			vec *= 0.f;

			Assert::AreEqual(0.f, vec.x);
			Assert::AreEqual(0.f, vec.y);
		}

		// =======================
		// Operators (vector)
		// =======================

		TEST_METHOD(Vector2i_AddVector_PopulatesValues)
		{
			Vector2i vec1(1, 1);
			Vector2i vec2(1, 1);

			Vector2i vec3 = vec1 + vec2;

			Assert::AreEqual(2, vec3.x);
			Assert::AreEqual(2, vec3.y);
		}

		TEST_METHOD(Vector2u_AddVector_PopulatesValues)
		{
			Vector2u vec1(1, 1);
			Vector2u vec2(1, 1);

			Vector2u vec3 = vec1 + vec2;

			Assert::AreEqual(2u, vec3.x);
			Assert::AreEqual(2u, vec3.y);
		}

		TEST_METHOD(Vector2f_AddVector_PopulatesValues)
		{
			Vector2f vec1(1.f, 1.f);
			Vector2f vec2(1.f, 1.f);

			Vector2f vec3 = vec1 + vec2;

			Assert::AreEqual(2.f, vec3.x);
			Assert::AreEqual(2.f, vec3.y);
		}

		TEST_METHOD(Vector2i_AddVector_DoesNotModifyOperands)
		{
			Vector2i vec1(1, 1);
			Vector2i vec2(1, 1);

			Vector2i vec3 = vec1 + vec2;

			Assert::AreEqual(1, vec1.x);
			Assert::AreEqual(1, vec1.y);
			Assert::AreEqual(1, vec2.x);
			Assert::AreEqual(1, vec2.y);
			Assert::AreEqual(2, vec3.x);
			Assert::AreEqual(2, vec3.y);
		}

		TEST_METHOD(Vector2i_SubVector_PopulatesValues)
		{
			Vector2i vec1(3, 3);
			Vector2i vec2(1, 1);

			Vector2i vec3 = vec1 - vec2;

			Assert::AreEqual(2, vec3.x);
			Assert::AreEqual(2, vec3.y);
		}

		TEST_METHOD(Vector2u_SubVector_PopulatesValues)
		{
			Vector2u vec1(3, 3);
			Vector2u vec2(1, 1);

			Vector2u vec3 = vec1 - vec2;

			Assert::AreEqual(2u, vec3.x);
			Assert::AreEqual(2u, vec3.y);
		}

		TEST_METHOD(Vector2f_SubVector_PopulatesValues)
		{
			Vector2f vec1(3.f, 3.f);
			Vector2f vec2(1.f, 1.f);

			Vector2f vec3 = vec1 - vec2;

			Assert::AreEqual(2.f, vec3.x);
			Assert::AreEqual(2.f, vec3.y);
		}

		TEST_METHOD(Vector2i_SubVector_DoesNotModifyOperands)
		{
			Vector2i vec1(3, 3);
			Vector2i vec2(1, 1);

			Vector2i vec3 = vec1 - vec2;

			Assert::AreEqual(3, vec1.x);
			Assert::AreEqual(3, vec1.y);
			Assert::AreEqual(1, vec2.x);
			Assert::AreEqual(1, vec2.y);
			Assert::AreEqual(2, vec3.x);
			Assert::AreEqual(2, vec3.y);
		}

		TEST_METHOD(Vector2i_MulVector_PopulatesValues)
		{
			Vector2i vec1(2, 2);
			Vector2i vec2(2, 2);

			Vector2i vec3 = vec1 * vec2;

			Assert::AreEqual(4, vec3.x);
			Assert::AreEqual(4, vec3.y);
		}

		TEST_METHOD(Vector2u_MulVector_PopulatesValues)
		{
			Vector2u vec1(2, 2);
			Vector2u vec2(2, 2);

			Vector2u vec3 = vec1 * vec2;

			Assert::AreEqual(4u, vec3.x);
			Assert::AreEqual(4u, vec3.y);
		}

		TEST_METHOD(Vector2f_MulVector_PopulatesValues)
		{
			Vector2f vec1(2.f, 2.f);
			Vector2f vec2(2.f, 2.f);

			Vector2f vec3 = vec1 * vec2;

			Assert::AreEqual(4.f, vec3.x);
			Assert::AreEqual(4.f, vec3.y);
		}

		TEST_METHOD(Vector2i_MulVector_ByZero_ZeroesValues)
		{
			Vector2i vec1(2, 2);
			Vector2i vec2(0, 0);

			Vector2i vec3 = vec1 * vec2;

			Assert::AreEqual(0, vec3.x);
			Assert::AreEqual(0, vec3.y);
		}

		TEST_METHOD(Vector2u_MulVector_ByZero_ZeroesValues)
		{
			Vector2u vec1(2, 2);
			Vector2u vec2(0, 0);

			Vector2u vec3 = vec1 * vec2;

			Assert::AreEqual(0u, vec3.x);
			Assert::AreEqual(0u, vec3.y);
		}

		TEST_METHOD(Vector2f_MulVector_ByZero_ZeroesValues)
		{
			Vector2f vec1(2.f, 2.f);
			Vector2f vec2(0.f, 0.f);

			Vector2f vec3 = vec1 * vec2;

			Assert::AreEqual(0.f, vec3.x);
			Assert::AreEqual(0.f, vec3.y);
		}

		TEST_METHOD(Vector2i_MulVector_DoesNotModifyOperands)
		{
			Vector2i vec1(2, 2);
			Vector2i vec2(3, 3);

			Vector2i vec3 = vec1 * vec2;

			Assert::AreEqual(2, vec1.x);
			Assert::AreEqual(2, vec1.y);
			Assert::AreEqual(3, vec2.x);
			Assert::AreEqual(3, vec2.y);
			Assert::AreEqual(6, vec3.x);
			Assert::AreEqual(6, vec3.y);
		}

		TEST_METHOD(Vector2i_DivVector_PopulatesValues)
		{
			Vector2i vec1(2, 2);
			Vector2i vec2(2, 2);

			Vector2i vec3 = vec1 / vec2;

			Assert::AreEqual(1, vec3.x);
			Assert::AreEqual(1, vec3.y);
		}

		TEST_METHOD(Vector2u_DivVector_PopulatesValues)
		{
			Vector2u vec1(2, 2);
			Vector2u vec2(2, 2);

			Vector2u vec3 = vec1 / vec2;

			Assert::AreEqual(1u, vec3.x);
			Assert::AreEqual(1u, vec3.y);
		}

		TEST_METHOD(Vector2f_DivVector_PopulatesValues)
		{
			Vector2f vec1(2.f, 2.f);
			Vector2f vec2(2.f, 2.f);

			Vector2f vec3 = vec1 / vec2;

			Assert::AreEqual(1.f, vec3.x);
			Assert::AreEqual(1.f, vec3.y);
		}

		TEST_METHOD(Vector2i_DivVector_DoesNotModifyOperands)
		{
			Vector2i vec1(4, 4);
			Vector2i vec2(2, 2);

			Vector2i vec3 = vec1 / vec2;

			Assert::AreEqual(4, vec1.x);
			Assert::AreEqual(4, vec1.y);
			Assert::AreEqual(2, vec2.x);
			Assert::AreEqual(2, vec2.y);
			Assert::AreEqual(2, vec3.x);
			Assert::AreEqual(2, vec3.y);
		}

		// =======================
		// Operators (scalar)
		// =======================

		TEST_METHOD(Vector2i_MulScalar_PopulatesValues)
		{
			Vector2i vec1(2, 2);

			Vector2i vec2 = vec1 * 2;

			Assert::AreEqual(4, vec2.x);
			Assert::AreEqual(4, vec2.y);
		}

		TEST_METHOD(Vector2u_MulScalar_PopulatesValues)
		{
			Vector2u vec1(2, 2);

			Vector2u vec2 = vec1 * 2u;

			Assert::AreEqual(4u, vec2.x);
			Assert::AreEqual(4u, vec2.y);
		}

		TEST_METHOD(Vector2f_MulScalar_PopulatesValues)
		{
			Vector2f vec1(2.f, 2.f);

			Vector2f vec2 = vec1 * 2.f;

			Assert::AreEqual(4.f, vec2.x);
			Assert::AreEqual(4.f, vec2.y);
		}

		TEST_METHOD(Vector2i_MulScalar_ByZero_ZeroesValues)
		{
			Vector2i vec1(2, 2);

			Vector2i vec2 = vec1 * 0;

			Assert::AreEqual(0, vec2.x);
			Assert::AreEqual(0, vec2.y);
		}

		TEST_METHOD(Vector2u_MulScalar_ByZero_ZeroesValues)
		{
			Vector2u vec1(2, 2);

			Vector2u vec2 = vec1 * 0u;

			Assert::AreEqual(0u, vec2.x);
			Assert::AreEqual(0u, vec2.y);
		}

		TEST_METHOD(Vector2f_MulScalar_ByZero_ZeroesValues)
		{
			Vector2f vec1(2.f, 2.f);

			Vector2f vec2 = vec1 * 0.f;

			Assert::AreEqual(0.f, vec2.x);
			Assert::AreEqual(0.f, vec2.y);
		}

		TEST_METHOD(Vector2i_MulScalar_DoesNotModifyOperand)
		{
			Vector2i vec1(2, 2);

			Vector2i vec2 = vec1 * 3;

			Assert::AreEqual(2, vec1.x);
			Assert::AreEqual(2, vec1.y);
			Assert::AreEqual(6, vec2.x);
			Assert::AreEqual(6, vec2.y);
		}

		TEST_METHOD(Vector2i_DivScalar_PopulatesValues)
		{
			Vector2i vec1(2, 2);

			Vector2i vec2 = vec1 / 2;

			Assert::AreEqual(1, vec2.x);
			Assert::AreEqual(1, vec2.y);
		}

		TEST_METHOD(Vector2u_DivScalar_PopulatesValues)
		{
			Vector2u vec1(2, 2);

			Vector2u vec2 = vec1 / 2u;

			Assert::AreEqual(1u, vec2.x);
			Assert::AreEqual(1u, vec2.y);
		}

		TEST_METHOD(Vector2f_DivScalar_PopulatesValues)
		{
			Vector2f vec1(2.f, 2.f);

			Vector2f vec2 = vec1 / 2.f;

			Assert::AreEqual(1.f, vec2.x);
			Assert::AreEqual(1.f, vec2.y);
		}

		TEST_METHOD(Vector2i_DivScalar_DoesNotModifyOperand)
		{
			Vector2i vec1(4, 4);

			Vector2i vec2 = vec1 / 2;

			Assert::AreEqual(4, vec1.x);
			Assert::AreEqual(4, vec1.y);
			Assert::AreEqual(2, vec2.x);
			Assert::AreEqual(2, vec2.y);
		}

		// =======================
		// Member functions
		// =======================

		TEST_METHOD(Vector2i_Clamp_WhenBelowLowerBound_ClampsUp)
		{
			Vector2i min(2, 2);
			Vector2i max(4, 4);
			Vector2i vec(0, 0);

			Vector2i result = vec.Clamp(min, max);

			Assert::AreEqual(2, result.x);
			Assert::AreEqual(2, result.y);
		}

		TEST_METHOD(Vector2i_Clamp_WhenAboveUpperBound_ClampsDown)
		{
			Vector2i min(2, 2);
			Vector2i max(4, 4);
			Vector2i vec(6, 6);

			Vector2i result = vec.Clamp(min, max);

			Assert::AreEqual(4, result.x);
			Assert::AreEqual(4, result.y);
		}

		TEST_METHOD(Vector2i_Clamp_WhenWithinBounds_ReturnsUnchanged)
		{
			Vector2i min(2, 2);
			Vector2i max(4, 4);
			Vector2i vec(3, 3);

			Vector2i result = vec.Clamp(min, max);

			Assert::AreEqual(3, result.x);
			Assert::AreEqual(3, result.y);
		}

		TEST_METHOD(Vector2u_Clamp_ClampsBetweenBounds)
		{
			Vector2u min(2, 2);
			Vector2u max(4, 4);
			Vector2u vec(6, 6);

			Vector2u result = vec.Clamp(min, max);

			Assert::AreEqual(4u, result.x);
			Assert::AreEqual(4u, result.y);
		}

		TEST_METHOD(Vector2f_Clamp_ClampsBetweenBounds)
		{
			Vector2f min(2.f, 2.f);
			Vector2f max(4.f, 4.f);
			Vector2f vec(6.f, 6.f);

			Vector2f result = vec.Clamp(min, max);

			Assert::AreEqual(4.f, result.x);
			Assert::AreEqual(4.f, result.y);
		}

		TEST_METHOD(Vector2i_LengthSquared_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2i vec(2, 3);

			Assert::AreEqual(13, vec.LengthSquared());
		}

		TEST_METHOD(Vector2u_LengthSquared_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2u vec(2, 3);

			Assert::AreEqual(13u, vec.LengthSquared());
		}

		TEST_METHOD(Vector2f_LengthSquared_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2f vec(2.f, 3.f);

			Assert::AreEqual(13.f, vec.LengthSquared());
		}

		TEST_METHOD(Vector2i_Dot_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2i vec1(2, 3);
			Vector2i vec2(4, 5);

			Assert::AreEqual(23, vec1.Dot(vec2));
		}

		TEST_METHOD(Vector2u_Dot_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2u vec1(2, 3);
			Vector2u vec2(4, 5);

			Assert::AreEqual(23u, vec1.Dot(vec2));
		}

		TEST_METHOD(Vector2f_Dot_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2f vec1(2.f, 3.f);
			Vector2f vec2(4.f, 5.f);

			Assert::AreEqual(23.f, vec1.Dot(vec2));
		}

		TEST_METHOD(Vector2i_Distance_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2i vec1(4, 6);
			Vector2i vec2(1, 2);

			Assert::AreEqual(5, vec1.Distance(vec2));
		}

		TEST_METHOD(Vector2u_Distance_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2u vec1(1, 2);
			Vector2u vec2(4, 6);

			Assert::AreEqual(5u, vec1.Distance(vec2));
		}

		TEST_METHOD(Vector2f_Distance_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2f vec1(4.f, 6.f);
			Vector2f vec2(1.f, 2.f);

			Assert::AreEqual(5.f, vec1.Distance(vec2), 0.0001f);
		}

		TEST_METHOD(Vector2i_Length_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2i vec(3, 4);

			Assert::AreEqual(5, vec.Length());
		}

		TEST_METHOD(Vector2u_Length_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2u vec(3, 4);

			Assert::AreEqual(5u, vec.Length());
		}

		TEST_METHOD(Vector2f_Length_NonSymmetric_ReturnsCorrectValue)
		{
			Vector2f vec(3.f, 4.f);

			Assert::AreEqual(5.f, vec.Length(), 0.0001f);
		}

		TEST_METHOD(Vector2i_IsBetween_WhenProjectionBetweenEndpoints_ReturnsTrue)
		{
			Vector2i min(2, 2);
			Vector2i max(4, 4);
			Vector2i vec(3, 3);

			Assert::IsTrue(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector2i_IsBetween_WhenOutsideEndpoints_ReturnsFalse)
		{
			Vector2i min(2, 2);
			Vector2i max(4, 4);
			Vector2i vec(6, 6);

			Assert::IsFalse(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector2i_IsBetween_NonCollinear_ReturnsFalse)
		{
			Vector2i a(2, 2);
			Vector2i b(4, 4);
			Vector2i vec(1, 4);

			Assert::IsFalse(vec.IsBetween(a, b));
		}

		TEST_METHOD(Vector2i_IsBetween_NonCollinear_MayReturnTrue)
		{
			Vector2i a(2, 2);
			Vector2i b(4, 4);
			Vector2i vec(3, 4);

			Assert::IsTrue(vec.IsBetween(a, b));
		}

		TEST_METHOD(Vector2i_IsBetween_AtEndpoint_ReturnsTrue)
		{
			Vector2i a(2, 2);
			Vector2i b(4, 4);

			Assert::IsTrue(a.IsBetween(a, b));
			Assert::IsTrue(b.IsBetween(a, b));
		}

		TEST_METHOD(Vector2u_IsBetween_WhenProjectionBetweenEndpoints_MayFailDueToUnsignedUnderflow)
		{
			Vector2u min(2, 2);
			Vector2u max(4, 4);
			Vector2u vec(3, 3);

			Assert::IsFalse(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector2u_IsBetween_WhenOutsideEndpoints_ReturnsFalse)
		{
			Vector2u min(2, 2);
			Vector2u max(4, 4);
			Vector2u vec(6, 6);

			Assert::IsFalse(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector2f_IsBetween_WhenProjectionBetweenEndpoints_ReturnsTrue)
		{
			Vector2f min(2.f, 2.f);
			Vector2f max(4.f, 4.f);
			Vector2f vec(3.f, 3.f);

			Assert::IsTrue(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector2f_IsBetween_WhenOutsideEndpoints_ReturnsFalse)
		{
			Vector2f min(2.f, 2.f);
			Vector2f max(4.f, 4.f);
			Vector2f vec(6.f, 6.f);

			Assert::IsFalse(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector2f_Normalize_ReturnsUnitVector)
		{
			Vector2f vec(3.f, 4.f);

			Vector2f result = vec.Normalize();

			Assert::AreEqual(0.6f, result.x, 0.0001f);
			Assert::AreEqual(0.8f, result.y, 0.0001f);
			Assert::AreEqual(1.f, result.Length(), 0.0001f);
		}
	};
}