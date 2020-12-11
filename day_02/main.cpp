#include <iostream>
#include <algorithm>
#include <cassert>

void other();

int main(int argc, char*[]) {
  if (argc == 2) {
    other();
    return 0;
  }

  int valid_passwords = 0;
  while (std::cin.good()) {
    char sep;

    int l;
    int m;
    char c;
    std::string pass;

    std::cin >> l;
    std::cin >> sep;
    if (!std::cin) break;
    assert(sep == '-');
    std::cin >> m;
    if (!std::cin) break;
    std::cin >> c;
    if (!std::cin) break;
    std::cin >> sep;
    if (!std::cin) break;
    assert(sep == ':');

    std::cin >> pass;

    std::cout << "Password is: '" << pass << "'\n";

    // l - lowest number of times c must appear
    // m - highest number of times c must appear
    // c - the required character

    auto count = std::count(pass.begin(), pass.end(), c);
    if (l <= count && count <= m) {
      // Password is good.
      valid_passwords++;
    }
  }

  std::cout << "There are " << valid_passwords << " valid passwords.\n";
  return 0;
}

void other()
{
  int valid_passwords = 0;
  while (std::cin.good()) {
    char sep;

    int l;
    int m;
    char c;
    std::string pass;

    std::cin >> l;
    std::cin >> sep;
    if (!std::cin) break;
    assert(sep == '-');
    std::cin >> m;
    if (!std::cin) break;
    std::cin >> c;
    if (!std::cin) break;
    std::cin >> sep;
    if (!std::cin) break;
    assert(sep == ':');

    std::cin >> pass;

    std::cout << "Password is: '" << pass << "'\n";

    // l - index 1 at which c may appear
    // m - index 2 at which c may appear
    // c - the required character at either l or m

    auto a = false;
    if (l <= pass.size()) {
      --l;
      if (pass[l] == c) {
        a = true;
      }
    }

    auto b = false;
    if (m <= pass.size()) {
      --m;
      if (pass[m] == c) {
        b = true;
      }
    }

    if (a != b) {
      ++valid_passwords;
    }
  }

  std::cout << "There are " << valid_passwords << " valid passwords.\n";
}
