#pragma once

#include "html_element.hpp"

namespace CppDom::Elements
{
    template <typename... T>
    struct div : public HtmlElementProximate <T...>
    {
        div(T&&... t) : HtmlElementProximate <T...>("div", std::forward <T&&>(t)...) {}
    };
}