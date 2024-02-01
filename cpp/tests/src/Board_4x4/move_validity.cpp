#include <array>

#include <supl/utility.hpp>

#include <supl/test_runner.hpp>
#include <supl/test_section.hpp>

#include "Board_4x4.hpp"

static auto test_valid_moves() -> supl::test_results
{
  supl::test_results results;

  const Board_4x4 pos_0
    // clang-format off
    {
      std::array{
          '_', '2', '3', '4',
          '5', '6', '7', '8',
          '9', 'A', 'B', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_0.can_move(Direction::Up),
                                   pos_0.can_move(Direction::Down),
                                   pos_0.can_move(Direction::Left),
                                   pos_0.can_move(Direction::Right)),
                        supl::ctie(false, true, false, true),
                        "Position 0");

  const Board_4x4 pos_1
    // clang-format off
    {
      std::array{
          '2', '_', '3', '4',
          '5', '6', '7', '8',
          '9', 'A', 'B', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_1.can_move(Direction::Up),
                                   pos_1.can_move(Direction::Down),
                                   pos_1.can_move(Direction::Left),
                                   pos_1.can_move(Direction::Right)),
                        supl::ctie(false, true, true, true),
                        "Position 1");

  const Board_4x4 pos_2
    // clang-format off
    {
      std::array{
          '2', '3', '_', '4',
          '5', '6', '7', '8',
          '9', 'A', 'B', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_2.can_move(Direction::Up),
                                   pos_2.can_move(Direction::Down),
                                   pos_2.can_move(Direction::Left),
                                   pos_2.can_move(Direction::Right)),
                        supl::ctie(false, true, true, true),
                        "Position 2");

  const Board_4x4 pos_3
    // clang-format off
    {
      std::array{
          '2', '3', '4', '_',
          '5', '6', '7', '8',
          '9', 'A', 'B', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_3.can_move(Direction::Up),
                                   pos_3.can_move(Direction::Down),
                                   pos_3.can_move(Direction::Left),
                                   pos_3.can_move(Direction::Right)),
                        supl::ctie(false, true, true, false),
                        "Position 3");

  const Board_4x4 pos_4
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '_', '6', '7', '8',
          '9', 'A', 'B', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_4.can_move(Direction::Up),
                                   pos_4.can_move(Direction::Down),
                                   pos_4.can_move(Direction::Left),
                                   pos_4.can_move(Direction::Right)),
                        supl::ctie(true, true, false, true),
                        "Position 4");

  const Board_4x4 pos_5
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '_', '7', '8',
          '9', 'A', 'B', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_5.can_move(Direction::Up),
                                   pos_5.can_move(Direction::Down),
                                   pos_5.can_move(Direction::Left),
                                   pos_5.can_move(Direction::Right)),
                        supl::ctie(true, true, true, true),
                        "Position 5");

  const Board_4x4 pos_6
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '7', '_', '8',
          '9', 'A', 'B', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_6.can_move(Direction::Up),
                                   pos_6.can_move(Direction::Down),
                                   pos_6.can_move(Direction::Left),
                                   pos_6.can_move(Direction::Right)),
                        supl::ctie(true, true, true, true),
                        "Position 6");

  const Board_4x4 pos_7
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '7', '8', '_',
          '9', 'A', 'B', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_7.can_move(Direction::Up),
                                   pos_7.can_move(Direction::Down),
                                   pos_7.can_move(Direction::Left),
                                   pos_7.can_move(Direction::Right)),
                        supl::ctie(true, true, true, false),
                        "Position 7");

  const Board_4x4 pos_8
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '7', '8', '9',
          '_', 'A', 'B', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_8.can_move(Direction::Up),
                                   pos_8.can_move(Direction::Down),
                                   pos_8.can_move(Direction::Left),
                                   pos_8.can_move(Direction::Right)),
                        supl::ctie(true, true, false, true),
                        "Position 8");

  const Board_4x4 pos_9
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '7', '8', '9',
          'A', '_', 'B', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_9.can_move(Direction::Up),
                                   pos_9.can_move(Direction::Down),
                                   pos_9.can_move(Direction::Left),
                                   pos_9.can_move(Direction::Right)),
                        supl::ctie(true, true, true, true),
                        "Position 9");

  const Board_4x4 pos_10
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '7', '8', '9',
          'A', 'B', '_', 'C',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_10.can_move(Direction::Up),
                                   pos_10.can_move(Direction::Down),
                                   pos_10.can_move(Direction::Left),
                                   pos_10.can_move(Direction::Right)),
                        supl::ctie(true, true, true, true),
                        "Position 10");

  const Board_4x4 pos_11
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '7', '8', '9',
          'A', 'B', 'C', '_',
          'D', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_11.can_move(Direction::Up),
                                   pos_11.can_move(Direction::Down),
                                   pos_11.can_move(Direction::Left),
                                   pos_11.can_move(Direction::Right)),
                        supl::ctie(true, true, true, false),
                        "Position 11");

  const Board_4x4 pos_12
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '7', '8', '9',
          'A', 'B', 'C', 'D',
          '_', 'E', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_12.can_move(Direction::Up),
                                   pos_12.can_move(Direction::Down),
                                   pos_12.can_move(Direction::Left),
                                   pos_12.can_move(Direction::Right)),
                        supl::ctie(true, false, false, true),
                        "Position 12");

  const Board_4x4 pos_13
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '7', '8', '9',
          'A', 'B', 'C', 'D',
          'E', '_', 'F', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_13.can_move(Direction::Up),
                                   pos_13.can_move(Direction::Down),
                                   pos_13.can_move(Direction::Left),
                                   pos_13.can_move(Direction::Right)),
                        supl::ctie(true, false, true, true),
                        "Position 13");

  const Board_4x4 pos_14
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '7', '8', '9',
          'A', 'B', 'C', 'D',
          'E', 'F', '_', '1'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_14.can_move(Direction::Up),
                                   pos_14.can_move(Direction::Down),
                                   pos_14.can_move(Direction::Left),
                                   pos_14.can_move(Direction::Right)),
                        supl::ctie(true, false, true, true),
                        "Position 14");

  const Board_4x4 pos_15
    // clang-format off
    {
      std::array{
          '2', '3', '4', '5',
          '6', '7', '8', '9',
          'A', 'B', 'C', 'D',
          'E', 'F', '1', '_'
      }
    };
  // clang-format on

  results.enforce_equal(supl::ctie(pos_15.can_move(Direction::Up),
                                   pos_15.can_move(Direction::Down),
                                   pos_15.can_move(Direction::Left),
                                   pos_15.can_move(Direction::Right)),
                        supl::ctie(true, false, true, false),
                        "Position 15");

  return results;
}

auto test_move_validity() -> supl::test_section
{
  supl::test_section section;

  section.add_test("Move Validity", &test_valid_moves);

  return section;
}

auto main() -> int
{
  supl::test_runner runner;

  runner.add_section(test_move_validity());

  return runner.run();
}
