#pragma once

#include "attribute.hpp"

namespace CppDom::Attributes
{
    struct className_ {
        Attribute <char const*> operator=(char const* val)
        {
            return {"class", std::move(val)};
        }
    } className;
}