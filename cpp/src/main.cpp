#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

#include "Board_4x4.hpp"
#include "search.hpp"

auto main() -> int
{
  // clang-format off
  Board_4x4 test {
    std::array {
      '1', '_', '2', '4',
      '5', '7', '3', '8',
      '9', '6', 'B', 'C',
      'D', 'A', 'E', 'F'
    }
    /* std::array { */
    /*   '1', '2', '3', '4', */
    /*   '5', '6', '7', '8', */
    /*   '9', 'A', 'B', 'C', */
    /*   '_', 'D', 'E', 'F' */
    /* } */
  };
  // clang-format on

  const auto solution {bfs_search(test)};

  std::cout << "Solution: " << '\n';

  for ( const auto reverse_view {std::views::reverse(solution)};
        const auto& state : reverse_view ) {
    std::cout << state << '\n';
  }
}
