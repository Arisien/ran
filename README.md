# Ran

High performance C++ library. Compatible with GCC x86_64

## Vector Arithmetic

Vec3 is stored as 4 packed 32 bit floats, alligned on 16 byte boundary. Vec3 structures are loaded into XMM register for performant operations with SSE intrinsics. Last float is zeroed out for proper horizontal addition. Double precision vectors are planned with Vec3D structure.

```cpp
#include <ran/Vec3.hpp>

void test () {
    auto v1 = ran::Vec3(1.f, 3.f, 0.f);
    auto v2 = ran::Vec3(0.f, 2.f, 1.f);
    v1.cross(v2);
    if (!v1.zero()) {
        v1.normalize();
    }
}
```

## Integer Operations

Ran supports some common x86 operations that are not provided by C's operators such as rotation (ROR, ROL).

```cpp
uint32_t test (uint32_t x) {
    x = ran::ror<8>(x);
    return x + 5;
}
```