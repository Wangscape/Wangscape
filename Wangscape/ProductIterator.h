#pragma once
#include <vector>
#include <iterator>

template<typename T, typename Container>
class ProductIterator :
    public std::iterator<std::input_iterator_tag,
                         std::vector<Container<T>::const_iterator>>
{
public:
    ProductIterator() = default;
    std::vector<Container<T>::const_iterator> components;
    ProductIterator& operator++();
    bool operator==(const ProductIterator& other);
    bool operator!=(const ProductIterator& other);
    const vector<Container<T>::const_iterator> operator*();
};
