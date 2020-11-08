#pragma once

#include "../util/value_ptr.hpp"

#include <emscripten/val.h>

namespace Electronpp::Attributes
{
    struct GenericAttribute : public cloneable <GenericAttribute>
    {
        std::string name;
        GenericAttribute(std::string name)
            : name{std::move(name)}
        {
        }
        GenericAttribute()
            : name{""}
        {
        }

        virtual void setOn(emscripten::val& node) = 0;

        virtual ~GenericAttribute() = default;
    };

    template <typename ValueT>
    struct Attribute : GenericAttribute
    {
        ValueT value;

        Attribute(std::string name, ValueT const& value)
            : GenericAttribute{std::move(name)}
            , value{value}
        {
        }
        
        void setOn(emscripten::val& node) override
        {
            using emscripten::val;

            node.call<val>("setAttribute", val(name), val(value));
        }

        Attribute* clone() const override {
            return new Attribute(name, value);
        }

        Attribute(Attribute const&) = default;
        Attribute(Attribute&&) = default;
    };
}