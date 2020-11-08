#pragma once

#include <emscripten/val.h>

auto body() 
{
    return emscripten::val::global("document")["body"];
}