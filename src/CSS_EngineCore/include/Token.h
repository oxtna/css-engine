#pragma once
#include <iostream>

namespace css {

enum class TokenType {
    Invalid,
    String,
    Comma,
    Colon,
    Semicolon,
    OpeningBrace,
    ClosingBrace,
    End,
};

std::ostream& operator<<(std::ostream& os, TokenType t);

class Token
{
  public:
    Token(TokenType type, std::size_t start, std::size_t end);
    Token(const Token& rhs) = default;
    ~Token() = default;
    TokenType GetType() const;
    std::size_t GetStart() const;
    std::size_t GetEnd() const;

  private:
    TokenType _type;
    std::size_t _start;
    std::size_t _end;

    friend std::ostream& operator<<(std::ostream& os, const Token& t);
};

}
