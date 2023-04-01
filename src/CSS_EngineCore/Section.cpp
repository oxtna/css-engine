#include "Section.h"
#include "Swap.hxx"

namespace css {

Section::Section(const Section& rhs)
    : _selectors(rhs._selectors), _attributes(rhs._attributes) {
}

Section::Section(Section&& rhs)
    : _selectors((LinkedList<String> &&)(rhs._selectors)),
      _attributes((LinkedList<Attribute> &&)(rhs._attributes)) {
    rhs._selectors = LinkedList<String>();
    rhs._attributes = LinkedList<Attribute>();
}

bool Section::HasSelector(const String& selector) const {
    for (const auto& sel : _selectors) {
        if (sel == selector) {
            return true;
        }
    }

    return false;
}

bool Section::HasAttribute(const String& attributeName) const {
    for (const auto& attr : _attributes) {
        if (attr.name == attributeName) {
            return true;
        }
    }

    return false;
}

String Section::GetSelector(std::size_t index) const {
    if (index >= _selectors.GetLength()) {
        return String();
    }

    return _selectors[index];
}

String Section::GetAttributeValue(const String& attributeName) const {
    for (const auto& attribute : _attributes) {
        if (attribute.name == attributeName) {
            return attribute.value;
        }
    }

    return String();
}

std::size_t Section::GetSelectorCount() const {
    return _selectors.GetLength();
}

std::size_t Section::GetAttributeCount() const {
    return _attributes.GetLength();
}

void Section::AddSelector(const String& selector) {
    _selectors.Add(selector);
}

void Section::AddSelector(String&& selector) {
    _selectors.Add((String &&)(selector));
}

void Section::AddAttribute(const Attribute& attribute) {
    for (auto& attr : _attributes) {
        if (attr.name == attribute.name) {
            attr.value = attribute.value;
            return;
        }
    }

    _attributes.Add(attribute);
}

void Section::AddAttribute(Attribute&& attribute) {
    for (auto& attr : _attributes) {
        if (attr.name == attribute.name) {
            attr.value = (String &&)(attribute.value);
            return;
        }
    }

    _attributes.Add((Attribute &&)(attribute));
}

void Section::RemoveAttribute(const String& attributeName) {
    for (std::size_t i = 0; i < _attributes.GetLength(); i++) {
        if (_attributes[i].name == attributeName) {
            _attributes.Remove(i);
            return;
        }
    }
}

Section& Section::operator=(const Section& rhs) {
    Section tmp = rhs;
    Swap(_selectors, tmp._selectors);
    Swap(_attributes, tmp._attributes);
    return *this;
}

Section& Section::operator=(Section&& rhs) {
    Swap(_selectors, rhs._selectors);
    Swap(_attributes, rhs._attributes);
    return *this;
}

}
