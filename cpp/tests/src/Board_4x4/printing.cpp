#include <array>
#include <iostream>

#include <supl/utility.hpp>

#include "Board_4x4.hpp"

auto main() -> int
{
  Board_4x4 test {
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

  std::cout << "Here is the output: \n" << test << '\n';

  return 0;
}
