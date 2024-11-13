#ifndef RAN_INT_HPP
#define RAN_INT_HPP

#include <type_traits>
#include <cstdint>
#include <climits>

namespace ran {

// Rotate Left (ROL)
template <size_t n, typename T>
constexpr inline T rol(T x) {
    static_assert(0 < n && n < sizeof(T) * CHAR_BIT, "bounds");
    static_assert(std::is_unsigned<T>::value, "signed");
    return (x << n) | (x >> (sizeof(T) * CHAR_BIT - n));
}

// Rotate Right (ROR)
template <size_t n, typename T>
constexpr inline T ror(T x) {
    static_assert(0 < n && n < sizeof(T) * CHAR_BIT, "bounds");
    static_assert(std::is_unsigned<T>::value, "signed");
    return (x >> n) | (x << (sizeof(T) * CHAR_BIT - n));
}

// Arithmetic shift right (SAR)
template <size_t n, typename T>
constexpr inline T sar(T x) {
    static_assert(0 < n && n < sizeof(T) * CHAR_BIT, "bounds");
    static_assert(std::is_scalar<T>::value, "type");
    using S = std::make_signed_t<T>;
    return S(x) >> n;
}

}

#endif