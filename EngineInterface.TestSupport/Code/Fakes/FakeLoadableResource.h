#pragma once

#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>

#include <Utilities/Traits.h>

class FakeLoadableResource
{
public:
    bool wasLoadCalled = false;
    std::string lastFilepath;
    std::string loadedContent;

    bool LoadFromFile(const std::string& filepath)
    {
        wasLoadCalled = true;
        lastFilepath = filepath;

        std::ifstream file(filepath);
        if (!file.is_open())
        {
            return false;
        }

        loadedContent.assign(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>());

        return !loadedContent.empty();
    }
};

template<>
struct ResourceTraits<FakeLoadableResource>
{
    static constexpr const char* TypeName = "FakeLoadableResource";

    static std::shared_ptr<FakeLoadableResource> Create()
    {
        return std::make_shared<FakeLoadableResource>();
    }
};