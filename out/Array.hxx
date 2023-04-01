#pragma once
#include <cstddef>
#include <stdexcept>

namespace css {

template <typename T, std::size_t N>
class Array
{
  public:
    using Iterator = T*;
    using ConstIterator = const T*;

    Array() : _occupied(0), _data() {}

    Array(const Array& rhs) : _occupied(rhs._occupied), _data() {
        for (std::size_t i = 0; i < _occupied; i++) {
            _data[i] = rhs._data[i];
        }
    }

    Array(Array&& rhs) : _occupied(rhs._occupied), _data() {
        rhs._occupied = 0;
        std::swap(_data, rhs._data);
    }

    ~Array() = default;

    constexpr std::size_t GetMaxLength() const { return N; }

    std::size_t GetLength() const { return _occupied; }

    const T* GetRawData() const { return _data; }

    bool IsEmpty() const { return _occupied == 0; }

    bool IsFull() const { return _occupied == N; }

    void Add(const T& data) {
        if (_occupied == N) {
            throw;
        }

        _data[_occupied] = data;
        _occupied++;
    }

    void Add(T&& data) {
        if (_occupied == N) {
            throw;
        }

        _data[_occupied] = std::move(data);
        _occupied++;
    }

    void Pop() {
        if (_occupied == 0) {
            throw;
        }

        _occupied--;
    }

    void Remove(std::size_t index) {
        if (index >= _occupied) {
            throw;
        }

        _occupied--;
        for (std::size_t i = index; i < _occupied; i++) {
            _data[i] = std::move(_data[i + 1]);
        }
    }

    Iterator begin() { return Iterator(_data); }

    ConstIterator begin() const { return ConstIterator(_data); }

    Iterator end() { return Iterator(_data + _occupied); }

    ConstIterator end() const { return ConstIterator(_data + _occupied); }

    const T& operator[](std::size_t index) const {
        if (index >= _occupied) {
            throw std::out_of_range("Index out of Array range");
        }

        return _data[index];
    }

    T& operator[](std::size_t index) {
        if (index >= _occupied) {
            throw std::out_of_range("Index out of Array range");
        }

        return _data[index];
    }

    Array& operator=(const Array& rhs) {
        Array tmp = rhs;
        std::swap(_occupied, tmp._occupied);
        std::swap(_data, tmp._data);
        return *this;
    }

    Array& operator=(Array&& rhs) {
        std::swap(_occupied, rhs._occupied);
        std::swap(_data, rhs._data);
        return *this;
    }

  private:
    std::size_t _occupied;
    T _data[N];
};

}
