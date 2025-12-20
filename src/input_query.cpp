#include "input_query.hpp"
void InputQuery::set_n(std::uint64_t n) {
    m_N = n;
}
std::uint64_t InputQuery::get_n() const {
    return m_N;
}
void InputQuery::set_output_file(const std::string& output_file) {
    m_output_file = output_file;
}
std::string InputQuery::get_output_file() const {
    return m_output_file;
}
void InputQuery::set_realization(std::uint64_t realization) {
    m_realization = realization;
}
std::uint64_t InputQuery::get_realization() const {
    return m_realization;
}
void InputQuery::set_threads(std::uint64_t threads) {
    m_threads = threads;
}
std::uint64_t InputQuery::get_threads() const {
    return m_threads;
}
void InputQuery::set_kind(Kind kind) {
    m_kind = kind;
}
Kind InputQuery::get_kind() const {
    return m_kind;
}
void InputQuery::set_chunk_size(std::uint64_t chunk_size) {
    m_chunk_size = chunk_size;
}
std::uint64_t InputQuery::get_chunk_size() const {
    return m_chunk_size;
}