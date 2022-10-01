#include "tree/ArbolBinario/ArbolBinario.h"
#include "tree/ArbolN-Ario/ArbolNario.h"
#include "utils/clean.cpp"
#include "utils/conversion.cpp"
#include "utils/file.cpp"
#include "utils/utils.cpp"
#include "json/json.h"
#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;
using namespace json;

typedef pair<int, jobject> par;
typedef map<int, jobject> personMap;

// clean firstname, lastname and concat
string formatName(jobject person) {
  string firstname = person.get("nombre");
  string lastname = person.get("apellido");
  string fullname = firstname.append(lastname);
  fullname = cleanPunct(fullname);
  return fullname;
}

// Parsing slaves array
jobject parsingSlaves(jobject person) {
  string slaves = person.get("subordinados");
  jobject parsedSlaves = jobject::parse(slaves);
  return parsedSlaves;
}

// Set all people in a map
// @return map with person.
void setAllPeople(personMap &personData) {
  int i = 0, j = 0;
  int totalSlaves = 0;

  jobject personSlave = parsingSlaves(personData.at(0));
  int maxSlaves = personSlave.size();

  personMap auxPersonData;
  auxPersonData.insert(par(1, personSlave));

  map<int, jobject>::iterator iMap = auxPersonData.begin();
  while (j < maxSlaves + 1) {
    jobject personActual = iMap->second.array(i);
    jobject slaves = jobject::parse(personActual.get("subordinados"));

    personData.insert(par(personData.size(), personActual));
    i++;

    if (slaves.size() > 0) {
      auxPersonData.insert(par(j + 2, slaves));
      totalSlaves += slaves.size();
    }

    if (i == maxSlaves) {
      i = 0;
      maxSlaves = totalSlaves;
      totalSlaves = 0;
      iMap++;
      j++;
    }
  }
}

// Transform an map of json in a list with a key selected
list<string> convertMapJsonToList(personMap personData, string key) {
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
}

// Iterate a map of json and show ther keys and values
void showPeople(personMap personData) {
  map<int, jobject>::iterator iMap;

  for (iMap = personData.begin(); iMap != personData.end(); ++iMap) {
    jobject personActual = iMap->second;

    cout << "Clave: " << iMap->first;
    cout << " Valor: " << personActual.get("nombre") << endl;
  }
}

int main() {
  string entradaFile = "entrada.in";
  string mode = readFile(entradaFile).back();

  if (mode != "cedula" && mode != "nombre") {
    cout << "Error. Coloca en entrada.in nombre o cedula" << endl;
    return 1;
  }

  string jsonFile = "entrada.json";
  vector<string> jsonData = readFile(jsonFile);

  for (int i = 0; i < jsonData.size(); ++i) {
    jsonData[i] = cleanSpace(jsonData[i]);
  }

  string jsonString = convertVectorToString(jsonData);
  jobject person = jobject::parse(jsonString);

  personMap personData;
  personData.insert(par(0, person));
  jobject parsedSlaves = parsingSlaves(person);

  if (parsedSlaves.size() > 0) {
    setAllPeople(personData);
    list<string> listPeople = convertMapJsonToList(personData, "nombre");

    /*cout << listPeople.back() << endl;
    listPeople.pop_back();
    cout << listPeople.back() << endl;
    listPeople.pop_back();
    cout << listPeople.back() << endl;
    listPeople.pop_back();
    cout << listPeople.back() << endl;
    listPeople.pop_back();
    cout << listPeople.back() << endl;
    listPeople.pop_back();*/

  }

  return 0;
}
