#include "CppUnitTest.h"

#include <Utilities/Vector3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(Vector3Tests)
	{
	public:

		// ======================================================
		// Constructor
		// ======================================================

		TEST_METHOD(Vector3i_DefaultConstruction_DefaultsValues)
		{
			Vector3i vec;
			Assert::AreEqual(0, vec.x);
			Assert::AreEqual(0, vec.y);
			Assert::AreEqual(0, vec.z);
		}

		TEST_METHOD(Vector3u_DefaultConstruction_DefaultsValues)
		{
			Vector3u vec;
			Assert::AreEqual(0u, vec.x);
			Assert::AreEqual(0u, vec.y);
			Assert::AreEqual(0u, vec.z);
		}

		TEST_METHOD(Vector3f_DefaultConstruction_DefaultsValues)
		{
			Vector3f vec;
			Assert::AreEqual(0.f, vec.x);
			Assert::AreEqual(0.f, vec.y);
			Assert::AreEqual(0.f, vec.z);
		}

		TEST_METHOD(Vector3i_ValueConstruction_PopulatesValues)
		{
			Vector3i vec(1, 1, 1);
			Assert::AreEqual(1, vec.x);
			Assert::AreEqual(1, vec.y);
			Assert::AreEqual(1, vec.z);
		}

		TEST_METHOD(Vector3u_ValueConstruction_PopulatesValues)
		{
			Vector3u vec(1, 1, 1);
			Assert::AreEqual(1u, vec.x);
			Assert::AreEqual(1u, vec.y);
			Assert::AreEqual(1u, vec.z);
		}

		TEST_METHOD(Vector3f_ValueConstruction_PopulatesValues)
		{
			Vector3f vec(1.f, 1.f, 1.f);
			Assert::AreEqual(1.f, vec.x);
			Assert::AreEqual(1.f, vec.y);
		}

		TEST_METHOD(Vector3i_ValueConstructionWithNegatives_PopulatesValues)
		{
			Vector3i vec(-1, -1, -1);
			Assert::AreEqual(-1, vec.x);
			Assert::AreEqual(-1, vec.y);
			Assert::AreEqual(-1, vec.z);
		}

		TEST_METHOD(Vector3f_ValueConstructionWithNegatives_PopulatesValues)
		{
			Vector3f vec(-1.f, -1.f, -1.f);
			Assert::AreEqual(-1.f, vec.x);
			Assert::AreEqual(-1.f, vec.y);
			Assert::AreEqual(-1.f, vec.z);
		}

		TEST_METHOD(Vector3u_ValueConstructionWithNegativeInputs_UsesImplicitConversion)
		{
			Vector3u vec(-1, -1, -1);
			Assert::AreEqual(static_cast<unsigned int>(-1), vec.x);
			Assert::AreEqual(static_cast<unsigned int>(-1), vec.y);
			Assert::AreEqual(static_cast<unsigned int>(-1), vec.z);
		}


		TEST_METHOD(Vector3i_CopyConstruction_CopiesValues)
		{
			Vector3i vec1(1, 1, 1);
			Vector3i vec2(vec1);

			Assert::AreEqual(vec1.x, vec2.x);
			Assert::AreEqual(vec1.y, vec2.y);
			Assert::AreEqual(vec1.z, vec2.z);
		}

		TEST_METHOD(Vector3u_CopyConstruction_CopiesValues)
		{
			Vector3u vec1(1, 1, 1);
			Vector3u vec2(vec1);

			Assert::AreEqual(vec1.x, vec2.x);
			Assert::AreEqual(vec1.y, vec2.y);
			Assert::AreEqual(vec1.z, vec2.z);
		}

		TEST_METHOD(Vector3f_CopyConstruction_CopiesValues)
		{
			Vector3f vec1(1.f, 1.f, 1.f);
			Vector3f vec2(vec1);

			Assert::AreEqual(vec1.x, vec2.x);
			Assert::AreEqual(vec1.y, vec2.y);
			Assert::AreEqual(vec1.z, vec2.z);
		}


		// ======================================================
		// Operators
		// ======================================================

		TEST_METHOD(Vector3i_EqualityOperator_AreEqual)
		{
			Vector3i vec1(1, 1, 1);
			Vector3i vec2(1, 1, 1);

			Assert::IsTrue(vec1 == vec2);
		}

		TEST_METHOD(Vector3u_EqualityOperator_AreEqual)
		{
			Vector3u vec1(1, 1, 1);
			Vector3u vec2(1, 1, 1);

			Assert::IsTrue(vec1 == vec2);
		}

		TEST_METHOD(Vector3f_EqualityOperator_AreEqual)
		{
			Vector3f vec1(1.f, 1.f, 1.f);
			Vector3f vec2(1.f, 1.f, 1.f);

			Assert::IsTrue(vec1 == vec2);
		}

		TEST_METHOD(Vector3i_InequalityOperator_AreNotEqual)
		{
			Vector3i vec1(1, 1, 1);
			Vector3i vec2(2, 2, 2);

			Assert::IsTrue(vec1 != vec2);
		}

		TEST_METHOD(Vector3u_InequalityOperator_AreNotEqual)
		{
			Vector3u vec1(1, 1, 1);
			Vector3u vec2(2, 2, 2);

			Assert::IsTrue(vec1 != vec2);
		}

		TEST_METHOD(Vector3f_InequalityOperator_AreNotEqual)
		{
			Vector3f vec1(1.f, 1.f, 1.f);
			Vector3f vec2(2.f, 2.f, 2.f);

			Assert::IsTrue(vec1 != vec2);
		}

		TEST_METHOD(Vector3i_InequalityOperator_DifferentX_AreNotEqual)
		{
			Vector3i vec1(1, 1, 1);
			Vector3i vec2(2, 1, 1);

			Assert::IsTrue(vec1 != vec2);
		}

		TEST_METHOD(Vector3i_InequalityOperator_DifferentY_AreNotEqual)
		{
			Vector3i vec1(1, 1, 1);
			Vector3i vec2(1, 2, 1);

			Assert::IsTrue(vec1 != vec2);
		}

		TEST_METHOD(Vector3i_InequalityOperator_DifferentZ_AreNotEqual)
		{
			Vector3i vec1(1, 1, 1);
			Vector3i vec2(1, 1, 2);

			Assert::IsTrue(vec1 != vec2);
		}


		TEST_METHOD(Vector3i_IndexOperator_GetsCorrectComponent)
		{
			Vector3i vec(1, 2, 3);

			Assert::AreEqual(vec.x, vec[0]);
			Assert::AreEqual(vec.y, vec[1]);
			Assert::AreEqual(vec.z, vec[2]);
		}

		TEST_METHOD(Vector3u_IndexOperator_GetsCorrectComponent)
		{
			Vector3u vec(1, 2, 3);

			Assert::AreEqual(vec.x, vec[0]);
			Assert::AreEqual(vec.y, vec[1]);
			Assert::AreEqual(vec.z, vec[2]);
		}

		TEST_METHOD(Vector3f_IndexOperator_GetsCorrectComponent)
		{
			Vector3f vec(1.f, 2.f, 3.f);

			Assert::AreEqual(vec.x, vec[0]);
			Assert::AreEqual(vec.y, vec[1]);
			Assert::AreEqual(vec.z, vec[2]);
		}

		TEST_METHOD(Vector3i_IndexOperator_SetsCorrectComponent)
		{
			Vector3i vec(1, 2, 3);

			vec[0] = 10;
			vec[1] = 20;
			vec[2] = 30;

			Assert::AreEqual(10, vec.x);
			Assert::AreEqual(20, vec.y);
			Assert::AreEqual(30, vec.z);
		}

		TEST_METHOD(Vector3i_ConstIndexOperator_GetsCorrectComponent)
		{
			const Vector3i vec(1, 2, 3);

			Assert::AreEqual(vec.x, vec[0]);
			Assert::AreEqual(vec.y, vec[1]);
			Assert::AreEqual(vec.z, vec[2]);
		}

		TEST_METHOD(Vector3i_IndexOperator_InvalidIndex_ThrowsOutOfRange)
		{
			Vector3i vec(1, 2, 3);

			Assert::ExpectException<std::out_of_range>([&]()
				{
					vec[3];
				});
		}

		TEST_METHOD(Vector3i_ConstIndexOperator_InvalidIndex_ThrowsOutOfRange)
		{
			const Vector3i vec(1, 2, 3);

			Assert::ExpectException<std::out_of_range>([&]()
				{
					vec[3];
				});
		}


		TEST_METHOD(Vector3i_AddAssignVector_PopulatesValues)
		{
			Vector3i vec1(1, 1, 1);
			Vector3i vec2(1, 1, 1);

			vec1 += vec2;

			Assert::AreEqual(2, vec1.x);
			Assert::AreEqual(2, vec1.y);
			Assert::AreEqual(2, vec1.z);
		}

		TEST_METHOD(Vector3u_AddAssignVector_PopulatesValues)
		{
			Vector3u vec1(1, 1, 1);
			Vector3u vec2(1, 1, 1);

			vec1 += vec2;

			Assert::AreEqual(2u, vec1.x);
			Assert::AreEqual(2u, vec1.y);
			Assert::AreEqual(2u, vec1.z);
		}

		TEST_METHOD(Vector3f_AddAssignVector_PopulatesValues)
		{
			Vector3f vec1(1.f, 1.f, 1.f);
			Vector3f vec2(1.f, 1.f, 1.f);

			vec1 += vec2;

			Assert::AreEqual(2.f, vec1.x);
			Assert::AreEqual(2.f, vec1.y);
			Assert::AreEqual(2.f, vec1.z);
		}

		TEST_METHOD(Vector3i_SubAssignVector_PopulatesValues)
		{
			Vector3i vec1(3, 3, 3);
			Vector3i vec2(1, 1, 1);

			vec1 -= vec2;

			Assert::AreEqual(2, vec1.x);
			Assert::AreEqual(2, vec1.y);
			Assert::AreEqual(2, vec1.z);
		}

		TEST_METHOD(Vector3u_SubAssignVector_PopulatesValues)
		{
			Vector3u vec1(3, 3, 3);
			Vector3u vec2(1, 1, 1);

			vec1 -= vec2;

			Assert::AreEqual(2u, vec1.x);
			Assert::AreEqual(2u, vec1.y);
			Assert::AreEqual(2u, vec1.z);
		}

		TEST_METHOD(Vector3f_SubAssignVector_PopulatesValues)
		{
			Vector3f vec1(3.f, 3.f, 3.f);
			Vector3f vec2(1.f, 1.f, 1.f);

			vec1 -= vec2;

			Assert::AreEqual(2.f, vec1.x);
			Assert::AreEqual(2.f, vec1.y);
			Assert::AreEqual(2.f, vec1.z);
		}

		TEST_METHOD(Vector3i_MulAssignVector_PopulatesValues)
		{
			Vector3i vec1(2, 2, 2);
			Vector3i vec2(2, 2, 2);

			vec1 *= vec2;

			Assert::AreEqual(4, vec1.x);
			Assert::AreEqual(4, vec1.y);
			Assert::AreEqual(4, vec1.z);
		}

		TEST_METHOD(Vector3u_MulAssignVector_PopulatesValues)
		{
			Vector3u vec1(2, 2, 2);
			Vector3u vec2(2, 2, 2);

			vec1 *= vec2;

			Assert::AreEqual(4u, vec1.x);
			Assert::AreEqual(4u, vec1.y);
			Assert::AreEqual(4u, vec1.z);
		}

		TEST_METHOD(Vector3f_MulAssignVector_PopulatesValues)
		{
			Vector3f vec1(2.f, 2.f, 2.f);
			Vector3f vec2(2.f, 2.f, 2.f);

			vec1 *= vec2;

			Assert::AreEqual(4.f, vec1.x);
			Assert::AreEqual(4.f, vec1.y);
			Assert::AreEqual(4.f, vec1.z);
		}

		TEST_METHOD(Vector3i_DivAssignVector_PopulatesValues)
		{
			Vector3i vec1(2, 2, 2);
			Vector3i vec2(2, 2, 2);

			vec1 /= vec2;

			Assert::AreEqual(1, vec1.x);
			Assert::AreEqual(1, vec1.y);
			Assert::AreEqual(1, vec1.z);
		}

		TEST_METHOD(Vector3u_DivAssignVector_PopulatesValues)
		{
			Vector3u vec1(2, 2, 2);
			Vector3u vec2(2, 2, 2);

			vec1 /= vec2;

			Assert::AreEqual(1u, vec1.x);
			Assert::AreEqual(1u, vec1.y);
			Assert::AreEqual(1u, vec1.z);
		}

		TEST_METHOD(Vector3f_DivAssignVector_PopulatesValues)
		{
			Vector3f vec1(2.f, 2.f, 2.f);
			Vector3f vec2(2.f, 2.f, 2.f);

			vec1 /= vec2;

			Assert::AreEqual(1.f, vec1.x);
			Assert::AreEqual(1.f, vec1.y);
			Assert::AreEqual(1.f, vec1.z);
		}

		TEST_METHOD(Vector3i_MulAssignVector_ByZero_ZeroesValues)
		{
			Vector3i vec1(2, 2, 2);
			Vector3i vec2(0, 0, 0);

			vec1 *= vec2;

			Assert::AreEqual(0, vec1.x);
			Assert::AreEqual(0, vec1.y);
			Assert::AreEqual(0, vec1.z);
		}

		TEST_METHOD(Vector3u_MulAssignVector_ByZero_ZeroesValues)
		{
			Vector3u vec1(2, 2, 2);
			Vector3u vec2(0, 0, 0);

			vec1 *= vec2;

			Assert::AreEqual(0u, vec1.x);
			Assert::AreEqual(0u, vec1.y);
			Assert::AreEqual(0u, vec1.z);
		}

		TEST_METHOD(Vector3f_MulAssignVector_ByZero_ZeroesValues)
		{
			Vector3f vec1(2.f, 2.f, 2.f);
			Vector3f vec2(0.f, 0.f, 0.f);

			vec1 *= vec2;

			Assert::AreEqual(0.f, vec1.x);
			Assert::AreEqual(0.f, vec1.y);
			Assert::AreEqual(0.f, vec1.z);
		}


		TEST_METHOD(Vector3i_MulAssignScalar_PopulatesValues)
		{
			Vector3i vec(2, 2, 2);

			vec *= 2;

			Assert::AreEqual(4, vec.x);
			Assert::AreEqual(4, vec.y);
			Assert::AreEqual(4, vec.z);
		}

		TEST_METHOD(Vector3u_MulAssignScalar_PopulatesValues)
		{
			Vector3u vec(2, 2, 2);

			vec *= 2u;

			Assert::AreEqual(4u, vec.x);
			Assert::AreEqual(4u, vec.y);
			Assert::AreEqual(4u, vec.z);
		}

		TEST_METHOD(Vector3f_MulAssignScalar_PopulatesValues)
		{
			Vector3f vec(2.f, 2.f, 2.f);

			vec *= 2.f;

			Assert::AreEqual(4.f, vec.x);
			Assert::AreEqual(4.f, vec.y);
			Assert::AreEqual(4.f, vec.z);
		}

		TEST_METHOD(Vector3i_DivAssignScalar_PopulatesValues)
		{
			Vector3i vec(2, 2, 2);

			vec /= 2;

			Assert::AreEqual(1, vec.x);
			Assert::AreEqual(1, vec.y);
			Assert::AreEqual(1, vec.z);
		}

		TEST_METHOD(Vector3u_DivAssignScalar_PopulatesValues)
		{
			Vector3u vec(2, 2, 2);

			vec /= 2u;

			Assert::AreEqual(1u, vec.x);
			Assert::AreEqual(1u, vec.y);
			Assert::AreEqual(1u, vec.z);
		}

		TEST_METHOD(Vector3f_DivAssignScalar_PopulatesValues)
		{
			Vector3f vec(2.f, 2.f, 2.f);

			vec /= 2.f;

			Assert::AreEqual(1.f, vec.x);
			Assert::AreEqual(1.f, vec.y);
			Assert::AreEqual(1.f, vec.z);
		}

		TEST_METHOD(Vector3i_MulAssignScalar_ByZero_ZeroesValues)
		{
			Vector3i vec(2, 2, 2);

			vec *= 0;

			Assert::AreEqual(0, vec.x);
			Assert::AreEqual(0, vec.y);
			Assert::AreEqual(0, vec.z);
		}

		TEST_METHOD(Vector3u_MulAssignScalar_ByZero_ZeroesValues)
		{
			Vector3u vec(2, 2, 2);

			vec *= 0u;

			Assert::AreEqual(0u, vec.x);
			Assert::AreEqual(0u, vec.y);
			Assert::AreEqual(0u, vec.z);
		}

		TEST_METHOD(Vector3f_MulAssignScalar_ByZero_ZeroesValues)
		{
			Vector3f vec(2.f, 2.f, 2.f);

			vec *= 0.f;

			Assert::AreEqual(0.f, vec.x);
			Assert::AreEqual(0.f, vec.y);
			Assert::AreEqual(0.f, vec.z);
		}


		TEST_METHOD(Vector3i_AddVector_PopulatesValues)
		{
			Vector3i vec1(1, 1, 1);
			Vector3i vec2(1, 1, 1);

			Vector3i vec3 = vec1 + vec2;

			Assert::AreEqual(2, vec3.x);
			Assert::AreEqual(2, vec3.y);
			Assert::AreEqual(2, vec3.z);
		}

		TEST_METHOD(Vector3u_AddVector_PopulatesValues)
		{
			Vector3u vec1(1, 1, 1);
			Vector3u vec2(1, 1, 1);

			Vector3u vec3 = vec1 + vec2;

			Assert::AreEqual(2u, vec3.x);
			Assert::AreEqual(2u, vec3.y);
			Assert::AreEqual(2u, vec3.z);
		}

		TEST_METHOD(Vector3f_AddVector_PopulatesValues)
		{
			Vector3f vec1(1.f, 1.f, 1.f);
			Vector3f vec2(1.f, 1.f, 1.f);

			Vector3f vec3 = vec1 + vec2;

			Assert::AreEqual(2.f, vec3.x);
			Assert::AreEqual(2.f, vec3.y);
			Assert::AreEqual(2.f, vec3.z);
		}

		TEST_METHOD(Vector3i_AddVector_DoesNotModifyOperands)
		{
			Vector3i vec1(1, 1, 1);
			Vector3i vec2(1, 1, 1);

			Vector3i vec3 = vec1 + vec2;

			Assert::AreEqual(1, vec1.x);
			Assert::AreEqual(1, vec1.y);
			Assert::AreEqual(1, vec1.z);
			Assert::AreEqual(1, vec2.x);
			Assert::AreEqual(1, vec2.y);
			Assert::AreEqual(1, vec2.z);
			Assert::AreEqual(2, vec3.x);
			Assert::AreEqual(2, vec3.y);
			Assert::AreEqual(2, vec3.z);
		}

		TEST_METHOD(Vector3i_SubVector_PopulatesValues)
		{
			Vector3i vec1(3, 3, 3);
			Vector3i vec2(1, 1, 1);

			Vector3i vec3 = vec1 - vec2;

			Assert::AreEqual(2, vec3.x);
			Assert::AreEqual(2, vec3.y);
			Assert::AreEqual(2, vec3.z);
		}

		TEST_METHOD(Vector3u_SubVector_PopulatesValues)
		{
			Vector3u vec1(3, 3, 3);
			Vector3u vec2(1, 1, 1);

			Vector3u vec3 = vec1 - vec2;

			Assert::AreEqual(2u, vec3.x);
			Assert::AreEqual(2u, vec3.y);
			Assert::AreEqual(2u, vec3.z);
		}

		TEST_METHOD(Vector3f_SubVector_PopulatesValues)
		{
			Vector3f vec1(3.f, 3.f, 3.f);
			Vector3f vec2(1.f, 1.f, 1.f);

			Vector3f vec3 = vec1 - vec2;

			Assert::AreEqual(2.f, vec3.x);
			Assert::AreEqual(2.f, vec3.y);
			Assert::AreEqual(2.f, vec3.z);
		}

		TEST_METHOD(Vector3i_SubVector_DoesNotModifyOperands)
		{
			Vector3i vec1(3, 3, 3);
			Vector3i vec2(1, 1, 1);

			Vector3i vec3 = vec1 - vec2;

			Assert::AreEqual(3, vec1.x);
			Assert::AreEqual(3, vec1.y);
			Assert::AreEqual(3, vec1.z);
			Assert::AreEqual(1, vec2.x);
			Assert::AreEqual(1, vec2.y);
			Assert::AreEqual(1, vec2.z);
			Assert::AreEqual(2, vec3.x);
			Assert::AreEqual(2, vec3.y);
			Assert::AreEqual(2, vec3.z);
		}

		TEST_METHOD(Vector3i_MulVector_PopulatesValues)
		{
			Vector3i vec1(2, 2, 2);
			Vector3i vec2(2, 2, 2);

			Vector3i vec3 = vec1 * vec2;

			Assert::AreEqual(4, vec3.x);
			Assert::AreEqual(4, vec3.y);
			Assert::AreEqual(4, vec3.z);
		}

		TEST_METHOD(Vector3u_MulVector_PopulatesValues)
		{
			Vector3u vec1(2, 2, 2);
			Vector3u vec2(2, 2, 2);

			Vector3u vec3 = vec1 * vec2;

			Assert::AreEqual(4u, vec3.x);
			Assert::AreEqual(4u, vec3.y);
			Assert::AreEqual(4u, vec3.z);
		}

		TEST_METHOD(Vector3f_MulVector_PopulatesValues)
		{
			Vector3f vec1(2.f, 2.f, 2.f);
			Vector3f vec2(2.f, 2.f, 2.f);

			Vector3f vec3 = vec1 * vec2;

			Assert::AreEqual(4.f, vec3.x);
			Assert::AreEqual(4.f, vec3.y);
			Assert::AreEqual(4.f, vec3.z);
		}

		TEST_METHOD(Vector3i_MulVector_ByZero_ZeroesValues)
		{
			Vector3i vec1(2, 2, 2);
			Vector3i vec2(0, 0, 0);

			Vector3i vec3 = vec1 * vec2;

			Assert::AreEqual(0, vec3.x);
			Assert::AreEqual(0, vec3.y);
			Assert::AreEqual(0, vec3.z);
		}

		TEST_METHOD(Vector3u_MulVector_ByZero_ZeroesValues)
		{
			Vector3u vec1(2, 2, 2);
			Vector3u vec2(0, 0, 0);

			Vector3u vec3 = vec1 * vec2;

			Assert::AreEqual(0u, vec3.x);
			Assert::AreEqual(0u, vec3.y);
			Assert::AreEqual(0u, vec3.z);
		}

		TEST_METHOD(Vector3f_MulVector_ByZero_ZeroesValues)
		{
			Vector3f vec1(2.f, 2.f, 2.f);
			Vector3f vec2(0.f, 0.f, 0.f);

			Vector3f vec3 = vec1 * vec2;

			Assert::AreEqual(0.f, vec3.x);
			Assert::AreEqual(0.f, vec3.y);
			Assert::AreEqual(0.f, vec3.z);
		}

		TEST_METHOD(Vector3i_MulVector_DoesNotModifyOperands)
		{
			Vector3i vec1(2, 2, 2);
			Vector3i vec2(3, 3, 3);

			Vector3i vec3 = vec1 * vec2;

			Assert::AreEqual(2, vec1.x);
			Assert::AreEqual(2, vec1.y);
			Assert::AreEqual(2, vec1.z);
			Assert::AreEqual(3, vec2.x);
			Assert::AreEqual(3, vec2.y);
			Assert::AreEqual(3, vec2.z);
			Assert::AreEqual(6, vec3.x);
			Assert::AreEqual(6, vec3.y);
			Assert::AreEqual(6, vec3.z);
		}

		TEST_METHOD(Vector3i_DivVector_PopulatesValues)
		{
			Vector3i vec1(2, 2, 2);
			Vector3i vec2(2, 2, 2);

			Vector3i vec3 = vec1 / vec2;

			Assert::AreEqual(1, vec3.x);
			Assert::AreEqual(1, vec3.y);
			Assert::AreEqual(1, vec3.z);
		}

		TEST_METHOD(Vector3u_DivVector_PopulatesValues)
		{
			Vector3u vec1(2, 2, 2);
			Vector3u vec2(2, 2, 2);

			Vector3u vec3 = vec1 / vec2;

			Assert::AreEqual(1u, vec3.x);
			Assert::AreEqual(1u, vec3.y);
			Assert::AreEqual(1u, vec3.z);
		}

		TEST_METHOD(Vector3f_DivVector_PopulatesValues)
		{
			Vector3f vec1(2.f, 2.f, 2.f);
			Vector3f vec2(2.f, 2.f, 2.f);

			Vector3f vec3 = vec1 / vec2;

			Assert::AreEqual(1.f, vec3.x);
			Assert::AreEqual(1.f, vec3.y);
			Assert::AreEqual(1.f, vec3.z);
		}

		TEST_METHOD(Vector3i_DivVector_DoesNotModifyOperands)
		{
			Vector3i vec1(4, 4, 4);
			Vector3i vec2(2, 2, 2);

			Vector3i vec3 = vec1 / vec2;

			Assert::AreEqual(4, vec1.x);
			Assert::AreEqual(4, vec1.y);
			Assert::AreEqual(4, vec1.z);
			Assert::AreEqual(2, vec2.x);
			Assert::AreEqual(2, vec2.y);
			Assert::AreEqual(2, vec2.z);
			Assert::AreEqual(2, vec3.x);
			Assert::AreEqual(2, vec3.y);
			Assert::AreEqual(2, vec3.z);
		}


		TEST_METHOD(Vector3i_MulScalar_PopulatesValues)
		{
			Vector3i vec1(2, 2, 2);

			Vector3i vec2 = vec1 * 2;

			Assert::AreEqual(4, vec2.x);
			Assert::AreEqual(4, vec2.y);
			Assert::AreEqual(4, vec2.z);
		}

		TEST_METHOD(Vector3u_MulScalar_PopulatesValues)
		{
			Vector3u vec1(2, 2, 2);

			Vector3u vec2 = vec1 * 2u;

			Assert::AreEqual(4u, vec2.x);
			Assert::AreEqual(4u, vec2.y);
			Assert::AreEqual(4u, vec2.z);
		}

		TEST_METHOD(Vector3f_MulScalar_PopulatesValues)
		{
			Vector3f vec1(2.f, 2.f, 2.f);

			Vector3f vec2 = vec1 * 2.f;

			Assert::AreEqual(4.f, vec2.x);
			Assert::AreEqual(4.f, vec2.y);
			Assert::AreEqual(4.f, vec2.z);
		}

		TEST_METHOD(Vector3i_MulScalar_ByZero_ZeroesValues)
		{
			Vector3i vec1(2, 2, 2);

			Vector3i vec2 = vec1 * 0;

			Assert::AreEqual(0, vec2.x);
			Assert::AreEqual(0, vec2.y);
			Assert::AreEqual(0, vec2.z);
		}

		TEST_METHOD(Vector3u_MulScalar_ByZero_ZeroesValues)
		{
			Vector3u vec1(2, 2, 2);

			Vector3u vec2 = vec1 * 0u;

			Assert::AreEqual(0u, vec2.x);
			Assert::AreEqual(0u, vec2.y);
			Assert::AreEqual(0u, vec2.z);
		}

		TEST_METHOD(Vector3f_MulScalar_ByZero_ZeroesValues)
		{
			Vector3f vec1(2.f, 2.f, 2.f);

			Vector3f vec2 = vec1 * 0.f;

			Assert::AreEqual(0.f, vec2.x);
			Assert::AreEqual(0.f, vec2.y);
			Assert::AreEqual(0.f, vec2.z);
		}

		TEST_METHOD(Vector3i_MulScalar_DoesNotModifyOperand)
		{
			Vector3i vec1(2, 2, 2);

			Vector3i vec2 = vec1 * 3;

			Assert::AreEqual(2, vec1.x);
			Assert::AreEqual(2, vec1.y);
			Assert::AreEqual(2, vec1.z);
			Assert::AreEqual(6, vec2.x);
			Assert::AreEqual(6, vec2.y);
			Assert::AreEqual(6, vec2.z);
		}

		TEST_METHOD(Vector3i_DivScalar_PopulatesValues)
		{
			Vector3i vec1(2, 2, 2);

			Vector3i vec2 = vec1 / 2;

			Assert::AreEqual(1, vec2.x);
			Assert::AreEqual(1, vec2.y);
			Assert::AreEqual(1, vec2.z);
		}

		TEST_METHOD(Vector3u_DivScalar_PopulatesValues)
		{
			Vector3u vec1(2, 2, 2);

			Vector3u vec2 = vec1 / 2u;

			Assert::AreEqual(1u, vec2.x);
			Assert::AreEqual(1u, vec2.y);
			Assert::AreEqual(1u, vec2.z);
		}

		TEST_METHOD(Vector3f_DivScalar_PopulatesValues)
		{
			Vector3f vec1(2.f, 2.f, 2.f);

			Vector3f vec2 = vec1 / 2.f;

			Assert::AreEqual(1.f, vec2.x);
			Assert::AreEqual(1.f, vec2.y);
			Assert::AreEqual(1.f, vec2.z);
		}

		TEST_METHOD(Vector3i_DivScalar_DoesNotModifyOperand)
		{
			Vector3i vec1(4, 4, 4);

			Vector3i vec2 = vec1 / 2;

			Assert::AreEqual(4, vec1.x);
			Assert::AreEqual(4, vec1.y);
			Assert::AreEqual(4, vec1.z);
			Assert::AreEqual(2, vec2.x);
			Assert::AreEqual(2, vec2.y);
			Assert::AreEqual(2, vec2.z);
		}


		// ======================================================
		// Vector Maths
		// ======================================================

		TEST_METHOD(Vector3i_Clamp_WhenBelowLowerBound_ClampsUp)
		{
			Vector3i min(2, 2, 2);
			Vector3i max(4, 4, 4);
			Vector3i vec(0, 0, 0);

			Vector3i result = vec.Clamp(min, max);

			Assert::AreEqual(2, result.x);
			Assert::AreEqual(2, result.y);
		}

		TEST_METHOD(Vector3i_Clamp_WhenAboveUpperBound_ClampsDown)
		{
			Vector3i min(2, 2, 2);
			Vector3i max(4, 4, 4);
			Vector3i vec(6, 6, 6);

			Vector3i result = vec.Clamp(min, max);

			Assert::AreEqual(4, result.x);
			Assert::AreEqual(4, result.y);
		}

		TEST_METHOD(Vector3i_Clamp_WhenWithinBounds_ReturnsUnchanged)
		{
			Vector3i min(2, 2, 2);
			Vector3i max(4, 4, 4);
			Vector3i vec(3, 3, 3);

			Vector3i result = vec.Clamp(min, max);

			Assert::AreEqual(3, result.x);
			Assert::AreEqual(3, result.y);
		}

		TEST_METHOD(Vector3u_Clamp_ClampsBetweenBounds)
		{
			Vector3u min(2, 2, 2);
			Vector3u max(4, 4, 4);
			Vector3u vec(6, 6, 6);

			Vector3u result = vec.Clamp(min, max);

			Assert::AreEqual(4u, result.x);
			Assert::AreEqual(4u, result.y);
		}

		TEST_METHOD(Vector3f_Clamp_ClampsBetweenBounds)
		{
			Vector3f min(2.f, 2.f, 2.f);
			Vector3f max(4.f, 4.f, 4.f);
			Vector3f vec(6.f, 6.f, 6.f);

			Vector3f result = vec.Clamp(min, max);

			Assert::AreEqual(4.f, result.x);
			Assert::AreEqual(4.f, result.y);
		}

		TEST_METHOD(Vector3i_LengthSquared_NonSymmetric_ReturnsCorrectValue)
		{
			Vector3i vec(2, 3, 6);

			Assert::AreEqual(49, vec.LengthSquared());
		}

		TEST_METHOD(Vector3u_LengthSquared_NonSymmetric_ReturnsCorrectValue)
		{
			Vector3u vec(2, 3, 6);

			Assert::AreEqual(49u, vec.LengthSquared());
		}

		TEST_METHOD(Vector3f_LengthSquared_NonSymmetric_ReturnsCorrectValue)
		{
			Vector3f vec(2.f, 3.f, 6.f);

			Assert::AreEqual(49.f, vec.LengthSquared());
		}

		TEST_METHOD(Vector3i_Distance_NonSymmetric_ReturnsCorrectValue)
		{
			Vector3i vec1(5, 7, 10);
			Vector3i vec2(3, 4, 4);

			Assert::AreEqual(7, vec1.Distance(vec2));
		}

		TEST_METHOD(Vector3u_Distance_NonSymmetric_ReturnsCorrectValue)
		{
			Vector3u vec1(5, 7, 10);
			Vector3u vec2(3, 4, 4);

			Assert::AreEqual(7u, vec1.Distance(vec2));
		}

		TEST_METHOD(Vector3f_Distance_NonSymmetric_ReturnsCorrectValue)
		{
			Vector3f vec1(5.f, 7.f, 10.f);
			Vector3f vec2(3.f, 4.f, 4.f);

			Assert::AreEqual(7.f, vec1.Distance(vec2), 0.0001f);
		}

		TEST_METHOD(Vector3i_Length_NonSymmetric_ReturnsCorrectValue)
		{
			Vector3i vec(2, 3, 6);

			Assert::AreEqual(7, vec.Length());
		}

		TEST_METHOD(Vector3u_Length_NonSymmetric_ReturnsCorrectValue)
		{
			Vector3u vec(2, 3, 6);

			Assert::AreEqual(7u, vec.Length());
		}

		TEST_METHOD(Vector3f_Length_NonSymmetric_ReturnsCorrectValue)
		{
			Vector3f vec(2.f, 3.f, 6.f);

			Assert::AreEqual(7.f, vec.Length(), 0.0001f);
		}

		TEST_METHOD(Vector3i_IsBetween_WhenProjectionBetweenEndpoints_ReturnsTrue)
		{
			Vector3i min(2, 2, 2);
			Vector3i max(4, 4, 4);
			Vector3i vec(3, 3, 3);

			Assert::IsTrue(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector3i_IsBetween_WhenOutsideEndpoints_ReturnsFalse)
		{
			Vector3i min(2, 2, 2);
			Vector3i max(4, 4, 4);
			Vector3i vec(6, 6, 6);

			Assert::IsFalse(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector3i_IsBetween_NonCollinear_ReturnsFalse)
		{
			Vector3i a(2, 2, 2);
			Vector3i b(4, 4, 4);
			Vector3i vec(3, 4, 5);

			Assert::IsFalse(vec.IsBetween(a, b));
		}

		TEST_METHOD(Vector3i_IsBetween_NonCollinear_MayReturnTrue)
		{
			Vector3i a(2, 2, 2);
			Vector3i b(4, 4, 4);
			Vector3i vec(3, 3, 4);

			Assert::IsTrue(vec.IsBetween(a, b));
		}

		TEST_METHOD(Vector3i_IsBetween_AtEndpoint_ReturnsTrue)
		{
			Vector3i a(2, 2, 2);
			Vector3i b(4, 4, 4);

			Assert::IsTrue(a.IsBetween(a, b));
			Assert::IsTrue(b.IsBetween(a, b));
		}

		TEST_METHOD(Vector3u_IsBetween_WhenProjectionBetweenEndpoints_MayFailDueToUnsignedUnderflow)
		{
			Vector3u min(2, 2, 2);
			Vector3u max(4, 4, 4);
			Vector3u vec(3, 3, 3);

			Assert::IsFalse(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector3u_IsBetween_WhenOutsideEndpoints_ReturnsFalse)
		{
			Vector3u min(2, 2, 2);
			Vector3u max(4, 4, 4);
			Vector3u vec(6, 6, 6);

			Assert::IsFalse(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector3f_IsBetween_WhenProjectionBetweenEndpoints_ReturnsTrue)
		{
			Vector3f min(2.f, 2.f, 2.f);
			Vector3f max(4.f, 4.f, 4.f);
			Vector3f vec(3.f, 3.f, 3.f);

			Assert::IsTrue(vec.IsBetween(min, max));
		}

		TEST_METHOD(Vector3f_IsBetween_WhenOutsideEndpoints_ReturnsFalse)
		{
			Vector3f min(2.f, 2.f, 2.f);
			Vector3f max(4.f, 4.f, 4.f);
			Vector3f vec(6.f, 6.f, 6.f);

			Assert::IsFalse(vec.IsBetween(min, max));
		}

		// ======================================================
		// Normalize
		// ======================================================

		TEST_METHOD(Vector3f_Normalize_ReturnsUnitVector)
		{
			Vector3f vec(3.f, 4.f, 5.f);

			Vector3f result = vec.Normalize();

			Assert::AreEqual(0.4243f, result.x, 0.0001f);
			Assert::AreEqual(0.5657f, result.y, 0.0001f);
			Assert::AreEqual(0.7071f, result.z, 0.0001f);
			Assert::AreEqual(1.f, result.Length(), 0.0001f);
		}
	};
}