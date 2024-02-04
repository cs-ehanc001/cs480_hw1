#include <cassert>
#include <iterator>
#include <limits>
#include <list>
#include <queue>
#include <stack>
#include <type_traits>
#include <vector>

#include <supl/utility.hpp>

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
  // default-constructed Board_4x4 is goal state
  const Board_4x4 goal {};

  // history to preserve lifetimes of all nodes for backtrace
  std::list<Board_4x4> history {start};

  std::queue<Board_4x4*> frontier {};
  frontier.push(&history.front());

  // will return out of the loop
  while ( history.size() < (history.max_size() / 2) ) {

    assert(! frontier.empty());

    // generate new moves
    auto new_moves {frontier.front()->generate_possible_moves()};

    // remove expanded node
    frontier.pop();

    // save them to history
    std::ranges::copy(new_moves, std::back_inserter(history));

    auto first_new {
      std::prev(history.end(),
                static_cast<std::iterator_traits<
                  std::decay_t<decltype(history.end())>>::difference_type>(
                  new_moves.size()))};

    for ( Board_4x4& board : new_moves ) {

      if ( board == goal ) {
        return backtrace(board);
      }
    }

    for ( Board_4x4& board :
          supl::range_wrapper {first_new, history.end()} ) {
      frontier.push(&board);
    }
  }

  assert(false);
}

// need depth-limiting!!
/* [[nodiscard]] auto dfs_search(const Board_4x4& start) */
/*   -> std::vector<Board_4x4> */
/* { */
/* } */

/* [[nodiscard]] auto ucs_search(const Board_4x4& start) */
/*   -> std::vector<Board_4x4> */
/* { */
/* } */
