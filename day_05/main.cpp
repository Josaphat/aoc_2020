#include <array>
#include <cassert>
#include <iostream>
#include <string>

void
other();
int
main(int argc, char* argv[])
{
  if (argc > 1) {
    other();
    return 0;
  }

  std::array<bool, 8* 128> seats;
  seats.fill(false);

  int max_id = -1;

  while (std::cin) {
    std::string code;
    std::cin >> code;

    if (code.empty()) {
      continue;
    }

    int row = -1;
    int col = -1;

    int upper = 127;
    int lower = 0;

    for (int i = 0; i < 7; ++i) {
      auto& c = code[i];
      if (c == 'F') {
        upper -= (upper - lower) / 2 + 1;
      } else if (c == 'B') {
        lower += (upper - lower) / 2 + 1;
      }
    }

    if (upper != lower) {
      std::cout << "OOPS! Row values are not the same!\n";
    }

    row = lower;

    upper = 7;
    lower = 0;

    for (int i = 7; i < 10; ++i) {
      auto& c = code[i];
      if (c == 'L') {
        upper -= (upper - lower) / 2 + 1;
      } else if (c == 'R') {
        lower += (upper - lower) / 2 + 1;
      }
    }
    if (upper != lower) {
      std::cout << "OOPS! Col values are not the same!\n";
    }

    col = lower;

    auto seat_id = row * 8 + col;
    std::cout << code << ": row " << row << ", column " << col << ", seat ID "
              << seat_id << ".\n";
    seats[seat_id] = true; // this seat is taken.

    if (seat_id > max_id) {
      max_id = seat_id;
    }
  }

  std::cout << "Max Seat ID: " << max_id << "\n";

  auto row_size = 0;
  for (auto i = 0; i < seats.size(); ++i) {
    if (!seats[i]) { // seat is not taken
      std::cout << i << " ";
      if (row_size++ % 8 == 0) {
        std::cout << "\n";
      }
    }
  }

  return 0;
}

void
other()
{}
