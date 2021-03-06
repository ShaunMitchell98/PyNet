#pragma once
#include <map>
#include <vector>
#include <typeindex>
#include <stdexcept>
#include <type_traits>
#include "IItem.h"
#include "Item.h"

using namespace std;

namespace PyNet::DI {

    class ItemContainer 
    {
    private:

        map<type_index, IItem*> _items;

    public:

        static auto factory() {
            return new ItemContainer();
        }

        ~ItemContainer() {

            for (auto& item : _items) {
                item.second->Reset();
                delete item.second;
            }
        }

        template<class RequiredType>
        Item<RequiredType>& Add() 
        {
            auto key = type_index(typeid(RequiredType));
            auto item = new Item<RequiredType>();
            _items.insert({ key, item  });
            return *item;
        }

        template <class RequiredType>
        Item<RequiredType>& GetItem()
        {
            auto it = _items.find(type_index(typeid(RequiredType)));

            if (it == _items.end())
            {
                throw runtime_error(string("No type ") + typeid(RequiredType).name() + " has been registered with the Container.");
            }

            return *static_cast<Item<RequiredType>*>(it->second);
        }

        void MakeReferencesWeak() {

            for (auto& i : _items) {
                i.second->MakeReferenceWeak();
            }
        }
    };
}