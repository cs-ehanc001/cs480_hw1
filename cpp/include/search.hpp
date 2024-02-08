#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <vector>

#include "Board_4x4.hpp"

[[nodiscard]] auto bfs_search(const Board_4x4& start)
  -> std::pair<std::vector<Board_4x4>, std::size_t>;
[[nodiscard]] auto dfs_search(const Board_4x4& start)
  -> std::pair<std::vector<Board_4x4>, std::size_t>;
[[nodiscard]] auto ucs_search(const Board_4x4& start)
  -> std::pair<std::vector<Board_4x4>, std::size_t>;

#endif
