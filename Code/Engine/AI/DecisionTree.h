#pragma once

#include "../../Utilities/Utils.h"
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// Generic Decision Node
template <typename T, typename S, typename... Args>
class DecisionNode {
public:
	T m_result;
	std::function<S(Args...)> m_condition;
	std::shared_ptr<DecisionNode> m_true;
	std::shared_ptr<DecisionNode> m_false;

	DecisionNode(std::function<S(Args...)> condition, T result)
		: m_condition(condition), m_result(result), m_true(nullptr), m_false(nullptr)
	{
	}
};

// Decision Tree Class
template <typename T, typename S, typename... Args>
class DecisionTree
{
public:
	DecisionTree(std::shared_ptr<DecisionNode<T, S, Args...>> root)
		: m_root(root)
	{
		ENSURE_VALID(m_root);
	}

	std::shared_ptr<DecisionNode<T, S, Args...>> GetRoot() { return m_root; }

	void AddBranch(std::string id, std::shared_ptr<DecisionNode<T, S, Args...>> root)
	{
		ENSURE_VALID(root);
		m_branches[id] = root;
	}

	std::shared_ptr<DecisionNode<T, S, Args...>> GetBranchNode(std::string id)
	{
		auto it = m_branches.find(id);
		if (it != m_branches.end())
			return it->second;

		return nullptr;
	}

	// Function to dynamically add a node
	std::shared_ptr<DecisionNode<T, S, Args...>> AddNode(
		std::shared_ptr<DecisionNode<T, S, Args...>> parent,
		std::function<S(Args...)> condition,
		T result, bool branch)
	{
		ENSURE_VALID_RET(parent, nullptr);

		auto newNode = std::make_shared<DecisionNode<T, S, Args...>>(condition, result);

		ENSURE_VALID_RET(newNode, nullptr);

		if (branch)
		{
			parent->m_true = newNode;
		}
		else
		{
			parent->m_false = newNode;
		}

		return newNode;
	}

	void Evaluate(Args... input)
	{
		ENSURE_VALID(m_root);
		T result = EvaluateTree(m_root, input...);
		m_results.push_back(result);

		for (auto& branchPair : m_branches)
		{
			CONTINUE_IF_INVALID(branchPair.second);
			m_results.push_back(EvaluateTree(branchPair.second, input...));
		}
	}

	std::vector<T> GetResults() { return m_results; }

private:

	T EvaluateTree(std::shared_ptr<DecisionNode<T, S, Args...>> node, Args... input)
	{
		auto current = node;
		while (current)
		{
			if (current->m_condition)
			{
				if (current->m_condition(input...))
				{
					if (!current->m_true)
						return current->m_result;
					current = current->m_true;
				}
				else
				{
					if (!current->m_false)
						return current->m_result;
					current = current->m_false;
				}
			}
			else
			{
				return current->m_result;
			}
		}
		throw std::runtime_error("Decision tree evaluation failed");
	}

	std::shared_ptr<DecisionNode<T, S, Args...>> m_root; // Root of the tree
	std::map<std::string, std::shared_ptr<DecisionNode<T, S, Args...>>> m_branches;
	std::vector<T> m_results;
};