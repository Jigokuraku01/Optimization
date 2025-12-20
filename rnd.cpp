#include "rnd.hpp"
//NOLINTBEGIN

Rnd::Rnd(std::uint64_t seed) {
    s[0] = seed = (seed ^ 0xabcdef1234567890) * 0x123456789abcdef;
    s[1] = seed ^ 0x123456789abcdef;
    s[2] = seed + 0xabcdef123456789;
    s[3] = seed * 0x987654321fedcba;
    for (int i = 0; i < 10; i++) {
        next();
    }
}
std::uint64_t Rnd::next() {
    const std::uint64_t result = s[0] + s[3];
    const std::uint64_t tmp = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= tmp;
    s[3] = rotl(s[3], 45);

    return result;
}

float Rnd::next_float() {
    return (static_cast<float>(next() >> 11) * (1.0F / (1ULL << 53)));
}

//NOLINTEND