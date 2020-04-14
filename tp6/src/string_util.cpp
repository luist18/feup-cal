#include "string_util.h"

void tokenize(const std::string &string, const char &delim, std::vector<std::string> &out) {
    std::stringstream ss(string);

    std::string s;
    while (getline(ss, s, delim)) {
        out.push_back(s);
    }
}

bool is_number(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
