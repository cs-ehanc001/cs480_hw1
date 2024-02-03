#include <cassert>
#include <iterator>
#include <list>
#include <queue>
#include <stack>
#include <supl/utility.hpp>
#include <vector>

#include "Board_4x4.hpp"
#include "search.hpp"

auto backtrace(const Board_4x4& goal) -> std::vector<Board_4x4>
{
  std::vector<Board_4x4> retval {goal};
  while ( retval.back().parent() != nullptr ) {
    retval.push_back(*retval.back().parent());
  }

  return retval;
}

[[nodiscard]] auto bfs_search(const Board_4x4& start)
  -> std::vector<Board_4x4>
{
  // all nodes (for backtrace of path)
  std::list<Board_4x4> history {start};

  std::queue<Board_4x4*> frontier {std::deque {&history.front()}};

  // default-constructed Board_4x4 is goal state
  const Board_4x4 goal {};

  // break when goal found
  while ( true ) {
    // expand front of frontier
    std::vector<Board_4x4> new_moves {
      frontier.front()->generate_possible_moves()};

    std::cout << "Expanding:" << *frontier.front() << '\n';
    std::cout << "Resulting moves: " << supl::stream_adapter {new_moves}
              << "\n\n\n";

    // remove expanded node from frontier
    frontier.pop();

    // save new nodes for backtrace later
    std::ranges::copy(new_moves, std::back_inserter(history));

    // add newly-generated nodes to frontier
    for ( auto& board : new_moves ) {

      if ( board == goal ) {
        return backtrace(board);
      }

      frontier.push(&board);
    }
  }
}

/* [[nodiscard]] auto dfs_search(const Board_4x4& start) */
/*   -> std::vector<Board_4x4> */
/* { */
/* } */

/* [[nodiscard]] auto ucs_search(const Board_4x4& start) */
/*   -> std::vector<Board_4x4> */
/* { */
/* } */
