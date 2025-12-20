#pragma once

#ifdef _OPENMP
#include <omp.h>
#endif

#include <cstdint>
#include <string>

enum class Kind : std::uint8_t { Static, Dynamic };

class InputQuery {
  public:
    InputQuery() = default;
    ~InputQuery() = default;

    void set_n(std::uint64_t n);
    [[nodiscard]] std::uint64_t get_n() const;
    void set_output_file(const std::string& output_file);
    [[nodiscard]] std::string get_output_file() const;
    void set_realization(std::uint64_t realization);
    [[nodiscard]] std::uint64_t get_realization() const;
    void set_threads(std::uint64_t threads);
    [[nodiscard]] std::uint64_t get_threads() const;
    void set_kind(Kind kind);
    [[nodiscard]] Kind get_kind() const;
    void set_chunk_size(std::uint64_t chunk_size);
    [[nodiscard]] std::uint64_t get_chunk_size() const;

  private:
    std::uint64_t m_N;
    std::string m_output_file;
    std::uint64_t m_realization;
    std::uint64_t m_threads = static_cast<std::uint64_t>(omp_get_max_threads());
    Kind m_kind;
    std::uint64_t m_chunk_size;
};