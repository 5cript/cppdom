#pragma once

#include <string_view>

class Component
{
public:
    virtual void render() {};
    virtual ~Component() = default;
};

