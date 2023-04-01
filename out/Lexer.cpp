#include "Lexer.h"

namespace css {

Lexer::Lexer(const String& text) : _text(text), _index(0) {
}

Lexer::Lexer(String&& text) : _text(std::move(text)), _index(0) {
}

Lexer::Lexer(const Lexer& rhs) : _text(rhs._text), _index(rhs._index) {
}

Lexer::Lexer(Lexer&& rhs) : _text(std::move(rhs._text)), _index(rhs._index) {
    rhs._text = String();
    rhs._index = 0;
}

Lexer& Lexer::operator=(const Lexer& rhs) {
    Lexer tmp = rhs;
    std::swap(_text, tmp._text);
    std::swap(_index, tmp._index);
    return *this;
}

Lexer& Lexer::operator=(Lexer&& rhs) {
    std::swap(_text, rhs._text);
    std::swap(_index, rhs._index);
    return *this;
}

Token Lexer::NextToken() {
    _SkipWhitespace();
    if (_index == _text.GetLength()) {
        return Token(TokenType::End, _index, _index);
    }

    std::size_t start = _index;
    TokenType tokenType = TokenType::Invalid;
    char c = _GetChar();
    if (c == ',') {
        tokenType = TokenType::Comma;
    }
    else if (c == ':') {
        tokenType = TokenType::Colon;
    }
    else if (c == ';') {
        tokenType = TokenType::Semicolon;
    }
    else if (c == '{') {
        tokenType = TokenType::OpeningBrace;
    }
    else if (c == '}') {
        tokenType = TokenType::ClosingBrace;
    }
    else if (c != '\0') {
        tokenType = TokenType::String;
        c = _GetChar();
        while (_index < _text.GetLength() && !_IsWhitespace(c) && !_IsSpecial(c)) {
            c = _GetChar();
        }
        _index--;
    }

    return Token(tokenType, start, _index);
}

String Lexer::GetSubstring(std::size_t start, std::size_t end) const {
    return _text.GetSubstring(start, end);
}

char Lexer::_Peek() const {
    return _text[_index];
}

char Lexer::_GetChar() {
    if (_index == _text.GetLength()) {
        return '\0';
    }

    return _text[_index++];
}

void Lexer::_SkipWhitespace() {
    while (_text.GetLength() != _index && _IsWhitespace(_text[_index])) {
        _index++;
    }
}

bool Lexer::_IsWhitespace(char c) {
    switch (c) {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        return true;
    default:
        return false;
    }
}

bool Lexer::_IsSpecial(char c) {
    switch (c) {
    case ',':
    case ':':
    case ';':
    case '{':
    case '}':
        return true;
    default:
        return false;
    }
}

}
