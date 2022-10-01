#ifndef CLEAN_H
#define CLEAN_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Clean space of a string
// @params __string with spaces
// @return a string without spaces
string cleanSpace(string strings) {
  auto start = strings.begin();
  auto end = strings.end();
  strings.erase(remove_if(start, end, ::isspace), end);
  return strings;
}

// Clean symbols and puncts of a string
// @params __string with puncts and symbols
// @return a string without puncts and symbols
string cleanPunct(string strings) {
  auto start = strings.begin();
  auto end = strings.end();
  strings.erase(remove_if(start, end, ::ispunct), end);
  return strings;
}

#endif
