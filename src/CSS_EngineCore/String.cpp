#include "String.h"

namespace css
{
	String::String() : _length(0), _data(nullptr) {}

	String::String(const char *str) : _length(_getStringLiteralLength(str)), _data(new char[_length + 1])
	{
		_copyStringData(str, _length);
	}

	String::String(const String &other) : _length(other._length), _data(new char[other._length + 1])
	{
		_copyStringData(other._data, _length);
	}

	String::String(String &&other) : _length(other._length), _data(other._data)
	{
		other._length = 0;
		other._data = nullptr;
	}

	String::~String()
	{
		delete[] _data;
	}

	std::size_t String::GetLength() const
	{
		return _length;
	}

	const char *String::GetData() const
	{
		return _data;
	}

	String String::operator+(const String &other) const
	{
		String concat;
		concat._length = _length + other._length;
		concat._data = new char[concat._length + 1];
		concat._copyStringData(_data, _length);
		concat._copyStringData(other._data, other._length, _length);

		return concat;
	}

	void String::_copyStringData(const char *str, std::size_t len, std::size_t offset)
	{
		std::size_t i = 0;
		for (; i < len && str[i]; i++)
		{
			_data[i + offset] = str[i];
		}
		_data[i + offset] = '\0';
	}

	std::size_t String::_getStringLiteralLength(const char *str)
	{
		std::size_t length = 0;
		while (*str++)
		{
			length++;
		}

		return length;
	}

	std::ostream &operator<<(std::ostream &os, const String &s)
	{
		return os << s._data;
	}
}