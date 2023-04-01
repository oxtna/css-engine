#pragma once
#include "Attribute.h"
#include "LinkedList.hxx"

namespace css {

class Section
{
  public:
    Section() = default;
    Section(const Section& rhs);
    Section(Section&& rhs);
    bool HasSelector(const String& selector) const;
    bool HasAttribute(const String& attributeName) const;
    String GetSelector(std::size_t index) const;
    String GetAttributeValue(const String& attributeName) const;
    std::size_t GetSelectorCount() const;
    std::size_t GetAttributeCount() const;
    void AddSelector(const String& selector);
    void AddSelector(String&& selector);
    void AddAttribute(const Attribute& attribute);
    void AddAttribute(Attribute&& attribute);
    void RemoveAttribute(const String& attributeName);
    Section& operator=(const Section& rhs);
    Section& operator=(Section&& rhs);

  private:
    LinkedList<String> _selectors;
    LinkedList<Attribute> _attributes;
};

}
