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
      '2', '5', '3', '1',
      '4', '6', '8', '7',
      'A', 'D', '_', 'C',
      'B', 'E', 'F', '9'
    }
  };
  // clang-format on

  const auto solution {bfs_search(test)};

  for ( const auto reverse_view {std::views::reverse(solution)};
        const auto& state : reverse_view ) {
    std::cout << state << '\n';
  }
}
