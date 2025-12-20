// NOLINTBEGIN

#include "hit.h"

#include <cmath>

bool hit_test(float x, float y, float z) {
    const float a = 2.0F;

    double left_part = (x * x * x * x - a * x * x * x);
    double right_part = -a * a * (y * y + z * z);

    return left_part <= right_part;
}
const float* get_axis_range() {
    static const float range[6] = {-2.0F, 2.0F, -2.0F, 2.0F, -2.0F, 2.0F};
    return range;
}

// NOLINTEND