#ifndef FICHAJUNG_STRING_UTIL_H
#define FICHAJUNG_STRING_UTIL_H

#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

void tokenize(const std::string &string, const char &delim, std::vector<std::string> &out);

bool is_number(const std::string& s);

#endif //FICHAJUNG_STRING_UTIL_H
