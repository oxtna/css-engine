#pragma once

template <typename T>
void log(const css::String& command, const T& output) {
    std::cout << command << " == " << output << std::endl;
}

template <typename T>
void log(const css::String& command, T&& output) {
    std::cout << command << " == " << std::move(output) << std::endl;
}
