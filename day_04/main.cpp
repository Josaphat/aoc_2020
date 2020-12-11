#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

void
other();

std::ostream&
operator<<(std::ostream& os, const std::map<std::string, std::string>& m)
{
  os << "{\n";
  for (const auto& pr : m) {
    os << "\t" << pr.first << ": " << pr.second << "\n";
  }
  return os << "}\n";
}

int
main(int argc, char* /*argv*/[])
{
  if (argc > 1) {
    other();
    return 0;
  }

  std::vector<std::map<std::string, std::string>> passports;
  while (std::cin) {
    passports.push_back({});
    while (std::cin) {
      std::string l;
      std::getline(std::cin, l);
      if (l.empty()) {
        // Record done.
        break;
      }

      std::stringstream ss{ l };
      while (ss) {
        std::string field;
        ss >> field;
        if (field.empty())
          continue;

        // split at the ':' character
        auto name_end = field.find_first_of(':', 0);
        std::string name = field.substr(0, name_end);
        std::string value = field.substr(name_end + 1);
        passports.back()[name] = value;
      }
    }
  }

  int valid_passports = 0;
  for (const auto& passport : passports) {
    std::map<std::string, bool> checklist = {
      { "byr", false }, { "iyr", false }, { "eyr", false }, { "hgt", false },
      { "hcl", false }, { "ecl", false }, { "pid", false }, { "cid", false },
    };
    for (const auto& pr : passport) {
      checklist[pr.first] = true;
    }

    auto is_valid = true;
    for (const auto& item : checklist) {
      if (item.first != "cid" && item.second == false) { // cid is optional
        is_valid = false;
        break;
      }
    }

    if (is_valid) {
      ++valid_passports;
    }
  }

  std::cout << "valid passports: " << valid_passports << "\n";
}

void
other()
{
  struct Height
  {
    enum unit
    {
      in,
      cm
    };
    int val;
    unit u;
  };

  struct Passport
  {
    std::optional<int> byr;
    bool byr_is_valid() const
    {
      if (!byr.has_value()) {
        std::cout << "byr has no value\n";
        return false;
      }
      auto a = byr.has_value() && *byr >= 1920 && *byr <= 2002;
      if (!a) { std::cout << "byr is not in range: " << *byr << "\n"; }
      return a;
    }
    void byr_parse(std::string val)
    {
      try {
        std::cout << "Parsing byr: " << val << "\n";
        byr = std::stoi(val);
        std::cout << "byr: " << *byr << "\n";
      } catch (...) {
        // ignore problems.
      }
    }

    std::optional<int> iyr;
    bool iyr_is_valid() const
    {
      if (!iyr.has_value()) {
        std::cout << "iyr has no value\n";
        return false;
      }

      auto a = iyr.has_value() && *iyr >= 2010 && *iyr <= 2020;
      if (!a) { std::cout << "iyr out of range: " << *iyr << "\n"; }
      return a;
    }
    void iyr_parse(std::string val)
    {
      try {
        iyr = std::stoi(val);
      } catch (...) {
        // ignore problems.
      }
    }

    std::optional<int> eyr;
    bool eyr_is_valid() const
    {
      auto a = eyr.has_value() && *eyr >= 2020 && *eyr <= 2030;
      if (!a) { std::cout << "eyr is invalid\n"; }
      return a;
    }
    void eyr_parse(std::string val)
    {
      try {
        eyr = std::stoi(val);
      } catch (...) {
        // ignore problems.
      }
    }

    std::optional<Height> hgt;
    bool hgt_is_valid() const
    {
      if (!hgt.has_value()) {
        std::cout << "no hgt value\n";
        return false;
      }

      if (hgt->u == Height::in) {
        auto a = hgt->val >= 59 && hgt->val <= 76;
        if (!a) { std::cout << "inches height is invalid\n"; }
        return a;
      } else if (hgt->u == Height::cm) {
        auto a = hgt->val >= 150 && hgt->val <= 193;
        if (!a) { std::cout << "cm height is invalid\n"; }
        return a;
      } else {
        std::cout << "hgt other is invalid\n";
        return false;
      }
    }
    void hgt_parse(std::string val)
    {
      try {
        std::size_t pos;

        int length = std::stoi(val, &pos);
        std::string u = val.substr(pos);
        auto unit = u == "in" ? Height::in : u == "cm" ? Height::cm : throw u;
        hgt = { length, unit };
      } catch (...) {
        // ignore problems
      }
    }

    std::optional<std::string> hcl;
    bool hcl_is_valid() const
    {
      if (!hcl.has_value())
        return false;

      // starts with #
      if (hcl->size() != 7) {
        std::cout << "hcl wrong length\n";
        return false;
      }

      if ((*hcl)[0] != '#') {
        std::cout << "hcl doesn't start with #\n";
        return false;
      }

      for (const auto& c : hcl->substr(1)) {
        if (c < '0' || c > '9') {
          if (c < 'a' || c > 'f') {
            // bad
            std::cout << "not 0-9a-f\n";
            return false;
          } else {
            // a-f
          }
        } else {
          // 0-9
        }
      }

      return true;
    }
    void hcl_parse(std::string val) { hcl = val; }

    std::optional<std::string> ecl;
    bool ecl_is_valid() const
    {
      auto a =  ecl.has_value() &&
             (*ecl == "amb" || *ecl == "blu" || *ecl == "brn" ||
              *ecl == "gry" || *ecl == "grn" || *ecl == "hzl" || *ecl == "oth");
      if (!a) std::cout << "ecl is invalid\n";
      return a;
    }
    void ecl_parse(std::string val) { ecl = val; }

    std::optional<std::string> pid;
    bool pid_is_valid() const
    {
      if (!pid.has_value()) {
        std::cout << "pid has no value\n";
        return false;
      }

      if (pid->size() != 9) {
        std::cout << "pid is wrong size\n";
        return false;
      }

      for (const auto& c : *pid) {
        if (c < '0' || c > '9') {
          std::cout << "pid character not 0-9\n";
          return false;
        }
      }
      return true;
    }
    void pid_parse(std::string val) { pid = val; }

    std::optional<std::string> cid;
    bool cid_is_valid() const
    {
      // ignored.
      return true;
    }
    void cid_parse(std::string val) { cid = val; }

    void insert(std::string name, std::string value)
    {
      if ("byr" == name) {
        byr_parse(value);
      } else if ("iyr" == name) {
        iyr_parse(value);
      } else if ("eyr" == name) {
        eyr_parse(value);
      } else if ("hgt" == name) {
        hgt_parse(value);
      } else if ("hcl" == name) {
        hcl_parse(value);
      } else if ("ecl" == name) {
        ecl_parse(value);
      } else if ("pid" == name) {
        pid_parse(value);
      } else if ("cid" == name) {
        cid_parse(value);
      }
    }
  };

  std::vector<Passport> passports;
  while (std::cin) {
    passports.push_back({});
    while (std::cin) {
      std::string l;
      std::getline(std::cin, l);
      if (l.empty()) {
        // Record done.
        break;
      }

      std::stringstream ss{ l };
      while (ss) {
        std::string field;
        ss >> field;
        if (field.empty())
          continue;

        // split at the ':' character
        auto name_end = field.find_first_of(':', 0);
        std::string name = field.substr(0, name_end);
        std::string value = field.substr(name_end + 1);
        passports.back().insert(name, value);
      }
    }
  }

  auto valid_passports = 0;

  for (const auto& passport : passports) {
    if (passport.byr_is_valid() && passport.iyr_is_valid() &&
        passport.eyr_is_valid() && passport.hgt_is_valid() &&
        passport.hcl_is_valid() && passport.ecl_is_valid() &&
        passport.pid_is_valid() && passport.cid_is_valid()) {
      ++valid_passports;
    }
  }

  std::cout << "There are " << valid_passports << " valid passports\n";
}
