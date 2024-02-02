#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <iostream>
#include <map>
#include <string_view>

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

  [[nodiscard]] friend auto operator<=>(const Board_4x4&,
                                        const Board_4x4&) = default;

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

  friend inline auto operator<<(std::ostream& out,
                                const Board_4x4& rhs) noexcept
    -> std::ostream&
  {
    const static std::map<char, std::string_view> print_mapping {
      {'1', "  1 "},
      {'2', "  2 "},
      {'3', "  3 "},
      {'4', "  4 "},
      {'5', "  5 "},
      {'6', "  6 "},
      {'7', "  7 "},
      {'8', "  8 "},
      {'9', "  9 "},
      {'A', " 10 "},
      {'B', " 11 "},
      {'C', " 12 "},
      {'D', " 13 "},
      {'E', " 14 "},
      {'F', " 15 "},
      {'_', "    "}
    };

    std::string output_buffer {
      R"(XXXX|XXXX|XXXX|XXXX
-------------------
XXXX|XXXX|XXXX|XXXX
-------------------
XXXX|XXXX|XXXX|XXXX
-------------------
XXXX|XXXX|XXXX|XXXX
)"};

    for ( const char elem : rhs.m_board_state ) {
      output_buffer.replace(
        output_buffer.find("XXXX"), 4, print_mapping.at(elem));
    }

    out << output_buffer;

    return out;
  }
};

#endif
