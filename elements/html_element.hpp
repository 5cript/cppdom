#pragma once

#include "element.hpp"
#include "../attributes/attribute.hpp"

#include <emscripten/val.h>

#include <iostream>

namespace Electronpp
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
    };
}