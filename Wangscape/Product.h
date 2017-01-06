#pragma once
#include <vector>
#include <functional>
#include "ProductIterator.h"

template<typename T, typename Container>
class Product
{
public:
    typedef ProductIterator const_iterator;
    Product(const Container<T>& container_, size_t power);
    <const Container<T>& container;
    ProductIterator cbegin();
    ProductIterator cend();
};

template<typename T, typename Container>
inline Product<T, Container>::Product(const Container<T>& container_, size_t power) :
    container(container_)
{
}

template<typename T, typename Container>
inline ProductIterator Product<T, Container>::cbegin()
{
    ProductIterator pi;
    for (const auto container : containers)
    {
        pi.components.push_back(container.cbegin());
    }
    return pi;
}

template<typename T, typename Container>
inline ProductIterator Product<T, Container>::cend()
{
    ProductIterator pi;
    for (const auto container : containers)
    {
        pi.components.push_back(container.cend());
    }
    return pi;
}
