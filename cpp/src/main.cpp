#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "Board_4x4.hpp"
#include "search.hpp"

void print_help_message(const char* const* const argv)
{
  std::cerr << "Usage:\n";
  std::cerr << argv[0] << " [search-type] [input-file]\n\n";

  std::cerr << "[search-type] must be one of: --bfs --dfs --ucs\n";
  std::cerr << "See README.md for input file specification\n";
}

auto main(const int argc, const char* const* const argv) -> int
{
  using search_fn_t = decltype(&bfs_search);

  search_fn_t search_function {nullptr};

  const std::map<std::string_view, search_fn_t> search_fn_table {
    {"--bfs", &bfs_search},
    {"--dfs", &dfs_search},
    {"--ucs", &ucs_search},
  };

  if ( argc != 3 ) {
    print_help_message(argv);
    return 1;
  }

  try {
    search_function = search_fn_table.at(argv[1]);
  } catch ( const std::out_of_range& ) {
    std::cerr << "Invalid search type: " << argv[1] << '\n';
    print_help_message(argv);
    return 1;
  }

  assert((search_function == &bfs_search)
         || (search_function == &dfs_search)
         || (search_function == &ucs_search));

  std::ifstream infile(argv[2], std::ios::in);

  if ( ! infile.is_open() ) {
    std::cerr << "File " << argv[2] << " could not be opened!" << '\n';
    print_help_message(argv);
    return 1;
  }

  Board_4x4 start {};

  infile >> start;

  const auto [solution, generated_node_count] {search_function(start)};

  if ( solution.empty() ) {
    std::cerr << "No solution could be found\n";
    std::cerr << generated_node_count << " nodes generated, using "
              << (sizeof(Board_4x4)) << " bytes of memory\n";
    return 1;
  }

  for ( const auto reverse_view {std::views::reverse(solution)};
        const auto& state : reverse_view ) {
    std::cout << state << '\n';
  }

  std::cout << generated_node_count << " nodes generated, using "
            << (sizeof(Board_4x4) * generated_node_count)
            << " bytes of memory\n\n";
  std::cout << "Solution: " << '\n';

  std::cout << "Solution took " << solution.size() << " steps\n";
}
