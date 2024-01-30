#include <supl/test_runner.hpp>
#include <supl/test_section.hpp>

auto test_illegal_argument() -> supl::test_results
{
  supl::test_results results;

  return results;
}

auto test_constructor() -> supl::test_section
{
  supl::test_section section;

  section.add_test("Board_4x4 Illegal Constructor Arg",
                   &test_illegal_argument);

  return section;
}

auto main() -> int
{
  supl::test_runner runner;

  runner.add_section(test_constructor());

  return runner.run();
}
