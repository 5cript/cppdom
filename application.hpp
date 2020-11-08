#pragma once

#include "body.hpp"

namespace Electronpp
{
    class Application
    {
    public:
        virtual void render() = 0;
        virtual ~Application() = default;
    };
}