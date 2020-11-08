#pragma once

#include "attribute.hpp"

namespace Electronpp::Attributes
{
    struct onClick_ {
        template <typename T>
        Attribute <std::function <void()>> operator=(T val)
        {
            return {"className", val};
        }
    } onClick;
}