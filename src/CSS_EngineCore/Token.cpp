#include "Token.h"

namespace css {

Token::Token(TokenType type, std::size_t start, std::size_t end)
    : _type(type), _start(start), _end(end) {
}

TokenType Token::GetType() const {
    return _type;
}

std::size_t Token::GetStart() const {
    return _start;
}

std::size_t Token::GetEnd() const {
    return _end;
}

std::ostream& operator<<(std::ostream& os, TokenType t) {
    switch (t) {
    case TokenType::Invalid:
        return os << "Invalid";
    case TokenType::String:
        return os << "String";
    case TokenType::Comma:
        return os << "Comma";
    case TokenType::Colon:
        return os << "Colon";
    case TokenType::Semicolon:
        return os << "Semicolon";
    case TokenType::OpeningBrace:
        return os << "OpeningBrace";
    case TokenType::ClosingBrace:
        return os << "ClosingBrace";
    case TokenType::End:
        return os << "End";
    default:
        return os;
    }
}

std::ostream& operator<<(std::ostream& os, const Token& t) {
    return os << "Token(" << t.GetType() << ", " << t.GetStart() << ", " << t.GetEnd()
              << ")";
}
}
