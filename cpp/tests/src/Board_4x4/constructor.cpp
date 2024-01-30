#include <array>

#include <stdexcept>
#include <supl/test_runner.hpp>
#include <supl/test_section.hpp>

#include "Board_4x4.hpp"

static auto test_valid_argument() -> supl::test_results
{
  supl::test_results results;

  try {
    Board_4x4 test1 {
      std::array {'1',
                  '2', '3',
                  '4', '5',
                  '6', '7',
                  '8', '9',
                  'A', 'B',
                  'C', 'D',
                  'E', 'F',
                  '_'}
    };
  } catch ( const std::invalid_argument& ) {
    results.fail("test1 should not have thrown");
  }

  return results;
}

static auto test_invalid_argument() -> supl::test_results
{
  supl::test_results results;

  try {
    Board_4x4 test1 {
      std::array {'1',
                  '2', '3',
                  '6', '7',
                  '4', '4',
                  '8', '9',
                  'C', 'D',
                  'A', 'B',
                  'E', 'F',
                  '_'}
    };
    results.fail("test1 should have thrown");
  } catch ( const std::invalid_argument& e ) {
    results.enforce_equal(e.what(), std::string {"Illegal board state"});
  }

  try {
    Board_4x4 test2 {
      std::array {'1',
                  '2', '3',
                  '6', '7',
                  '4', 'H',
                  '8', '9',
                  'C', 'D',
                  'A', 'B',
                  'E', 'F',
                  '_'}
    };
    results.fail("test2 should have thrown");
  } catch ( const std::invalid_argument& e ) {
    results.enforce_equal(e.what(), std::string {"Illegal board state"});
  }

  return results;
}

auto test_constructor() -> supl::test_section
{
  supl::test_section section;

  section.add_test("Board_4x4 Valid Constructor Arg",
                   &test_valid_argument);
  section.add_test("Board_4x4 Invalid Constructor Arg",
                   &test_invalid_argument);

  return section;
}

auto main() -> int
{
  supl::test_runner runner;

  runner.add_section(test_constructor());

  return runner.run();
}
