#pragma once

#include "inline_html.hpp"

#include <cstdio>

namespace Electronpp::Elements
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

            parent.set("textContent", emscripten::val{html_});
        }

        text* clone() const override
        {
            return new text(*this);
        }
    };
}