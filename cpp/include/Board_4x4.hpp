#ifndef BOARD_HPP
#define BOARD_HPP

#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <vector>

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

  const Board_4x4* m_parent {nullptr};

  bool m_can_move_up : 1 {true};
  bool m_can_move_down : 1 {false};
  bool m_can_move_left : 1 {true};
  bool m_can_move_right : 1 {false};

  void p_determine_legal_moves() noexcept;
  auto p_swap(std::size_t idx1, std::size_t idx2) noexcept -> Board_4x4&;

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

  [[nodiscard]] auto generate_possible_moves() const noexcept
    -> std::vector<Board_4x4>;

  // may return null
  [[nodiscard]] auto parent() const -> const Board_4x4*
  {
    return m_parent;
  }

  friend inline auto operator<<(std::ostream& out,
                                const Board_4x4& rhs) noexcept
    -> std::ostream&
  {
    const std::array<std::pair<char, std::string_view>, 16> print_mapping {
      std::make_pair<char, std::string_view>('1', "  1 "),
      std::make_pair<char, std::string_view>('2', "  2 "),
      std::make_pair<char, std::string_view>('3', "  3 "),
      std::make_pair<char, std::string_view>('4', "  4 "),
      std::make_pair<char, std::string_view>('5', "  5 "),
      std::make_pair<char, std::string_view>('6', "  6 "),
      std::make_pair<char, std::string_view>('7', "  7 "),
      std::make_pair<char, std::string_view>('8', "  8 "),
      std::make_pair<char, std::string_view>('9', "  9 "),
      std::make_pair<char, std::string_view>('A', " 10 "),
      std::make_pair<char, std::string_view>('B', " 11 "),
      std::make_pair<char, std::string_view>('C', " 12 "),
      std::make_pair<char, std::string_view>('D', " 13 "),
      std::make_pair<char, std::string_view>('E', " 14 "),
      std::make_pair<char, std::string_view>('F', " 15 "),
      std::make_pair<char, std::string_view>('_', "    ")};

    std::string output_buffer {
      R"(
XXXX|XXXX|XXXX|XXXX
-------------------
XXXX|XXXX|XXXX|XXXX
-------------------
XXXX|XXXX|XXXX|XXXX
-------------------
XXXX|XXXX|XXXX|XXXX
)"};

    for ( const char elem : rhs.m_board_state ) {
      output_buffer.replace(output_buffer.find("XXXX"),
                            4,
                            (*std::ranges::find_if(print_mapping,
                                                   [&](const auto& kv) {
                                                     return kv.first
                                                         == elem;
                                                   }))
                              .second);
    }

    out << output_buffer;

    return out;
  }
};

#endif
