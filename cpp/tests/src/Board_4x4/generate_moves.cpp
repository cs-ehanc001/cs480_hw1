#include <algorithm>
#include <array>

#include <supl/utility.hpp>

#include <supl/test_runner.hpp>
#include <supl/test_section.hpp>

#include "Board_4x4.hpp"

static auto generate_moves_from_top_left() -> supl::test_results
{
  supl::test_results results;

  const Board_4x4 start {
  // clang-format off
    std::array{
        '_', '2', '3', '4',
        '5', '6', '7', '8',
        '9', 'A', 'B', 'C',
        'D', 'E', 'F', '1'
    }
  // clang-format on
  };

  auto possible_moves {start.generate_possible_moves()};

  results.enforce_equal(
    possible_moves.size(), 2, "Should be 2 legal moves");

  const Board_4x4 move_right {
  // clang-format off
    std::array{
        '2', '_', '3', '4',
        '5', '6', '7', '8',
        '9', 'A', 'B', 'C',
        'D', 'E', 'F', '1'
    }
  // clang-format on
  };

  const Board_4x4 move_down {
  // clang-format off
    std::array{
        '5', '2', '3', '4',
        '_', '6', '7', '8',
        '9', 'A', 'B', 'C',
        'D', 'E', 'F', '1'
    }
  // clang-format on
  };

  results.enforce_false(std::ranges::find(possible_moves, move_right)
                          == possible_moves.end(),
                        "Incorrect right move");
  results.enforce_false(std::ranges::find(possible_moves, move_down)
                          == possible_moves.end(),
                        "Incorrect down move");

  if ( ! results.test_passes() ) {
    std::cout << start << '\n';
    std::cout << supl::stream_adapter {possible_moves} << '\n';
  }

  return results;
}

auto test_move_validity() -> supl::test_section
{
  supl::test_section section;

  section.add_test("Move Validity", &generate_moves_from_top_left);

  return section;
}

auto main() -> int
{
  supl::test_runner runner;

  runner.add_section(test_move_validity());

  return runner.run();
}
