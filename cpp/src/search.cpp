#include <cassert>
#include <iterator>
#include <queue>
#include <stack>
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
  std::queue<const Board_4x4*> frontier {std::deque {&start}};

  // all nodes (for backtrace of path)
  std::vector<Board_4x4> history {};

  // default-constructed Board_4x4 is goal state
  constexpr Board_4x4 goal {};

  // break when goal found
  while ( true ) {
    // expand front of frontier
    std::vector<Board_4x4> new_moves {
      frontier.front()->generate_possible_moves()};

    // remove previous state to avoid infinite loop
    const auto previous_move {
      std::ranges::find(new_moves, *frontier.front())};
    assert(previous_move != new_moves.end());
    new_moves.erase(previous_move);

    // remove expanded node from frontier
    frontier.pop();

    // save new nodes for backtrace later
    std::ranges::copy(new_moves, std::back_inserter(history));

    // add newly-generated nodes to frontier
    for ( const auto& board : new_moves ) {

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
