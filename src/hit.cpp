// NOLINTBEGIN

#include "hit.h"

#include <cmath>

bool hit_test(float x, float y, float z) {
    const float a = 2.0F;

    float right_part = (x * x * x * x) / (4.0F * a * a) - x * x - y * y;

    if (right_part < 0.0F) {
        return false;
    }

    float left_part = z * z;

    return left_part <= right_part;
}
const float* get_axis_range() {
    static const float range[6] = {-2.0F, 2.0F, -2.0F, 2.0F, 0.0F, 2.0F};
    return range;
}

// NOLINTEND
