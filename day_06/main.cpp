#include <array>
#include <bitset>
#include <iostream>
#include <vector>

void
other();

int
main(int argc, char* /*argv*/[])
{
  if (argc > 1) {
    other();
    return 0;
  }

  std::vector<std::bitset<26>> plane_answers{};

  while (std::cin) {

    std::bitset<26> group_answers;
    int group_members = 0;
    while (std::cin) {
      std::string line;
      std::getline(std::cin, line);

      if (line.empty()) {
        break;
      }
      ++group_members;
      std::bitset<26> answers{};
      for (const auto& c : line) {
        const auto idx = c - 'a';
        answers[idx] = true;
      }

      // OR in the answers for this person.
      group_answers |= answers;
    }

    if (group_members != 0) {
      plane_answers.push_back(group_answers);
    }
  }

  int sum = 0;
  for (const auto& ga : plane_answers) {
    sum += ga.count();
  }

  std::cout << "Sum of 'yes's: " << sum << "\n";

  return 0;
}

void
other()
{

  std::vector<std::bitset<26>> plane_answers{};

  while (std::cin) {

    // We're using an AND operation to clear any values to which somebody says
    // "no" so we need to start with everything set to one.
    std::bitset<26> group_answers;
    group_answers.flip();

    // To make sure we don't count an empty group.
    int group_members = 0;
    while (std::cin) {
      std::string line;
      std::getline(std::cin, line);

      if (line.empty()) {
        break;
      }
      ++group_members;
      std::bitset<26> answers{};
      for (const auto& c : line) {
        const auto idx = c - 'a';
        answers[idx] = true;
      }

      // 'AND' in the answers for this person.
      group_answers &= answers;
    }

    if (group_members != 0) {
      plane_answers.push_back(group_answers);
    }
  }

  int sum = 0;
  for (const auto& ga : plane_answers) {
    sum += ga.count();
  }

  std::cout << "Sum of 'yes's: " << sum << "\n";
}
