#pragma once

#include "html_element.hpp"

MAKE_HTML_TAG(address)
MAKE_HTML_TAG(article)
MAKE_HTML_TAG(aside)
MAKE_HTML_TAG(footer)
MAKE_HTML_TAG(header)
MAKE_HTML_TAG(h1)
MAKE_HTML_TAG(h2)
MAKE_HTML_TAG(h3)
MAKE_HTML_TAG(h4)
MAKE_HTML_TAG(h5)
MAKE_HTML_TAG(h6)
MAKE_HTML_TAG(hgroup)
MAKE_HTML_TAG(nav)
MAKE_HTML_TAG(section)

namespace CppDom::Elements
{
    template <typename... T>
    struct main_ : public HtmlElementProximate <T...>
    {
        main_(T&&... t) : HtmlElementProximate <T...>("main", std::forward <T&&>(t)...) {}
    };
}