#pragma once
#include <utility>
#include <stdexcept>
#include <cstddef>

namespace css
{
	template <typename T>
	class LinkedList
	{
	private:
		class Node
		{
		public:
			Node(const T &data) : data(data), prev(nullptr), next(nullptr) {}

			Node(const T &data, Node *previous) : data(data), prev(previous), next(nullptr) {}

			Node(T &&data) : data(std::move(data)), prev(nullptr), next(nullptr) {}

			Node(T &&data, Node *previous) : data(std::move(data)), prev(previous), next(nullptr) {}

			T data;
			Node *prev;
			Node *next;
		};

	public:
		LinkedList() : _length(0), _first(nullptr), _last(nullptr) {}

		~LinkedList()
		{
			if (_first == nullptr)
			{
				return;
			}

			Node *current = _first->next;
			while (current != nullptr)
			{
				delete current->prev;
				current = current->next;
			}

			delete _last;
		}

		std::size_t GetLength() const
		{
			return _length;
		}

		void Add(const T &data)
		{
			if (_first == nullptr)
			{
				_first = new Node(data);
				_last = _first;
			}
			else
			{
				_last->next = new Node(data, _last);
				_last = _last->next;
			}

			_length++;
		}

		void Add(T &&data)
		{
			if (_first == nullptr)
			{
				_first = new Node(std::move(data));
			}
			else
			{
				_last->next = new Node(std::move(data), _last);
				_last = _last->next;
			}

			_length++;
		}

		const T &operator[](std::size_t index) const
		{
			if (index >= _length)
			{
				throw std::out_of_range("Index out of Linked List range");
			}
			else if (index < _length / 2)
			{
				Node *current = _first;
				while (index > 0)
				{
					current = current->next;
					index--;
				}

				return current->data;
			}
			else
			{
				Node *current = _last;
				index = _length - index - 1;
				while (index > 0)
				{
					current = current->prev;
					index--;
				}

				return current->data;
			}
		}

	private:
		std::size_t _length;
		Node *_first;
		Node *_last;
	};
}
