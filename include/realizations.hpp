#pragma once

#include "input_query.hpp"
#ifdef _OPENMP
#include <omp.h>
#endif
class Realization1 {
  public:
    Realization1() = delete;
    static double execute(const InputQuery& query);
};
class Realization2 {
  public:
    Realization2() = delete;
    static double execute(const InputQuery& query);

  private:
    static double static_execute(const InputQuery& query);
    static double dynamic_execute(const InputQuery& query);
};
class Realization3 {
  public:
    Realization3() = delete;
    static double execute(const InputQuery& query);

  private:
    static double static_execute(const InputQuery& query);
    static double dynamic_execute(const InputQuery& query);
};