#pragma once

#include "html_element.hpp"
#include "text.hpp"

namespace Electronpp::Elements
{
    template <typename... T>
    struct button : public HtmlElementProximate <T...>
    {
        button(T&&... t) : HtmlElementProximate <T...>("button", std::forward <T&&>(t)...) {}

        using HtmlElementProximate <T...>::operator();
    };
}