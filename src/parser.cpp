#include "parser.hpp"

#include <fstream>

InputQuery Parser::parse(std::vector<std::string> args) {
    InputQuery query;

    for (std::size_t i = 0; i < args.size(); ++i) {
        if (args[i] == "--input") {
            std::ifstream infile(args[++i]);
            std::uint64_t inp_n;
            infile >> inp_n;
            query.set_n(inp_n);
            infile.close();
        }
        if (args[i] == "--output") {
            query.set_output_file(args[++i]);
        }
        if (args[i] == "--realization") {
            query.set_realization(
                static_cast<std::uint64_t>(std::stoull(args[++i], nullptr, 0)));
        }
        if (args[i] == "--threads") {
            query.set_threads(
                static_cast<std::uint64_t>(std::stoull(args[++i], nullptr, 0)));
        }
        if (args[i] == "--kind") {
            if (args[++i] == "static") {
                query.set_kind(Kind::Static);
            }
            else if (args[i] == "dynamic") {
                query.set_kind(Kind::Dynamic);
            }
        }
        if (args[i] == "--chunk_size") {
            query.set_chunk_size(
                static_cast<std::uint64_t>(std::stoull(args[++i], nullptr, 0)));
        }
    }

    return query;
}