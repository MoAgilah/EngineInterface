#pragma once

#include "../../Input/KeyCode.h"

class INativeKeyConverter
{
public:
    virtual ~INativeKeyConverter() = default;

    virtual KeyCode ConvertRaw(void* rawKey) const = 0;
};

template <typename PlatformKey>
class IKeyConverter : public INativeKeyConverter
{
public:
    virtual KeyCode Convert(PlatformKey key) const = 0;

    KeyCode ConvertRaw(void* rawKey) const override {
        return Convert(*static_cast<PlatformKey*>(rawKey));
    }
};
