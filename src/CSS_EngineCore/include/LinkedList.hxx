#pragma once
#include "Swap.hxx"
#include <cstddef>
#include <cstdlib>

namespace css {

template <typename T>
class LinkedList
{
  private:
    class Node
    {
      public:
        Node(const T& data) : _data(data), _prev(nullptr), _next(nullptr) {}

        Node(const T& data, Node* previous)
            : _data(data), _prev(previous), _next(nullptr) {}

        Node(T&& data) : _data((T &&)(data)), _prev(nullptr), _next(nullptr) {}

        Node(T&& data, Node* previous)
            : _data((T &&)(data)), _prev(previous), _next(nullptr) {}

        Node* GetPrevious() const { return _prev; }

        void SetPrevious(Node* previous) { _prev = previous; }

        Node* GetNext() const { return _next; }

        void SetNext(Node* next) { _next = next; }

        T& GetData() { return _data; }

        void SetData(const T& data) { _data = data; }

        void SetData(T&& data) { _data = (T &&)(data); }

      private:
        T _data;
        Node* _prev;
        Node* _next;
    };

    class LinkedListIterator
    {
      public:
        using ValueType = T;
        using ReferenceType = ValueType&;
        using PointerType = ValueType*;

        LinkedListIterator(Node* ptr) : _current(ptr) {}

        LinkedListIterator(const LinkedListIterator& rhs) : _current(rhs._current) {}

        LinkedListIterator& operator++() {
            _current = _current->GetNext();
            return *this;
        }

        LinkedListIterator operator++(int) {
            LinkedListIterator iterator = *this;
            ++(*this);
            return iterator;
        }

        LinkedListIterator& operator--() {
            _current = _current->GetPrevious();
            return *this;
        }

        LinkedListIterator operator--(int) {
            LinkedListIterator iterator = *this;
            --(*this);
            return iterator;
        }

        PointerType operator->() const { return &_current->GetData(); }

        ReferenceType operator*() const { return _current->GetData(); }

        bool operator==(const LinkedListIterator& rhs) const {
            return _current == rhs._current;
        }

        bool operator!=(const LinkedListIterator& rhs) const { return !(*this == rhs); }

      private:
        Node* _current;
    };

  public:
    using Iterator = LinkedListIterator;
    using ConstIterator = const LinkedListIterator;

    LinkedList() : _length(0), _first(nullptr), _last(nullptr) {}

    LinkedList(const LinkedList& rhs)
        : _length(rhs._length), _first(nullptr), _last(nullptr) {
        if (_length == 0) {
            return;
        }

        _first = new Node(rhs._first->GetData());
        Node* currentThis = _first;
        Node* currentRhs = rhs._first->GetNext();
        while (currentRhs != nullptr) {
            currentThis->SetNext(new Node(currentRhs->GetData()));
            currentThis = currentThis->GetNext();
            currentRhs = currentRhs->GetNext();
        }

        _last = currentThis;
    }

    LinkedList(LinkedList&& rhs)
        : _length(rhs._length), _first(rhs._first), _last(rhs._last) {
        rhs._length = 0;
        rhs._first = nullptr;
        rhs._last = nullptr;
    }

    ~LinkedList() {
        if (_first == nullptr) {
            return;
        }

        Node* current = _first->GetNext();
        while (current != nullptr) {
            delete current->GetPrevious();
            current = current->GetNext();
        }

        delete _last;
    }

    std::size_t GetLength() const { return _length; }

    void Add(const T& data) {
        if (_first == nullptr) {
            _first = new Node(data);
            _last = _first;
        }
        else {
            _last->SetNext(new Node(data, _last));
            _last = _last->GetNext();
        }

        _length++;
    }

    void Add(T&& data) {
        if (_first == nullptr) {
            _first = new Node((T &&)(data));
            _last = _first;
        }
        else {
            _last->SetNext(new Node((T &&)(data), _last));
            _last = _last->GetNext();
        }

        _length++;
    }

    void Remove(std::size_t index) {
        if (index >= _length) {
            throw;
        }

        Node* toBeDeleted = nullptr;
        if (_length == 1) {
            toBeDeleted = _first;
            _first = _last = nullptr;
        }
        else if (index == 0) {
            toBeDeleted = _first;
            _first = _first->GetNext();
            _first->SetPrevious(nullptr);
        }
        else if (index == _length - 1) {
            toBeDeleted = _last;
            _last = _last->GetPrevious();
            _last->SetNext(nullptr);
        }
        else {
            toBeDeleted = _first;
            while (index > 0) {
                toBeDeleted = toBeDeleted->GetNext();
            }

            toBeDeleted->GetPrevious()->SetNext(toBeDeleted->GetNext());
            toBeDeleted->GetNext()->SetPrevious(toBeDeleted->GetPrevious());
        }
        delete toBeDeleted;
        _length--;
    }

    LinkedList& operator=(const LinkedList& rhs) {
        LinkedList tmp = rhs;
        Swap(_length, tmp._length);
        Swap(_first, tmp._first);
        Swap(_last, tmp._last);
        return *this;
    }

    LinkedList& operator=(LinkedList&& rhs) {
        Swap(_length, rhs._length);
        Swap(_first, rhs._first);
        Swap(_last, rhs._last);
        return *this;
    }

    T& operator[](std::size_t index) const {
        if (index >= _length) {
            std::exit(EXIT_FAILURE);
        }
        else if (index < _length / 2) {
            Node* current = _first;
            while (index > 0) {
                current = current->GetNext();
                index--;
            }

            return current->GetData();
        }
        else {
            Node* current = _last;
            index = _length - index - 1;
            while (index > 0) {
                current = current->GetPrevious();
                index--;
            }

            return current->GetData();
        }
    }

    Iterator begin() { return Iterator(_first); }

    ConstIterator begin() const { return ConstIterator(_first); }

    Iterator end() { return Iterator(nullptr); }

    ConstIterator end() const { return ConstIterator(nullptr); }

  private:
    std::size_t _length;
    Node* _first;
    Node* _last;
};

}
