#include "utility.h"

bool streq(const char* str1, const char* str2) {
    if (str1 == nullptr || str2 == nullptr) {
        return false;
    }

    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }

    if (*str1 != *str2) {
        return false;
    }

    return true;
}

css::Array<css::String, 3> splitCommand(const css::String& str) {
    if (str.Find(',') == -1 || str.Find(',') == str.FindLast(',')) {
        throw;
    }

    css::Array<css::String, 3> array;
    css::String first;
    css::String second;
    css::String last;

    if (str[str.GetLength() - 1] == '*') {
        first = str.GetSubstring(0, str.Find(','));
        second = str.GetSubstring(str.Find(',') + 1, str.FindLast(','));
        last = str.GetSubstring(str.FindLast(',') + 1, str.GetLength());
    }
    else if (str[str.GetLength() - 1] == '?') {
        css::String withoutLast = str.GetSubstring(0, str.FindLast(','));
        first = withoutLast.GetSubstring(0, withoutLast.FindLast(','));
        second = withoutLast.GetSubstring(
            withoutLast.FindLast(',') + 1, withoutLast.GetLength());
        last = str.GetSubstring(str.FindLast(',') + 1, str.GetLength());
    }
    else {
        css::String withoutFirst = str.GetSubstring(str.Find(',') + 1, str.GetLength());
        first = str.GetSubstring(0, str.Find(','));
        second = withoutFirst.GetSubstring(0, withoutFirst.Find(','));
        last = withoutFirst.GetSubstring(
            withoutFirst.Find(',') + 1, withoutFirst.GetLength());
    }

    array.Add((css::String &&)(first));
    array.Add((css::String &&)(second));
    array.Add((css::String &&)(last));
    return array;
}

std::size_t strToN(const css::String& string) {
    const char* str = string.GetData();
    if (str == nullptr) {
        throw;
    }

    std::size_t n = 0;
    while (*str != '\0') {
        n *= 10;
        n += *str - '0';
        str++;
    }

    return n;
}
