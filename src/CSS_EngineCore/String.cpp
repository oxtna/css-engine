#include "String.h"
#include "Swap.hxx"
#include <cstdlib>

namespace css {

String::String() : _length(0), _data(nullptr) {
}

String::String(const char* str)
    : _length(_GetStringLiteralLength(str)),
      _data(_length == 0 ? nullptr : new char[_length + 1]) {
    if (_length > 0) {
        _CopyStringData(str, _length);
    }
}

String::String(const char* str, std::size_t maxLength)
    : _length(
          _GetStringLiteralLength(str) > maxLength ? maxLength
                                                   : _GetStringLiteralLength(str)),
      _data(_length == 0 ? nullptr : new char[_length + 1]) {
    if (_length > 0) {
        _CopyStringData(str, _length);
    }
}

String::String(const String& rhs)
    : _length(rhs._length), _data(_length == 0 ? nullptr : new char[rhs._length + 1]) {
    if (_length > 0) {
        _CopyStringData(rhs._data, _length);
    }
}

String::String(String&& rhs) : _length(rhs._length), _data(rhs._data) {
    rhs._length = 0;
    rhs._data = nullptr;
}

String::~String() {
    delete[] _data;
}

std::size_t String::GetLength() const {
    return _length;
}

const char* String::GetData() const {
    return _data;
}

String String::GetSubstring(std::size_t start, std::size_t end) const {
    int length = end - start;
    if (length <= 0 || start >= _length) {
        return String();
    }

    return String(_data + start, length);
}

int String::Find(char c) const {
    for (int i = 0; i < _length; i++) {
        if (_data[i] == c) {
            return i;
        }
    }

    return -1;
}

int String::FindLast(char c) const {
    for (int i = _length - 1; i >= 0; i--) {
        if (_data[i] == c) {
            return i;
        }
    }

    return -1;
}

std::size_t String::Count(char c) const {
    std::size_t count = 0;
    for (std::size_t i = 0; i < _length; i++) {
        if (_data[i] == c) {
            count++;
        }
    }

    return count;
}

bool String::operator==(const String& rhs) const {
    if (_data == nullptr && rhs._data == nullptr) {
        return true;
    }
    if (_length != rhs._length) {
        return false;
    }

    const char* thisStr = _data;
    const char* rhsStr = rhs._data;
    while (*thisStr && *rhsStr && *thisStr == *rhsStr) {
        thisStr++;
        rhsStr++;
    }

    if (*thisStr != *rhsStr) {
        return false;
    }

    return true;
}

bool String::operator!=(const String& rhs) const {
    return !(*this == rhs);
}

String String::operator+(const String& rhs) const {
    String concat;
    concat._length = _length + rhs._length;
    concat._data = new char[concat._length + 1];
    concat._CopyStringData(_data, _length);
    concat._CopyStringData(rhs._data, rhs._length, _length);

    return concat;
}

char String::operator[](const std::size_t index) const {
    if (index >= _length) {
        std::exit(EXIT_FAILURE);
    }

    return _data[index];
}

String& String::operator=(const String& rhs) {
    String tmp = rhs;
    Swap(_length, tmp._length);
    Swap(_data, tmp._data);
    return *this;
}

String& String::operator=(String&& rhs) {
    Swap(_length, rhs._length);
    Swap(_data, rhs._data);
    return *this;
}

void String::_CopyStringData(const char* str, std::size_t len, std::size_t offset) {
    std::size_t i = 0;
    while (i < len && str[i]) {
        _data[i + offset] = str[i];
        i++;
    }
    _data[i + offset] = '\0';
}

std::size_t String::_GetStringLiteralLength(const char* str) {
    std::size_t length = 0;
    while (*str++) {
        length++;
    }

    return length;
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    return os << (s._data == nullptr ? "" : s._data);
}
}
