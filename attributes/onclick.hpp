#pragma once

#include "attribute.hpp"
#include "../util/function.hpp"

namespace CppDom::Attributes
{
    struct onClick_ {
        ComplexAttribute operator=(std::function<void(emscripten::val)>&& func)
        {
            return {[f = std::move(func)](emscripten::val element){
                element.set("onclick", js::bind(f, std::placeholders::_1));
            }};
        }
    } onClick;
}