#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int
count_target(
  const std::string& target,
  const std::string& color_rule,
  const std::map<std::string, std::vector<std::pair<int, std::string>>>& rules);

int
count_bags(
  const std::string& color_rule,
  const std::map<std::string, std::vector<std::pair<int, std::string>>>& rules);

int
main(int /*argc*/, char* /*argv*/[])
{
  std::map<std::string, std::vector<std::pair<int, std::string>>> rules;

  while (std::cin) {
    std::string line;
    std::getline(std::cin, line);
    if (line.empty()) {
      break;
    }

    std::stringstream ss{ line };

    std::string adj;
    std::string col;
    ss >> adj;
    ss >> col;

    std::string temp;
    ss >> temp; // pull out "bags"
    ss >> temp; // pull out "contain"

    std::string key = adj + " " + col;
    auto& contents = rules[key];

    while (ss) {
      int x{ 0 };
      ss >> x;
      if (x == 0) {
        continue;
      }
      ss >> adj;
      ss >> col;
      ss >> temp; // "bag(s)"

      contents.push_back({ x, adj + " " + col });
    }
  }

  // Print out the rules.
  if constexpr (false) {
    std::cout << "Read in rules: \n";
    for (const auto& rule : rules) {
      std::cout << rule.first << " bags contain ";
      if (rule.second.empty()) {
        std::cout << "no other bags";
      }
      bool first = true;
      for (const auto& pr : rule.second) {
        std::cout << (first ? "" : ", ") << pr.first << " " << pr.second
                  << " bag " << (pr.first > 1 ? "s" : "");
        first = false;
      }
      std::cout << ".\n";
    }
  }

  const std::string target = "shiny gold";
  int target_count = 0;
  for (const auto& rule : rules) {
    if (count_target(target, rule.first, rules) != 0) {
      ++target_count;
    }
  }

  std::cout << "Rules with shiny gold in them: " << target_count << "\n";

  auto total_bags = count_bags(target, rules);
  std::cout << "required bags " << total_bags << "\n";
  return 0;
}

int
count_target(
  const std::string& target,
  const std::string& color_rule,
  const std::map<std::string, std::vector<std::pair<int, std::string>>>& rules)
{
  auto count = 0;

  if (rules.at(color_rule).empty()) {
    return 0;
  }

  for (const auto& subrule : rules.at(color_rule)) {
    if (subrule.second == target) {
      ++count;
    } else {
      count += count_target(target, subrule.second, rules);
    }
  }
  return count;
}

int
count_bags(
  const std::string& color_rule,
  const std::map<std::string, std::vector<std::pair<int, std::string>>>& rules)
{

  if (rules.at(color_rule).empty()) {
    return 0;
  }

  auto total = 0;
  for (const auto& subrule : rules.at(color_rule)) {
    total += subrule.first;
    total += subrule.first * count_bags(subrule.second, rules);
  }
  return total;
}
