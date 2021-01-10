#pragma once

#include <emscripten/bind.h>
#include <functional>

/*
EMSCRIPTEN_BINDINGS(CppDom)
{
    using namespace emscripten;

    class_<std::function <void()>>("stdfunction")
        .constructor<>()
        .function("call", &std::function <void()>::operator())
    ;
}
*/