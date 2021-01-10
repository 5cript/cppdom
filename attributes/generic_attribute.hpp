#pragma once

#include "../util/value_ptr.hpp"

#include <emscripten/val.h>

namespace CppDom::Attributes
{
    struct GenericAttribute : public cloneable <GenericAttribute>
    {
    public:
        virtual void setOn(emscripten::val& node) = 0;
        virtual void update() {};

        virtual ~GenericAttribute() = default;
    };
}