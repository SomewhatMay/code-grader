#include <algorithm>
#include <cctype>
#include <locale>

// trim from start (in place)
inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
  rtrim(s);
  ltrim(s);
}

std::string remove_all_whitespace(std::string line) {
  auto new_end = std::remove_if(line.begin(), line.end(), [](char x) {
    return (!std::isprint(x) || x == ' ');
  });
  line.erase(new_end, line.end());
  return line;
}

std::string shorten_line(const std::string &line, const int &length) {
  std::string short_ver = line.substr(0, length);

  if (line.length() > length) {
    short_ver += "...";
  }

  return short_ver;
}

std::string shorten_line(const std::string &line) { return shorten_line(line, 32); }