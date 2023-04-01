#pragma once
#include <cstddef>
#include <cstdlib>

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
        for (std::size_t i = 0; i < _occupied; i++) {
            _data[i] = (T &&)(rhs._data[i]);
        }
        rhs._occupied = 0;
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

        _data[_occupied] = (T &&)(data);
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
            _data[i] = (T &&)(_data[i + 1]);
        }
    }

    Iterator begin() { return Iterator(_data); }

    ConstIterator begin() const { return ConstIterator(_data); }

    Iterator end() { return Iterator(_data + _occupied); }

    ConstIterator end() const { return ConstIterator(_data + _occupied); }

    const T& operator[](std::size_t index) const {
        if (index >= _occupied) {
            std::exit(EXIT_FAILURE);
        }

        return _data[index];
    }

    T& operator[](std::size_t index) {
        if (index >= _occupied) {
            std::exit(EXIT_FAILURE);
        }

        return _data[index];
    }

    Array& operator=(const Array& rhs) {
        _occupied = rhs._occupied;
        for (std::size_t i = 0; i < rhs._occupied; i++) {
            _data[i] = rhs._data[i];
        }
        return *this;
    }

    Array& operator=(Array&& rhs) {
        T tmpData;
        for (std::size_t i = 0; i < N; i++) {
            tmpData = (T &&)(_data[i]);
            _data[i] = (T &&)(rhs._data[i]);
            rhs._data[i] = (T &&)(tmpData);
        }
        std::size_t tmpOccupied = _occupied;
        _occupied = rhs._occupied;
        rhs._occupied = tmpOccupied;
        return *this;
    }

  private:
    std::size_t _occupied;
    T _data[N];
};

}
