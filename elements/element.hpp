#pragma once

#include <emscripten/val.h>

#include "../util/value_ptr.hpp"
#include "../attributes/attribute.hpp"

#include <emscripten/emscripten.h>

#include <cstdio>

namespace CppDom
{
    struct Element : public cloneable <Element>
    {
    public:
        using attributes_type = std::vector <value_ptr <Attributes::GenericAttribute>>;
        using children_type = std::vector <value_ptr <Element>>;

        Element(std::string name, std::vector <value_ptr <Attributes::GenericAttribute>> attributes, std::vector <value_ptr <Element>> children = {})
            : name{std::move(name)}
            , attributes{std::move(attributes)}
            , children{std::move(children)}
        {
        }

        virtual void renderInto(emscripten::val& parent)
        {
            using emscripten::val;

            auto elem = val::global("document").call<val>("createElement", val(name.c_str()));
            for (auto const& attr : attributes)
            {
                attr->setOn(elem);
            }
            for (auto const& child : children)
            {
                child->renderInto(elem);
            }
            parent.call<val>("appendChild", elem);
        }

        virtual ~Element() = default;

    private:
        std::string name;
        attributes_type attributes;
        children_type children;
    };
}