#pragma once

#include "../../Utilities/Colour.h"
#include <optional>
#include <string>

struct ElementStyle
{
	std::optional<Colour> colour;
	std::optional<std::string> effectID;
};