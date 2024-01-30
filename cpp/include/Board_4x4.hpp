#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>

enum class Direction : char {
  Up,
  Down,
  Left,
  Right
};

class Board_4x4
{
private:

  std::array<char, 16> m_board_state
    // clang-format off
    {
      '1', '2', '3', '4',
      '5', '6', '7', '8',
      '9', 'A', 'B', 'C',
      'D', 'E', 'F', '_'
    };
  // clang-format on
  bool m_can_move_up : 1 {true};
  bool m_can_move_down : 1 {false};
  bool m_can_move_left : 1 {true};
  bool m_can_move_right : 1 {false};

public:

  Board_4x4() = default;
  Board_4x4(const Board_4x4&) noexcept = default;
  Board_4x4(Board_4x4&&) noexcept = default;
  auto operator=(const Board_4x4&) noexcept -> Board_4x4& = default;
  auto operator=(Board_4x4&&) noexcept -> Board_4x4& = default;
  ~Board_4x4() = default;

  explicit Board_4x4(const std::array<char, 16>& board_state);

  [[nodiscard]] auto can_move(Direction dir) const noexcept -> bool
  {
    switch ( dir ) {
      using enum Direction;

      case Up:
        return m_can_move_up;
      case Down:
        return m_can_move_down;
      case Left:
        return m_can_move_left;
      case Right:
        return m_can_move_right;
    }
  }
};

#endif
