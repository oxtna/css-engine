#pragma once
#include "String.h"
#include "Token.h"

namespace css {

class Lexer
{
  public:
    Lexer(const String& text);
    Lexer(String&& text);
    Lexer(const Lexer& rhs);
    Lexer(Lexer&& rhs);
    ~Lexer() = default;
    Lexer& operator=(const Lexer& rhs);
    Lexer& operator=(Lexer&& rhs);
    Token NextToken();
    String GetSubstring(std::size_t start, std::size_t end) const;

  private:
    String _text;
    std::size_t _index;

    char _Peek() const;
    char _GetChar();
    void _SkipWhitespace();
    static bool _IsWhitespace(char c);
    static bool _IsSpecial(char c);
};

}
