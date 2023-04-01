#pragma once
#include <iostream>
namespace css {

class String
{
  public:
    String();
    String(const String& rhs);
    String(String&& rhs);
    String(const char* str);
    String(const char* str, std::size_t maxLength);
    ~String();
    std::size_t GetLength() const;
    const char* GetData() const;
    String GetSubstring(std::size_t start, std::size_t end) const;
    int Find(char c) const;
    int FindLast(char c) const;
    bool operator==(const String& rhs) const;
    bool operator!=(const String& rhs) const;
    String operator+(const String& rhs) const;
    char operator[](const std::size_t index) const;
    String& operator=(const String& rhs);
    String& operator=(String&& rhs);

  private:
    std::size_t _length;
    char* _data;

    void _CopyStringData(const char* str, std::size_t len, std::size_t offset = 0);

    static std::size_t _GetStringLiteralLength(const char* str);

    friend std::ostream& operator<<(std::ostream& os, const String& s);
};

}
