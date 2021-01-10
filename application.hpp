#pragma once

#include "body.hpp"
#include "bindings.hpp"

namespace CppDom
{
    class Application
    {
    public:
        virtual void render() = 0;
        virtual ~Application() = default;
    };
}