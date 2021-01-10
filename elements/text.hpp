#pragma once

#include "inline_html.hpp"

namespace CppDom::Elements
{
    class text : public InlineHtml
    {
    public:
        text(std::string content) 
            : InlineHtml(std::move(content)) 
        {
        }

        void renderInto(emscripten::val& parent) override
        {
            using emscripten::val;
            parent.set("innerText", emscripten::val{html_});
        }

        text* clone() const override
        {
            return new text(*this);
        }
    };
}