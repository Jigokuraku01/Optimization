#include "hit.h"
#include "my_exception.hpp"
#include "realizations.hpp"
#include "rnd.hpp"
#include <vector>

double Realization2::execute(const InputQuery& query) {
    switch (query.get_kind()) {
        case Kind::Static:
            return static_execute(query);
        case Kind::Dynamic:
            return dynamic_execute(query);
        default:
            throw MyException(EXIT_FAILURE, "unknown kind");
    }
}

double Realization2::static_execute(const InputQuery& query) {
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

    std::uint64_t total_hit_count = 0;
    const std::uint64_t max_n = query.get_n();

    std::vector<std::uint64_t> local_hits(query.get_threads(), 0ULL);
#pragma omp parallel num_threads(static_cast<int>(query.get_threads()))
    {
        const auto tid = static_cast<std::uint32_t>(omp_get_thread_num());
        Rnd rnd(123456789 +
                static_cast<std::uint64_t>(omp_get_thread_num()) * 1000003);
        std::uint64_t hit_count = 0;

#pragma omp for schedule(static, static_cast<int>(query.get_chunk_size()))
        for (std::uint64_t i = 0; i < max_n; ++i) {
            const float tmp_x = x_min + del_x * rnd.next_float();
            const float tmp_y = y_min + del_y * rnd.next_float();
            const float tmp_z = z_min + del_z * rnd.next_float();
            if (hit_test(tmp_x, tmp_y, tmp_z)) {
                ++hit_count;
            }
        }

        local_hits[tid] = hit_count;
    }

    for (std::uint64_t i = 0; i < query.get_threads(); ++i) {
        total_hit_count += local_hits[i];
    }
    return static_cast<double>(total_hit_count) / static_cast<double>(max_n) *
           del_x * del_y * del_z;
}

double Realization2::dynamic_execute(const InputQuery& query) {
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

    std::uint64_t total_hit_count = 0;
    const std::uint64_t max_n = query.get_n();

    std::vector<std::uint64_t> local_hits(query.get_threads(), 0ULL);
#pragma omp parallel num_threads(static_cast<int>(query.get_threads()))
    {
        const auto tid = static_cast<std::uint32_t>(omp_get_thread_num());
        Rnd rnd(123456789 +
                static_cast<std::uint64_t>(omp_get_thread_num()) * 1000003);
        std::uint64_t hit_count = 0;

#pragma omp for schedule(dynamic, static_cast<int>(query.get_chunk_size()))
        for (std::uint64_t i = 0; i < max_n; ++i) {
            const float tmp_x = x_min + del_x * rnd.next_float();
            const float tmp_y = y_min + del_y * rnd.next_float();
            const float tmp_z = z_min + del_z * rnd.next_float();
            if (hit_test(tmp_x, tmp_y, tmp_z)) {
                ++hit_count;
            }
        }
        local_hits[tid] = hit_count;
    }

    for (std::uint64_t i = 0; i < query.get_threads(); ++i) {
        total_hit_count += local_hits[i];
    }
    return static_cast<double>(total_hit_count) / static_cast<double>(max_n) *
           del_x * del_y * del_z;
}