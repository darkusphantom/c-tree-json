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

/*list<string> convertMapJsonToList(personMap personData, string key) {
  map<int, jobject>::iterator iMap;
  list<string> listPeople;

  for (iMap = personData.begin(); iMap != personData.end(); ++iMap) {
    jobject personActual = iMap->second;

    if (key == "cedula") {
      string cleanedCi = cleanPunct(personActual.get(key));
      listPeople.push_front(cleanedCi);
    }

    if (key == "nombre") {
      string fullname = formatName(personActual);
      listPeople.push_front(fullname);
    }
  }
  return listPeople;
}*/


// Utils reading
//

template <class type> void readVector(vector<type> words) {
  for (int i = 0; i < words.size(); ++i) {
    // cout << i + 1 << ": " << words[i] << endl;
    cout << words[i] << endl;
  }
}

template <class type> void readList(list<type> listElements) {
  int max = listElements.size();
  for (int i = 0; i < max; ++i) {
    cout << listElements.back() << endl;
    listElements.pop_back();
  }
}

#endif
