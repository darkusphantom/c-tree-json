#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <list>
#include <sstream>
#include <vector>
using namespace std;

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

// Utils reading
//

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
