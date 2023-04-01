#pragma once
#include "Array.hxx"
#include "Lexer.h"
#include "LinkedList.hxx"
#include "Section.h"

namespace css {

class Engine
{
  public:
    enum class EngineState {
        OutsideSection,
        AttributeName,
        AttributeValue,
        Entry,
        Error,
        End,
    };

  public:
    Engine();
    Engine(const Engine& rhs) = delete;
    Engine(Engine&& rhs) = delete;
    ~Engine() = default;
    void Parse(const String& str);
    void Parse(String&& str);
    std::size_t CountSections() const;
    std::size_t CountSelector(const String& selector) const;
    std::size_t CountAttribute(const String& attributeName) const;
    int CountSelectorsInSection(std::size_t sectionIndex) const;
    int CountAttributesInSection(std::size_t sectionIndex) const;
    String
        GetSelectorInSection(std::size_t sectionIndex, std::size_t selectorIndex) const;
    String GetAttributeValueInSection(
        std::size_t sectionIndex, const String& attributeName) const;
    String GetAttributeValueOfSelector(
        const String& selector, const String& attributeName) const;
    bool DeleteSection(std::size_t sectionIndex);
    bool
        DeleteAttributeFromSection(std::size_t sectionIndex, const String& attributeName);

  private:
    static constexpr std::size_t _ARRAY_SIZE = 8;
    using SectionArray = Array<Section, _ARRAY_SIZE>;
    LinkedList<SectionArray> _list;
    Lexer _lexer;
    EngineState _state;

    EngineState _GetNextState(TokenType tokenType) const;
    void _Parse();
    void _AddSection(Section&& section);
};

}
