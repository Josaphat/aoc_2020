#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void other();

int main(int argc, char* []) {
  if (argc == 2) {
    other();
    return 0;
  }

  // Start by reading the input biome
  std::vector<std::string> biome;
  while (std::cin) {
    std::string line;
    std::getline(std::cin, line);
    std::cout << "line: '" << line << "'\n";
    if (line.size() > 0) {
      biome.push_back(line);
    }
  }

  // We want to assume that every line in the biome map is the same size.
  int width = -1;
  for (const auto& s : biome) {
    std::cout << s << "\n";
    if (width == -1) {
      width = s.size();
    } else {
      if (s.size() != width){
        // Assumption blown.
        std::cerr << "Input lines not all same width\n";
        return -1;
      }
    }
  }

  int rise = 1; // really "negative" one, since we're going down.
  int run = 3;

  int trees = 0;
  for (int row = 0, col = 0; row < biome.size(); row += rise, col += run) {
    auto c = biome[row] [col % width];
    if (c == '.') {
      // Open.
    }
    else if (c == '#') {
      // Watch out for that tree!
      ++trees;
    }
  }

  std::cout << "Path would encounter " << trees << " tree" << (trees > 1 ? "s." : ".") << "\n";
  return 0;
}

void other()
{

  // Start by reading the input biome
  std::vector<std::string> biome;
  while (std::cin) {
    std::string line;
    std::getline(std::cin, line);
    std::cout << "line: '" << line << "'\n";
    if (line.size() > 0) {
      biome.push_back(line);
    }
  }

  // We want to assume that every line in the biome map is the same size.
  int width = -1;
  for (const auto& s : biome) {
    std::cout << s << "\n";
    if (width == -1) {
      width = s.size();
    } else {
      if (s.size() != width){
        // Assumption blown.
        std::cerr << "Input lines not all same width\n";
        return;
      }
    }
  }

  // <run, rise>
  std::vector<std::pair<int, int>> slopes = {{1,1}, {3,1}, {5, 1}, {7, 1}, {1, 2} };
  std::vector<int> tree_results;

  for (const auto& slope : slopes) {
    int run = slope.first;
    int rise = slope.second;
    std::cout << "=== run: " << run << "\n"
              << "=== rise: " << rise << "\n";

    int trees = 0;
    for (int row = 0, col = 0; row < biome.size(); row += rise, col += run) {
      auto c = biome[row] [col % width];
      if (c == '.') {
        // Open.
      }
      else if (c == '#') {
        // Watch out for that tree!
        ++trees;
      }
    }

    std::cout << "=== Path would encounter " << trees << " tree" << (trees > 1 ? "s." : ".") << "\n";
    tree_results.push_back(trees);
  }

  auto answer = std::accumulate(tree_results.begin(), tree_results.end(), 1, [](const auto& a, const auto& b) { return a*b; });
  std::cout << "The product of the answers is: " << answer << "\n";
}
