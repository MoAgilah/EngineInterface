#pragma once

#include "../../Utilities/Guards.h"
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// Generic Decision Node
template <typename T, typename S, typename... Args>
class DecisionNode
{
public:
    T m_result;
    std::function<S(Args...)> m_condition;
    std::shared_ptr<DecisionNode<T, S, Args...>> m_true;
    std::shared_ptr<DecisionNode<T, S, Args...>> m_false;

    DecisionNode(std::function<S(Args...)> condition, T result)
        : m_result(result), m_condition(condition), m_true(nullptr), m_false(nullptr)
    {
    }
};

// Decision Tree Class
template <typename T, typename S, typename... Args>
class DecisionTree
{
public:
    explicit DecisionTree(std::shared_ptr<DecisionNode<T, S, Args...>> root)
        : m_root(root)
    {
        if (!CheckNotNull(m_root.get(), "Invalid Pointer 'm_root'"))
        {
            throw std::invalid_argument("DecisionTree requires a valid root node");
        }
    }

    std::shared_ptr<DecisionNode<T, S, Args...>> GetRoot() const
    {
        return m_root;
    }

    void AddBranch(const std::string& id, std::shared_ptr<DecisionNode<T, S, Args...>> root)
    {
        if (!CheckNotNull(root.get(), "Invalid Pointer 'root'"))
            return;

        m_branches[id] = root;
    }

    std::shared_ptr<DecisionNode<T, S, Args...>> GetBranchNode(const std::string& id) const
    {
        auto it = m_branches.find(id);
        if (it != m_branches.end())
            return it->second;

        return nullptr;
    }

    std::shared_ptr<DecisionNode<T, S, Args...>> AddNode(
        std::shared_ptr<DecisionNode<T, S, Args...>> parent,
        std::function<S(Args...)> condition,
        T result,
        bool branch)
    {
        if (!CheckNotNull(parent.get(), "Invalid Pointer 'parent'"))
            return nullptr;

        auto newNode = std::make_shared<DecisionNode<T, S, Args...>>(condition, result);

        if (!CheckNotNull(newNode.get(), "Invalid Pointer 'newNode'"))
            return nullptr;

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
        if (!CheckNotNull(m_root.get(), "Invalid Pointer 'm_root'"))
            return;

        m_results.clear();

        T result = EvaluateTree(m_root, input...);
        m_results.push_back(result);

        for (auto& branchPair : m_branches)
        {
            if (!CheckNotNull(branchPair.second.get(), "Invalid Pointer 'branchPair.second'"))
                continue;

            m_results.push_back(EvaluateTree(branchPair.second, input...));
        }
    }

    const std::vector<T>& GetResults() const
    {
        return m_results;
    }

private:
    T EvaluateTree(std::shared_ptr<DecisionNode<T, S, Args...>> node, Args... input)
    {
        if (!CheckNotNull(node.get(), "Invalid Pointer 'node'"))
            throw std::runtime_error("Decision tree evaluation failed: invalid root node");

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

    std::shared_ptr<DecisionNode<T, S, Args...>> m_root;
    std::map<std::string, std::shared_ptr<DecisionNode<T, S, Args...>>> m_branches;
    std::vector<T> m_results;
};