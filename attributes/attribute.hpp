#pragma once

#include "generic_attribute.hpp"
#include "../util/observer.hpp"

#include <emscripten/val.h>
#include <functional>

#include <iostream>

namespace CppDom::Attributes
{
    template <typename ValueT>
    class Attribute : public GenericAttribute
    {
    public:
        Attribute(std::string name, ValueT value)
            : name_{std::move(name)}
            , value_{std::move(value)}
        {
        }
        
        void setOn(emscripten::val& node) override
        {
            using emscripten::val;

            node.call<val>("setAttribute", val(name_), val(value_));
        }

        Attribute* clone() const override {
            return new Attribute(name_, value_);
        }

        Attribute(Attribute const&) = default;
        Attribute(Attribute&&) = default;

    private:
        std::string name_;
        ValueT value_;
    };

    class ComplexAttribute : public GenericAttribute
    {
    public:
        ComplexAttribute(std::function <void(emscripten::val&)> setOn)
            : GenericAttribute{}
            , setOn_{setOn}
        {
        }

        void setOn(emscripten::val& node) override
        {
            setOn_(node);
        }

        ComplexAttribute* clone() const override {
            return new ComplexAttribute(setOn_);
        }

    private:
        std::function <void(emscripten::val&)> setOn_;
    };

    template <typename ValueT>
    class ReactiveAttribute : public GenericAttribute
    {
    public:
        ReactiveAttribute(std::string name, SharedObserver<ValueT> value)
            : name_{std::move(name)}
            , value_{std::move(value)}
        {
            value_.subscribe(this);
        }     
        ~ReactiveAttribute()
        {
            value_.unsubscribe(this);
        }   
        operator=(ReactiveAttribute const&) = delete;
        ReactiveAttribute(ReactiveAttribute const&) = delete;

        void setOn(emscripten::val& node) override
        {
            using emscripten::val;
            node.call<val>("setAttribute", val(name_), val(static_cast <ValueT&>(value_)));
            parent_ = &node;
        }

        void update() override
        {
            std::cout << "update reactive\n";
            using emscripten::val;
            if (parent_ != nullptr)
                parent_->call<val>("setAttribute", val(name_), val(static_cast <ValueT&>(value_)));
        }
        
        ReactiveAttribute* clone() const override {
            return new ReactiveAttribute(name_, value_);
        }

    private:
        emscripten::val* parent_;
        std::string name_;
        SharedObserver<ValueT> value_;
    };
}

#define MAKE_HTML_STRING_ATTRIBUTE(NAME) \
namespace CppDom::Attributes \
{ \
    struct NAME ## _ { \
        Attribute <char const*> operator=(char const* val) \
        { \
            return {#NAME, std::move(val)}; \
        } \
        template <typename T> \
        ReactiveAttribute <T> operator=(SharedObserver<T> observed) \
        { \
            return {#NAME, std::move(observed)}; \
        } \
    } NAME; \
}