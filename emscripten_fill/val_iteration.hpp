#include "../util/function.hpp"
#include <emscripten/val.h>
#include <iostream>

namespace CppDom
{
    void forEach(emscripten::val const& val, std::function <void(std::string const&, emscripten::val)> const& func)
    {
        emscripten::val::module_property("extensions").call<emscripten::val>
        (
            "forEach",
            val,
            js::bind([func](emscripten::val name, emscripten::val member){
                func(name.as<std::string>(), member);
            }, std::placeholders::_1, std::placeholders::_2)
        );
    }
}

std::ostream& operator<<(std::ostream& stream, emscripten::val const& val)
{
    emscripten::val::module_property("extensions").call<emscripten::val>("consolelog", val);
    return stream;
}