#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>

#include "Board_4x4.hpp"

[[nodiscard]] auto
is_legal_board(const std::array<char, 16>& board_state) noexcept -> bool
{
  constexpr static std::array<char, 16> legal_chars {'1',
                                                     '2',
                                                     '3',
                                                     '4',
                                                     '5',
                                                     '6',
                                                     '7',
                                                     '8',
                                                     '9',
                                                     'A',
                                                     'B',
                                                     'C',
                                                     'D',
                                                     'E',
                                                     'F',
                                                     '_'};

  // each legal_char must appear in board_state
  // consequently, if all appear, then each appears exactly once
  return std::ranges::all_of(legal_chars, [&](const char elem) {
    // True if char is found
    return std::ranges::find(board_state, elem) != board_state.end();
  });
}

Board_4x4::Board_4x4(const std::array<char, 16>& board_state)
    : m_board_state {board_state}
    , m_can_move_up {true}  // NOLINT(*default-member-init*)
    , m_can_move_down {true}
    , m_can_move_left {true}  // NOLINT(*default-member-init*)
    , m_can_move_right {true}
{
  if ( ! is_legal_board(board_state) ) {
    throw std::invalid_argument {"Illegal board state"};
  }

  const std::size_t space_idx = static_cast<std::size_t>(std::distance(
    std::begin(m_board_state), std::ranges::find(m_board_state, '_')));

  assert(m_board_state.at(space_idx) == '_');

  const std::size_t column {space_idx % 4};
  const std::size_t row {space_idx / 4};

  if ( row == 0 ) {
    m_can_move_up = false;
  }

  if ( row == 3 ) {
    m_can_move_down = false;
  }

  if ( column == 0 ) {
    m_can_move_left = false;
  }

  if ( column == 3 ) {
    m_can_move_right = false;
  }
}
