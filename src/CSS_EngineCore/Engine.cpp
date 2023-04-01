#include "Engine.h"

#define INDEX_CAST(e) (static_cast<std::size_t>(e))

using EngineState = css::Engine::EngineState;

// as long as TokenType::End is the last value in the enum this works
static const std::size_t TOKEN_TYPE_COUNT =
    static_cast<std::size_t>(css::TokenType::End) + 1;

static const EngineState _STATE_TRANSFER[][TOKEN_TYPE_COUNT] = {
    {
        // EngineState::OutsideSection
        EngineState::Error,           // TokenType::Invalid
        EngineState::OutsideSection,  // TokenType::String
        EngineState::OutsideSection,  // TokenType::Comma
        EngineState::OutsideSection,  // TokenType::Colon
        EngineState::Error,           // TokenType::Semicolon
        EngineState::AttributeName,   // TokenType::OpeningBrace
        EngineState::Error,           // TokenType::ClosingBrace
        EngineState::End,             // TokenType::End
    },
    {
        // EngineState::AttributeName
        EngineState::Error,           // TokenType::Invalid
        EngineState::AttributeName,   // TokenType::String
        EngineState::Error,           // TokenType::Comma
        EngineState::AttributeValue,  // TokenType::Colon
        EngineState::Error,           // TokenType::Semicolon
        EngineState::Error,           // TokenType::OpeningBrace
        EngineState::OutsideSection,  // TokenType::ClosingBrace
        EngineState::Error,           // TokenType::End
    },
    {
        // EngineState::AttributeValue
        EngineState::Error,           // TokenType::Invalid
        EngineState::AttributeValue,  // TokenType::String
        EngineState::AttributeValue,  // TokenType::Comma
        EngineState::Error,           // TokenType::Colon
        EngineState::AttributeName,   // TokenType::Semicolon
        EngineState::Error,           // TokenType::OpeningBrace
        EngineState::OutsideSection,  // TokenType::ClosingBrace
        EngineState::Error,           // TokenType::End
    },
    {
        // EngineState::Entry
        EngineState::Error,           // TokenType::Invalid
        EngineState::OutsideSection,  // TokenType::String
        EngineState::Error,           // TokenType::Comma
        EngineState::OutsideSection,  // TokenType::Colon
        EngineState::Error,           // TokenType::Semicolon
        EngineState::AttributeName,   // TokenType::OpeningBrace
        EngineState::Error,           // TokenType::ClosingBrace
        EngineState::End,             // TokenType::End
    },
};

namespace css {

Engine::Engine() : _list(), _lexer(""), _state(EngineState::Entry) {
}

void Engine::Parse(const String& str) {
    _lexer = Lexer(str);
    _Parse();
}

void Engine::Parse(String&& str) {
    _lexer = Lexer((String &&)(str));
    _Parse();
}

std::size_t Engine::CountSections() const {
    std::size_t count = 0;
    for (const auto& sectionArray : _list) {
        count += sectionArray.GetLength();
    }

    return count;
}

std::size_t Engine::CountSelector(const String& selector) const {
    std::size_t count = 0;
    for (const auto& sectionArray : _list) {
        for (const auto& section : sectionArray) {
            if (section.HasSelector(selector)) {
                count++;
            }
        }
    }

    return count;
}

std::size_t Engine::CountAttribute(const String& attributeName) const {
    std::size_t count = 0;
    for (const auto& sectionArray : _list) {
        for (const auto& section : sectionArray) {
            if (section.HasAttribute(attributeName)) {
                count++;
            }
        }
    }

    return count;
}

int Engine::CountSelectorsInSection(std::size_t sectionIndex) const {
    for (const auto& sectionArray : _list) {
        if (sectionIndex >= sectionArray.GetLength()) {
            sectionIndex -= sectionArray.GetLength();
            continue;
        }

        return sectionArray[sectionIndex].GetSelectorCount();
    }

    return -1;
}

int Engine::CountAttributesInSection(std::size_t sectionIndex) const {
    for (const auto& sectionArray : _list) {
        if (sectionIndex >= sectionArray.GetLength()) {
            sectionIndex -= sectionArray.GetLength();
            continue;
        }

        return sectionArray[sectionIndex].GetAttributeCount();
    }

    return -1;
}

String Engine::GetSelectorInSection(
    std::size_t sectionIndex, std::size_t selectorIndex) const {
    for (const auto& sectionArray : _list) {
        if (sectionIndex >= sectionArray.GetLength()) {
            sectionIndex -= sectionArray.GetLength();
            continue;
        }

        return sectionArray[sectionIndex].GetSelector(selectorIndex);
    }

    return String();
}

String Engine::GetAttributeValueInSection(
    std::size_t sectionIndex, const String& attributeName) const {
    for (const auto& sectionArray : _list) {
        if (sectionIndex >= sectionArray.GetLength()) {
            sectionIndex -= sectionArray.GetLength();
            continue;
        }

        return sectionArray[sectionIndex].GetAttributeValue(attributeName);
    }

    return String();
}

String Engine::GetAttributeValueOfSelector(
    const String& selector, const String& attributeName) const {
    for (int i = _list.GetLength() - 1; i >= 0; i--) {
        const auto& sectionArray = _list[i];
        for (int j = sectionArray.GetLength() - 1; j >= 0; j--) {
            const auto& section = sectionArray[j];
            if (section.HasSelector(selector)) {
                return section.GetAttributeValue(attributeName);
            }
        }
    }

    return String();
}

bool Engine::DeleteSection(std::size_t sectionIndex) {
    for (std::size_t i = 0; i < _list.GetLength(); i++) {
        if (sectionIndex >= _list[i].GetLength()) {
            sectionIndex -= _list[i].GetLength();
            continue;
        }

        _list[i].Remove(sectionIndex);
        if (_list[i].GetLength() == 0) {
            _list.Remove(i);
        }
        return true;
    }

    return false;
}

bool Engine::DeleteAttributeFromSection(
    std::size_t sectionIndex, const String& attributeName) {
    for (std::size_t i = 0; i < _list.GetLength(); i++) {
        if (sectionIndex >= _list[i].GetLength()) {
            sectionIndex -= _list[i].GetLength();
            continue;
        }

        if (_list[i][sectionIndex].HasAttribute(attributeName)) {
            _list[i][sectionIndex].RemoveAttribute(attributeName);
            if (_list[i][sectionIndex].GetAttributeCount() == 0) {
                _list[i].Remove(sectionIndex);
                if (_list[i].GetLength() == 0) {
                    _list.Remove(i);
                }
            }
            return true;
        }
        else {
            return false;
        }
    }

    return false;
}

EngineState Engine::_GetNextState(TokenType tokenType) const {
    return _STATE_TRANSFER[INDEX_CAST(_state)][INDEX_CAST(tokenType)];
}

void Engine::_Parse() {
    std::size_t startingIndex = 0;
    std::size_t endingIndex = 0;
    Token previousToken = Token(TokenType::Invalid, 0, 0);
    Section section;
    Attribute attribute;

    for (Token currentToken = _lexer.NextToken();
         currentToken.GetType() != TokenType::End;
         currentToken = _lexer.NextToken()) {
        EngineState nextState = _GetNextState(currentToken.GetType());
        if (nextState == EngineState::Error) {
            throw;
        }

        if (_state == EngineState::OutsideSection) {
            if (previousToken.GetType() == TokenType::Comma ||
                previousToken.GetType() == TokenType::ClosingBrace) {
                startingIndex = currentToken.GetStart();
            }

            if (currentToken.GetType() == TokenType::Colon ||
                currentToken.GetType() == TokenType::String) {
                endingIndex = currentToken.GetEnd();
            }
            else if (
                currentToken.GetType() == TokenType::Comma ||
                currentToken.GetType() == TokenType::OpeningBrace) {
                String selector = _lexer.GetSubstring(startingIndex, endingIndex);
                if (selector.GetLength() != 0) {
                    section.AddSelector(_lexer.GetSubstring(startingIndex, endingIndex));
                }
            }
            else
                throw;
        }

        else if (_state == EngineState::AttributeName) {
            if (previousToken.GetType() == TokenType::OpeningBrace ||
                previousToken.GetType() == TokenType::Semicolon) {
                startingIndex = currentToken.GetStart();
            }

            if (currentToken.GetType() == TokenType::String) {
                endingIndex = currentToken.GetEnd();
            }
            else if (currentToken.GetType() == TokenType::Colon) {
                attribute.name = _lexer.GetSubstring(startingIndex, endingIndex);
            }
            else if (
                currentToken.GetType() == TokenType::ClosingBrace &&
                (previousToken.GetType() == TokenType::String ||
                 previousToken.GetType() == TokenType::Semicolon ||
                 previousToken.GetType() == TokenType::OpeningBrace)) {
                _AddSection((Section &&)(section));
                section = Section();
            }
            else
                throw;
        }

        else if (_state == EngineState::AttributeValue) {
            if (previousToken.GetType() == TokenType::Colon) {
                if (!(currentToken.GetType() == TokenType::String)) {
                    throw;
                }

                startingIndex = currentToken.GetStart();
            }

            if (currentToken.GetType() == TokenType::String ||
                currentToken.GetType() == TokenType::Comma) {
                endingIndex = currentToken.GetEnd();
            }
            else if (
                currentToken.GetType() == TokenType::Semicolon ||
                currentToken.GetType() == TokenType::ClosingBrace) {
                attribute.value = _lexer.GetSubstring(startingIndex, endingIndex);
                section.AddAttribute((Attribute &&)(attribute));
                attribute = Attribute();
            }

            if (currentToken.GetType() == TokenType::ClosingBrace) {
                _AddSection((Section &&)(section));
                section = Section();
            }
        }

        else if (_state == EngineState::Entry) {
            if (currentToken.GetType() == TokenType::String ||
                currentToken.GetType() == TokenType::Colon) {
                startingIndex = currentToken.GetStart();
                endingIndex = currentToken.GetEnd();
            }
            else if (currentToken.GetType() == TokenType::End) {
                break;
            }
            else if (!(currentToken.GetType() == TokenType::OpeningBrace))
                throw;
        }

        previousToken = currentToken;
        _state = nextState;
    }
}

void Engine::_AddSection(Section&& section) {
    if (_list.GetLength() == 0 || _list[_list.GetLength() - 1].IsFull()) {
        _list.Add(SectionArray());
    }
    auto& lastSectionArray = _list[_list.GetLength() - 1];
    lastSectionArray.Add((Section &&)(section));
}

}
