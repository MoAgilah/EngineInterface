#pragma once

#include "../../../Utilities/Vector.h"
#include <memory>
#include <string>

// Non-templated base interface for type-erased window management
class INativeWindow
{
public:
    virtual ~INativeWindow() = default;

    virtual bool Create(const Vector2f& screenDims, const std::string& title) = 0;
    virtual void PollEvents() = 0;
    virtual bool ShouldClose() const = 0;
    virtual void Close() = 0;
    virtual void* GetNativeHandle() = 0;
};

// Templated interface that inherits from the type-erased base
template<typename T>
class IWindow : public INativeWindow
{
public:
    virtual T* GetWindow() = 0;

protected:

    std::shared_ptr<T> m_window;
};
