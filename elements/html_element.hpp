#pragma once

#include "element.hpp"
#include "text.hpp"
#include "../attributes/attribute.hpp"

#include <emscripten/val.h>

#include <iostream>

namespace CppDom
{
    template <typename... Children>
    struct HtmlElement : public Element
    {
        HtmlElement(std::string name, Element::attributes_type&& attributes, Children&&... children)
            : Element(
                std::move(name),
                std::move(attributes),
                {make_value <Children> (std::forward <Children&&>(children))...}
            )
        {
        }

        HtmlElement* clone() const override
        {
            return new HtmlElement(*this);
        }
    };

    // div proxy
    template <typename... Attr>
    struct HtmlElementProximate
    {
        std::string name;
        Element::attributes_type attributes;

        HtmlElementProximate(std::string name, Attr&&... attr)
            : name(std::move(name))
            , attributes{make_value <Attr>(attr)...}
        {
        }

        template <typename... ElementT>
        HtmlElement <ElementT...> operator()(ElementT&&... elements) &&
        {
            return HtmlElement <ElementT...>{
                std::move(name),
                std::move(attributes),
                std::forward <ElementT&&> (elements)...
            };
        }

        HtmlElement <Elements::text> operator()(char const* txt) &&
        {
            return HtmlElement <Elements::text>{
                std::move(name),
                std::move(attributes),
                Elements::text{txt}
            };
        }
    };
}

#define MAKE_HTML_TAG(NAME) \
namespace CppDom::Elements \
{ \
    template <typename... T> \
    struct NAME : public HtmlElementProximate <T...> \
    { \
        NAME(T&&... t) : HtmlElementProximate <T...>(#NAME, std::forward <T&&>(t)...) {} \
\
        using HtmlElementProximate <T...>::operator(); \
    }; \
}