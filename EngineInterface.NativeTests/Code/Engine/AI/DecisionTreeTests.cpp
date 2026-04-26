#include "CppUnitTest.h"

#include <Engine/AI/DecisionTree.h>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AI
{
	enum class TestDecisionResult
	{
		Root,
		TrueResult,
		FalseResult,
		BranchRoot,
		BranchTrueResult
	};

	TEST_CLASS(DecisionTreeTests)
	{
	public:
		TEST_METHOD(DecisionTree_Constructor_WithNullRoot_Throws)
		{
			Assert::ExpectException<std::invalid_argument>([]
				{
					DecisionTree<TestDecisionResult, bool, int> tree(nullptr);
				});
		}

		TEST_METHOD(DecisionTree_GetRoot_ReturnsRoot)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			auto result = tree.GetRoot();

			Assert::IsNotNull(result.get());
			Assert::IsTrue(root.get() == result.get());
		}

		TEST_METHOD(DecisionTree_AddBranch_WithValidBranch_StoresBranch)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			tree.AddBranch("Other", root);

			auto branch = tree.GetBranchNode("Other");

			Assert::IsNotNull(branch.get());
			Assert::IsTrue(root.get() == branch.get());
		}

		TEST_METHOD(DecisionTree_AddBranch_WithExistingId_OverridesBranch)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			tree.AddBranch("Other", root);

			auto branch1 = tree.GetBranchNode("Other");

			Assert::IsNotNull(branch1.get());
			Assert::IsTrue(root.get() == branch1.get());

			auto branchRoot = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value == 10;
				},
				TestDecisionResult::BranchRoot
			);

			tree.AddBranch("Other", branchRoot);

			auto branch2 = tree.GetBranchNode("Other");

			Assert::IsNotNull(branch2.get());
			Assert::IsTrue(branchRoot.get() == branch2.get());
		}

		TEST_METHOD(DecisionTree_AddBranch_WithNullBranch_DoesNothing)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			tree.AddBranch("Other", nullptr);

			Assert::IsNull(tree.GetBranchNode("Other").get());
		}

		TEST_METHOD(DecisionTree_GetBranchNode_WithMissingId_ReturnsNull)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			Assert::IsNull(tree.GetBranchNode("Other").get());
		}

		TEST_METHOD(DecisionTree_AddNode_WithNullParent_ReturnsNullPtr)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			auto node = tree.AddNode(
				nullptr,
				[](int value) { return true; },
				TestDecisionResult::TrueResult,
				true
			);

			Assert::IsNull(node.get());
		}

		TEST_METHOD(DecisionTree_AddNode_ReturnsCreatedNode)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			auto node = tree.AddNode(
				root,
				[](int value) { return true; },
				TestDecisionResult::TrueResult,
				true
			);

			Assert::IsNotNull(node.get());
		}

		TEST_METHOD(DecisionTree_AddNode_WhenBranchTrue_AssignsTrueNode)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			tree.AddNode(
				root,
				[](int value) { return true; },
				TestDecisionResult::TrueResult,
				true
			);

			Assert::IsNotNull(root->m_true.get());
		}

		TEST_METHOD(DecisionTree_AddNode_WhenBranchFalse_AssignsFalseNode)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			tree.AddNode(
				root,
				[](int value) { return false; },
				TestDecisionResult::FalseResult,
				false
			);

			Assert::IsNotNull(root->m_false.get());
		}

		TEST_METHOD(DecisionTree_Evaluate_NodeWithNoCondition_ReturnsOwnResult)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				nullptr,
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			tree.Evaluate(10);

			auto res = tree.GetResults();

			Assert::IsFalse(res.empty());
			Assert::AreEqual(std::size_t(1), res.size());
			Assert::AreEqual(
				static_cast<int>(TestDecisionResult::Root),
				static_cast<int>(res[0])
			);
		}

		TEST_METHOD(DecisionTree_Evaluate_WithTruePath_ReturnsExpectedResult)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			tree.AddNode(
				root,
				[](int value) { return true; },
				TestDecisionResult::TrueResult,
				true
			);

			tree.Evaluate(10);

			auto res = tree.GetResults();

			Assert::IsFalse(res.empty());
			Assert::AreEqual(std::size_t(1), res.size());
			Assert::AreEqual(
				static_cast<int>(TestDecisionResult::TrueResult),
				static_cast<int>(res[0])
			);
		}

		TEST_METHOD(DecisionTree_Evaluate_WithFalsePath_ReturnsExpectedResult)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			tree.AddNode(
				root,
				[](int value) { return false; },
				TestDecisionResult::FalseResult,
				false
			);

			tree.Evaluate(-10);

			auto res = tree.GetResults();

			Assert::IsFalse(res.empty());
			Assert::AreEqual(std::size_t(1), res.size());
			Assert::AreEqual(
				static_cast<int>(TestDecisionResult::FalseResult),
				static_cast<int>(res[0]));
		}

		TEST_METHOD(DecisionTree_Evaluate_ClearPreviousResults)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			tree.AddNode(
				root,
				[](int value) { return true; },
				TestDecisionResult::TrueResult,
				true
			);

			tree.AddNode(
				root,
				[](int value) { return false; },
				TestDecisionResult::FalseResult,
				false
			);

			tree.Evaluate(10);

			auto res = tree.GetResults();

			Assert::IsFalse(res.empty());
			Assert::AreEqual(std::size_t(1), res.size());
			Assert::AreEqual(
				static_cast<int>(TestDecisionResult::TrueResult),
				static_cast<int>(res[0])
			);

			tree.Evaluate(-10);

			res = tree.GetResults();

			Assert::IsFalse(res.empty());
			Assert::AreEqual(std::size_t(1), res.size());
			Assert::AreEqual(
				static_cast<int>(TestDecisionResult::FalseResult),
				static_cast<int>(res[0]));
		}

		TEST_METHOD(DecisionTree_Evaluate_WithBranches_AppendsBranchResults)
		{
			auto root = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value > 0;
				},
				TestDecisionResult::Root
			);

			DecisionTree<TestDecisionResult, bool, int> tree(root);

			// Create a branch with its own root
			auto branchRoot = std::make_shared<DecisionNode<TestDecisionResult, bool, int>>(
				[](int value)
				{
					return value == 10;
				},
				TestDecisionResult::BranchRoot
			);

			tree.AddBranch("Branch", branchRoot);

			// Add nodes to both trees
			tree.AddNode(
				root,
				[](int value) { return true; },
				TestDecisionResult::TrueResult,
				true
			);

			tree.AddNode(
				branchRoot,
				[](int value) { return true; },
				TestDecisionResult::BranchTrueResult,
				true
			);

			tree.Evaluate(10);

			auto res = tree.GetResults();

			Assert::AreEqual(std::size_t(2), res.size());

			Assert::AreEqual(
				static_cast<int>(TestDecisionResult::TrueResult),
				static_cast<int>(res[0])
			);

			Assert::AreEqual(
				static_cast<int>(TestDecisionResult::BranchTrueResult),
				static_cast<int>(res[1])
			);
		}
	};
}