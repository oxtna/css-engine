#pragma once
#include "Array.hxx"
#include "String.h"

bool streq(const char* str1, const char* str2);

css::Array<css::String, 3> splitCommand(const css::String& str);

std::size_t strToN(const css::String& str);
