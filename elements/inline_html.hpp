#pragma once

#include "element.hpp"

#include <emscripten/val.h>

namespace Electronpp
{
    class InlineHtml : public Element
    {   
    public:
        InlineHtml(std::string html)
            : Element(
                {}, {}, {}
            )
            , html_{std::move(html)}
        {
        }

        void renderInto(emscripten::val& parent) override
        {
            using emscripten::val;

            parent.set("innerHtml", emscripten::val{html_});
        }

        InlineHtml* clone() const override
        {
            return new InlineHtml(*this);
        }

    protected:
        std::string html_;
    };
}