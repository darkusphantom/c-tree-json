#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>
using namespace std;


template <class type> void cleanSpace(vector<type> &strings) {
  for (int i = 0; i < strings.size(); ++i) {
    auto start = strings[i].begin();
    auto end = strings[i].end();
    strings[i].erase(remove_if(start, end, ::isspace), end);
  }
}

string cleanPunct(string strings) {
  auto start = strings.begin();
  auto end = strings.end();

  strings.erase(remove_if(start, end, ::ispunct), end);
  return strings;
}

// Obtiene los valores de una linea, leyendo caracter por caracter
void getReadWordByWord(list<int> &principalList, list<string> &listType) {
  int value;
  string word, line, typeList;

  cin >> typeList;
  if (typeList != "\n") {
    listType.push_back(typeList);
    getline(cin, line);
    // cout << line << endl;

    stringstream stringLine(line);
    while (stringLine >> word) {
      value = stoi(word);
      principalList.push_back(value);
    }
  }
}

template <class type> void readVector(vector<type> words) {
  for (int i = 0; i < words.size(); ++i) {
    // cout << i + 1 << ": " << words[i] << endl;
    cout << words[i] << endl;
  }
}

template <class type> void readList(list<type> listElements) {
  for (int i = 0; i < listElements.size(); ++i) {
    cout << listElements.back() << endl;
    listElements.pop_back();
  }
}

#endif
