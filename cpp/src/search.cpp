#include <cassert>
#include <iterator>
#include <list>
#include <numeric>
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
  -> std::pair<std::vector<Board_4x4>, std::size_t>
{
  // default-constructed Board_4x4 is goal state
  const Board_4x4 goal {};

  // history to preserve lifetimes of all nodes for backtrace
  std::list<Board_4x4> history {start};

  // FIFO frontier
  std::queue<const Board_4x4*> frontier {};
  frontier.push(&history.front());

  // will return out of the loop
  while ( history.size() < (history.max_size() / 2) ) {

    assert(! frontier.empty());

    // generate new moves
    const auto new_moves {frontier.front()->generate_possible_moves()};

    // remove expanded node
    frontier.pop();

    // save them to history
    std::ranges::copy(new_moves, std::back_inserter(history));

    for ( const Board_4x4& board : new_moves ) {

      // goal check each newly-generated node
      if ( board == goal ) {
        return {backtrace(board), history.size()};
      }
    }

    // iterator to first new node in history
    const auto first_new {
      std::prev(history.end(),
                static_cast<std::iterator_traits<
                  std::decay_t<decltype(history.end())>>::difference_type>(
                  new_moves.size()))};

    // add new nodes to frontier, cautious of object lifetimes
    for ( const Board_4x4& board :
          supl::range_wrapper {first_new, history.end()} ) {
      frontier.push(&board);
    }
  }

  assert(false);
}

[[nodiscard]] auto dfs_search(const Board_4x4& start)
  -> std::pair<std::vector<Board_4x4>, std::size_t>
{
  // default-constructed Board_4x4 is goal state
  const Board_4x4 goal {};
  constexpr std::size_t max_depth {10};

  struct Node {
    Board_4x4* board_ptr;
    std::size_t depth;
  };

  // history to preserve lifetimes of all nodes for backtrace
  std::list<Board_4x4> history {start};

  // LIFO frontier
  std::stack<Node> frontier {std::deque {Node {&history.front(), 0}}};

  while ( history.size() < (history.max_size() / 2) ) {

    assert(! frontier.empty());

    // goal check before expansion
    if ( *frontier.top().board_ptr == goal ) {
      return {backtrace(*frontier.top().board_ptr), history.size()};
    }

    // get new moves and depth of node currently being expanded
    const auto [new_moves, current_depth] {[&]() {
      const auto& [board_ptr, depth] {frontier.top()};
      return std::pair {board_ptr->generate_possible_moves(), depth};
    }()};
    frontier.pop();

    // do not search deeper than max_depth
    if ( current_depth == max_depth ) {
      continue;
    }

    std::ranges::copy(new_moves, std::back_inserter(history));

    // iterator to first new node in history
    const auto first_new {
      std::prev(history.end(),
                static_cast<std::iterator_traits<
                  std::decay_t<decltype(history.end())>>::difference_type>(
                  new_moves.size()))};

    // add new nodes to frontier, cautious of object lifetimes
    for ( Board_4x4& board :
          supl::range_wrapper {first_new, history.end()} ) {
      frontier.emplace(&board, current_depth + 1);
    }
  }

  return {{}, history.size()};
}

// h1 heuristic
auto misplaced_squares(const Board_4x4& arg) noexcept -> int
{
  constexpr static Board_4x4 goal {};

  return std::transform_reduce(arg.data().begin(),
                               arg.data().end(),
                               goal.data().begin(),
                               0,
                               std::plus {},
                               [](char a, char b) -> int {
                                 return static_cast<int>(a != b);
                               });
}

[[nodiscard]] auto ucs_search(const Board_4x4& start)
  -> std::pair<std::vector<Board_4x4>, std::size_t>
{
  // default-constructed Board_4x4 is goal state
  const Board_4x4 goal {};

  // history to preserve lifetimes of all nodes for backtrace
  std::list<Board_4x4> history {start};

  // frontier sorted such that nodes with the lowest h1 metric
  // are at the front
  std::priority_queue frontier {
    [](const Board_4x4* lhs, const Board_4x4* rhs) -> bool {
      return misplaced_squares(*lhs) > misplaced_squares(*rhs);
    },
    std::deque<const Board_4x4*> {&history.front()}};

  // will return out of the loop
  while ( history.size() < (history.max_size() / 2) ) {

    assert(! frontier.empty());

    // generate new moves
    const auto new_moves {frontier.top()->generate_possible_moves()};

    // remove expanded node
    frontier.pop();

    // save them to history
    std::ranges::copy(new_moves, std::back_inserter(history));

    for ( const Board_4x4& board : new_moves ) {

      // goal check each newly-generated node
      if ( board == goal ) {
        return {backtrace(board), history.size()};
      }
    }

    // iterator to first new node in history
    const auto first_new {
      std::prev(history.end(),
                static_cast<std::iterator_traits<
                  std::decay_t<decltype(history.end())>>::difference_type>(
                  new_moves.size()))};

    // add new nodes to frontier, cautious of object lifetimes
    for ( const Board_4x4& board :
          supl::range_wrapper {first_new, history.end()} ) {
      frontier.push(&board);
    }
  }

  assert(false);
}
