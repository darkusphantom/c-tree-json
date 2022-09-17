#include "tree/ArbolBinario/ArbolBinario.h"
#include "tree/ArbolN-Ario/ArbolNario.h"
#include "utils/file.cpp"
#include "utils/person.h"
#include "utils/utils.cpp"
#include "json/json.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <list>
#include <string>

using namespace std;

int main() {
  string entradaFile = "entrada.in";
  string jsonFile = "entrada.json";
  vector<string> entradaInData = readFile(entradaFile);
  vector<string> jsonData = readFile(jsonFile);

  cleanSpace(jsonData);
  readVector(jsonData);

  return 0;
}
