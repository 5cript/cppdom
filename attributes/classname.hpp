#pragma once

#include "attribute.hpp"

namespace Electronpp::Attributes
{
    struct className_ {
        Attribute <char const*> operator=(char const* val)
        {
            return {"className", std::move(val)};
        }
    } className;
}