#pragma once

namespace css {

template <typename T>
void Swap(T& lhs, T& rhs) {
    T tmp = (T &&)(lhs);
    lhs = (T &&)(rhs);
    rhs = (T &&)(tmp);
}

}
