#include <algorithm>
#include <array>
#include <ranges>
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
    return std::ranges::find(board_state, elem) == board_state.end();
  });

  /* for ( const char elem : legal_chars ) { */
  /*   if ( std::ranges::find(board_state, elem) == board_state.end() ) { */
  /*     return false; */
  /*   } */
  /* } */
  /* return true; */
}

Board_4x4::Board_4x4(const std::array<char, 16>& board_state)
    : m_board_state {board_state}
{
  if ( ! is_legal_board(board_state) ) {
    throw std::invalid_argument {"Illegal board state"};
  }
}
