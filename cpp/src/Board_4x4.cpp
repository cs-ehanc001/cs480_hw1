#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <supl/utility.hpp>

#include "Board_4x4.hpp"

[[nodiscard]] auto static is_legal_board(
  const std::array<char, 16>& board_state) noexcept -> bool
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

[[nodiscard]] static auto
space_index(const std::array<char, 16>& board_state) noexcept
  -> std::size_t
{
  const std::size_t retval {static_cast<std::size_t>(std::distance(
    std::begin(board_state), std::ranges::find(board_state, '_')))};

  assert(retval < 16);

  return retval;
}

void Board_4x4::p_determine_legal_moves() noexcept
{
  const std::size_t space_idx {space_index(m_board_state)};
  assert(space_idx < 16);
  assert(m_board_state.at(space_idx) == '_');

  const std::size_t column {space_idx % 4};
  const std::size_t row {space_idx / 4};

  m_can_move_up = row != 0;

  m_can_move_down = row != 3;

  m_can_move_left = column != 0;

  m_can_move_right = column != 3;
}

Board_4x4::Board_4x4(const std::array<char, 16>& board_state)
    : m_board_state {board_state}
{
  if ( ! is_legal_board(board_state) ) {
    throw std::invalid_argument {"Illegal board state"};
  }

  p_determine_legal_moves();
}

auto Board_4x4::p_swap(std::size_t idx1, std::size_t idx2) noexcept
  -> Board_4x4&
{
  assert(idx1 != idx2);
  assert(idx1 < 16);
  assert(idx2 < 16);

  std::swap(m_board_state.at(idx1), m_board_state.at(idx2));
  this->p_determine_legal_moves();
  return *this;
}

auto Board_4x4::generate_possible_moves() const noexcept
  -> std::vector<Board_4x4>
{

  /* std::cout << "Calling space_index from generate_possible_moves with: " */
  /*           << supl::stream_adapter {m_board_state} << '\n'; */

  assert(is_legal_board(m_board_state));

  const std::size_t space_idx {space_index(m_board_state)};
  assert(m_board_state.at(space_idx) == '_');

  std::vector<Board_4x4> possible_moves {};

  if ( m_can_move_up ) {
    possible_moves.push_back(
      supl::explicit_copy(*this).p_swap(space_idx, space_idx - 4));
  }

  if ( m_can_move_down ) {
    possible_moves.push_back(
      supl::explicit_copy(*this).p_swap(space_idx, space_idx + 4));
  }

  if ( m_can_move_left ) {
    possible_moves.push_back(
      supl::explicit_copy(*this).p_swap(space_idx, space_idx - 1));
  }

  if ( m_can_move_right ) {
    possible_moves.push_back(
      supl::explicit_copy(*this).p_swap(space_idx, space_idx + 1));
  }

  for ( Board_4x4& board : possible_moves ) {
    board.m_parent = this;
  }

  if ( m_parent != nullptr ) {
    // move that would undo (doing could lead to infinite loop)
    const Board_4x4& undoing_move {*m_parent};
    const auto undoing_itr {
      std::ranges::find(possible_moves, undoing_move)};

    assert(undoing_itr != possible_moves.end());

    possible_moves.erase(undoing_itr);
  }

  return possible_moves;
}
