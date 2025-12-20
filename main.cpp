

#include <omp.h>

#include "hit.h"
#include "my_exception.hpp"
#include "parser.hpp"
#include "realizations.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    try {
        std::vector<std::string> tmp_vec;
        tmp_vec.reserve(static_cast<std::uint64_t>(argc - 1));
        auto size = static_cast<std::uint64_t>(argc - 1);
        for (std::uint64_t i = 0; i < size; ++i) {
            tmp_vec.emplace_back(argv[i + 1]);
        }
        InputQuery query = Parser::parse(tmp_vec);
        double ans;
        volatile double start_time = omp_get_wtime();
        switch (query.get_realization()) {
            case 1:
                ans = Realization1::execute(query);
                break;
            case 2:
                ans = Realization2::execute(query);
                break;
            case 3:
                ans = Realization3::execute(query);
                break;
            default:
                throw MyException(EXIT_FAILURE, "unknown realization");
        }
        volatile double end_time = omp_get_wtime();

        printf("Time (%i thread(s)): %g ms\n",
               static_cast<int>(query.get_threads()),
               (end_time - start_time) * 1000.0);
        std::ofstream output_file(query.get_output_file());
        if (!output_file.is_open()) {
            throw MyException(EXIT_FAILURE, "cannot open output file");
        }
        output_file << ans << "\n";
        output_file.close();
        return EXIT_SUCCESS;
    }
    catch (const MyException& e) {
        std::cerr << e.get_error();
        return static_cast<std::int32_t>(e.get_code());
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "unknown error";
        return EXIT_FAILURE;
    }
}
