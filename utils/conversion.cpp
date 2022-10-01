#ifndef CONVERTION_H
#define CONVERTION_H

#include <iostream>
#include <list>
#include <vector>
using namespace std;

// Transform an vector of strings to string
// this method is usefull when you work with json
// @params __data is a vector of strings
// @return a string
string convertVectorToString(vector<string> data) {
  string dataString = "";

  for (int i = 0; i < data.size(); i++) {
    char lastWord = data[i].back();
    dataString.append(data[i]);

    if (lastWord == ',')
      dataString.append("\n");
  }

  return dataString;
}

#endif
