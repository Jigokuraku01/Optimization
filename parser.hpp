#pragma once
#include "input_query.hpp"
#include <vector>

class Parser {
  public:
    Parser() = delete;
    static InputQuery parse(std::vector<std::string> args);
};