#include <iostream>
#include <map>
#include <string>
#include <vector>

void other();

int main(int argc, char* argv[]) {
  if (argc == 2) {
    std::cout << "Executing 'other'\n";
    other();
    return 0;
  }
  int a = -1;
  int b = -1;

  // Read it all into a map.
  //
  // Insert potential answers proactively and mark them as such as we get inputs.
  std::map<int, bool> values;
  while (std::cin.good()) {
    int x;
    std::cin >> x;

    auto co_result = 2020 - x;

    // If this value has already been marked as being an answer, spit it out.
    if (values[x]) {
      // We found our answer
      a = x;
      b = co_result;
      while (std::cin) {
        int x;
        std::cin >> x;
      }
      break;
    } else {
      values[co_result] = true;
    }
  }

  if (a == -1 || b == -1) {
    std::cerr << "Didn't get an answer...\n";
    return -1;
  }

  std::cout << "The answer is " << a << " x " << b << " = " << a * b << "\n";
  return 0;
}


void other() {
  int a = -1;
  int b = -1;
  int c = -1;

  std::vector<int> values;
  while (std::cin.good()) {
    int x;
    std::cin >> x;
    values.push_back(x);
  }

  // 2020 = x + y + z
  //
  // 2020 - x' = k
  // k - y' = z'

  for (const auto& v : values) {
    auto k = 2020 - v;

    std::cout << "Looking for answers with k = " << k << "\n";
    std::map<int, bool> answers;
    for (const auto& x: values) {
      auto y = k - x;
      if (answers[x]) {
        a = x;
        b = y;
        c = v;
        break;
      } else {
        answers[y] = true;
      }
    }

    if (a != -1 && b != -1 && c != -1) {
      // We got an answer.
      break;
    }
  }


  if (a == -1 || b == -1 || c == -1) {
    std::cerr << "Didn't get an answer...\n";
    return;
  }

  std::cout << "The answer is " << a << " x " << b << " x " << c << " = " << a * b * c << "\n";
  return;
}
