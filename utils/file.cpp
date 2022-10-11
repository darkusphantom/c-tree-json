#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

// Read a file
// @params a string with the name of the file
// @return a vector of string with the data of the filename
vector<string> readFile(string filename) {
  vector<string> lines;
  string line;

  ifstream file(filename.c_str());
  if (!file.is_open()) {
    cout << "Lo sentimos. El archivo que estás buscando no se encuentra en el "
            "directorio."
         << endl;
    cout << "Por favor, ve y revisa que estan los archivos 'entrada.in' y "
            "'entrada.json'."
         << endl;
    exit(EXIT_FAILURE);
  }

  while (getline(file, line)) {
    lines.push_back(line);
  }

  file.close();
  return lines;
}

// Write in a file
// @params1 a string with the data to write in the file
// @params2 the name of the file
void writeFile(string data, string filename) {
  ofstream file(filename.c_str());
  file << data;
  file.close();
}

#endif
