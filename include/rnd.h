#pragma once

#include <cstdint>

//NOLINTBEGIN
class Rnd {
  private:
    std::uint64_t s[4];

    static inline std::uint64_t rotl(std::uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }

  public:
    explicit Rnd(std::uint64_t seed);

    std::uint64_t next();

    float next_float();
};

//NOLINTEND