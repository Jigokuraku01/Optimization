#include "hit.h"
#include "realizations.hpp"
#include "rnd.h"
double Realization1::execute(const InputQuery& query) {
    const float* axis_range = get_axis_range();
    const float x_min = axis_range[0];
    const float x_max = axis_range[1];
    const float y_min = axis_range[2];
    const float y_max = axis_range[3];
    const float z_min = axis_range[4];
    const float z_max = axis_range[5];

    const float del_x = x_max - x_min;
    const float del_y = y_max - y_min;
    const float del_z = z_max - z_min;

    Rnd rnd(123456789);
    std::uint64_t hit_count = 0;
    const std::uint64_t max_n = query.get_n();
    for (std::uint64_t i = 0; i < max_n; ++i) {
        const float tmp_x = x_min + del_x * rnd.next_float();
        const float tmp_y = y_min + del_y * rnd.next_float();
        const float tmp_z = z_min + del_z * rnd.next_float();
        if (hit_test(tmp_x, tmp_y, tmp_z)) {
            ++hit_count;
        }
    }

    return static_cast<double>(hit_count) / static_cast<double>(max_n) * del_x *
           del_y * del_z;
}