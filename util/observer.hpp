#pragma once

#include "../attributes/generic_attribute.hpp"
#include <unordered_set>

namespace CppDom
{
    template <typename ValueT>
    class Observer
    {
    public:
        using value_type = ValueT;

        Observer(ValueT const& value)
            : value_{value}
            , subscribed_{}
        {}
        Observer(ValueT&& value)
            : value_(std::move(value))
            , subscribed_{}
        {}
        Observer()
            : value_{}
            , subscribed_{}
        {}
        ValueT* operator->()
        {
            return &value_;
        }
        Observer& operator=(ValueT const& value)
        {
            value_ = value;
            update();  
            return *this; 
        }
        void update()
        {
            for (auto const& subscriber : subscribed_)
            {
                subscriber->update();
            }
        }
        void subscribe(Attributes::GenericAttribute* attribute)
        {
            subscribed_.insert(attribute);
        }
        void unsubscribe(Attributes::GenericAttribute* attribute)
        {
            subscribed_.erase(attribute);
        }
        operator ValueT&()
        {
            return value_;
        }
    private:
        ValueT value_;
        std::unordered_set <Attributes::GenericAttribute*> subscribed_;
    };

    template <typename ValueT>
    class SharedObserver
    {
    public:
        ValueT* operator->()
        {
            return observer_->operator->();
        }
        SharedObserver(ValueT const& value)
            : observer_{std::make_shared<Observer<ValueT>>(value)}
        {
        }
        SharedObserver(ValueT&& value)
            : observer_{std::make_shared<Observer<ValueT>>(std::move(value))}
        {}
        SharedObserver()
            : observer_{}
        {}
        SharedObserver& operator=(ValueT const& value)
        {
            *observer_ = value;
            return *this; 
        }
        void update()
        {
            return observer_->update();
        }
        void subscribe(Attributes::GenericAttribute* attribute)
        {
            observer_->subscribe(attribute);
        }
        void unsubscribe(Attributes::GenericAttribute* attribute)
        {
            observer_->unsubscribe(attribute);
        }
        operator ValueT&()
        {
            return static_cast <ValueT&>(*observer_);
        }
    private:
        std::shared_ptr <Observer<ValueT>> observer_;
    };
}