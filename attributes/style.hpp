#pragma once

#include "attribute.hpp"

#include <sstream>

namespace CppDom::Attributes
{
    struct StyleProp {
        char const* name;
        constexpr StyleProp(char const* name)
            : name{name}
        {

        }
        std::string operator=(char const* value)
        {
            return std::string{name} + ":" + value;
        }
        std::string operator=(std::string const& value)
        {
            return std::string{name} + ":" + value;
        }
    };

    static constexpr StyleProp operator"" _cssa(char const* name, std::size_t)
    {
        return StyleProp{name};
    };

    template <typename... Properties>
    struct StyleImpl
    {
    };

    template <>
    struct StyleImpl <>
    {
        std::string inlineStyle = "";
        StyleImpl()
        {
        }

        std::string toString() const
        {
            return inlineStyle;
        }  
    };

    template <typename Property, typename... Properties>
    struct StyleImpl <Property, Properties...>
    {
        std::string inlineStyle = "";
        StyleImpl(Property const& prop, Properties const&... props)
        {
            std::stringstream sstr;
            using expander = int[];
            sstr << prop;
            (void)expander{0, (sstr << ";" << props, void(), 0)...};
            inlineStyle = sstr.str();
        }

        std::string toString() const
        {
            return inlineStyle;
        }        
    };

    template <typename... T>
    struct Style
        : public StyleImpl <T...>
    {
        Style(T&&... args)
            : StyleImpl <T...>(std::forward <T&&>(args)...)
        {}
    };

    struct style_ {
        template <typename... T>
        Attribute <std::string> operator=(Style<T...> const& style)
        {
            return {"style", style.toString()};
        }
    } style;
}