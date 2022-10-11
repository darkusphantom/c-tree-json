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
typedef vector<string> nodeVector;
typedef list<nodeVector> vectorList;

// clean firstname, lastname and concat
string formatName(jobject person) {
  string firstname = person.get("nombre");
  string lastname = person.get("apellido");
  string fullname = firstname.append(lastname);
  fullname = cleanPunct(fullname);
  return fullname;
}

// Parsing slaves array
// @params1 a jobject to get the "subordinados"
// @return a jobject of slaves
jobject parsingSlaves(jobject person) {
  string slaves = person.get("subordinados");
  jobject parsedSlaves = jobject::parse(slaves);
  return parsedSlaves;
}

// get a map list by level
// @params1 a map list with the root of json
// @return map with person.
personMap getByLevel(personMap personData) {
  int i = 0, j = 0;
  int totalSlaves = 0;

  // Parsing slaves of first person and get the max
  jobject personSlave = parsingSlaves(personData[0]);
  int maxSlaves = personSlave.size();

  // Insert the slaves obtained
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

    // When i == maxSlaves, pass to the next level and reset counters
    if (i == maxSlaves) {
      i = 0;                   // Reset slave
      maxSlaves = totalSlaves; // Max slaves of the next level
      totalSlaves = 0;
      iMap++;
      j++;
    }
  }

  return personData;
}

// Get a map list in preorden
// @params1 a map list with the root of json
// @return map with person.
personMap getPeoplePreorden(personMap personData) {
  int i = 0, j = 0;
  list<int> totalSlaves;

  jobject personSlave = parsingSlaves(personData[0]);
  int maxSlaves = personSlave.size();

  personMap auxPersonData;
  auxPersonData.insert(par(1, personSlave));

  map<int, jobject>::iterator iMap = auxPersonData.begin();
  while (i < maxSlaves) {
    jobject personActual = iMap->second.array(i);
    jobject slaves = jobject::parse(personActual.get("subordinados"));

    personData.insert(par(personData.size(), personActual));
    i++;

    if (slaves.size() > 0) {
      auxPersonData.insert(par(i + 1, slaves));
      // coloca el valor actual del iterador para retomarlo
      totalSlaves.push_back(i);

      // Coloca el iterador maximo del siguiente
      totalSlaves.push_front(slaves.size());
      i = 0; // Reset slave
      iMap++;
    }

    if (!totalSlaves.empty()) {
      if (totalSlaves.front() == i) {
        totalSlaves.pop_front();
        i = totalSlaves.back();
        totalSlaves.pop_back();
        iMap--;
      }
    }
  }

  totalSlaves.clear();
  auxPersonData.clear();
  return personData;
}

// Get a map list in postorden
// @params1 a map list with the root of json
// @return map with person.
personMap getPeoplePostorden(personMap personData) {
  int i = 0;
  bool isRoadComplete = false;
  list<int> totalSlaves;

  jobject personSlave = parsingSlaves(personData[0]);
  int maxSlaves = personSlave.size();

  personMap auxPersonData, personWithSlaves;
  auxPersonData.insert(par(1, personSlave));

  map<int, jobject>::iterator iMap = auxPersonData.begin();
  while (i < maxSlaves) {
    jobject personActual = iMap->second.array(i);
    jobject slaves = jobject::parse(personActual.get("subordinados"));
    bool haveSlaves = slaves.size() > 0;

    if (!haveSlaves) {
      personData.insert(par(personData.size(), personActual));
    }
    i++;

    if (haveSlaves) {
      auxPersonData.insert(par(i + 1, slaves));
      personWithSlaves.insert(par(personWithSlaves.size(), personActual));

      // coloca el valor actual del iterador para retomarlo
      totalSlaves.push_back(i);

      // Coloca el iterador maximo del siguiente
      totalSlaves.push_front(slaves.size());
      i = 0; // Reset slave
      iMap++;
    }

    if (!haveSlaves && !totalSlaves.empty()) {
      if (totalSlaves.front() == i) {
        totalSlaves.pop_front();
        i = totalSlaves.back();
        totalSlaves.pop_back();
        iMap--;
      }
    }
  }

  map<int, jobject>::iterator counter;
  auto init = personWithSlaves.begin();
  auto end = personWithSlaves.end();
  for (counter = init; counter != end; counter++) {
    jobject personActual = counter->second;
    personData.insert(par(personData.size(), personActual));
  }

  totalSlaves.clear();
  auxPersonData.clear();
  return personData;
}

// Get a map list in inorden
// @params1 a map list with the root of json
// @return map with person.
personMap getPeopleInorden(personMap personData) {
  int i = 0;
  bool isRoadComplete = false;
  list<int> totalSlaves;

  jobject personSlave = parsingSlaves(personData[0]);
  int maxSlaves = personSlave.size();

  personMap auxPersonData, personWithSlaves;
  auxPersonData.insert(par(1, personSlave));

  map<int, jobject>::iterator iMap = auxPersonData.begin();
  while (i < maxSlaves) {
    jobject personActual = iMap->second.array(i);
    jobject slaves = jobject::parse(personActual.get("subordinados"));
    bool haveSlaves = slaves.size() > 0;

    if (!haveSlaves) {
      // cout << "Persona actual: " << personActual.get("nombre") << endl;
      personData.insert(par(personData.size(), personActual));
    }
    i++;

    if (haveSlaves) {
      auxPersonData.insert(par(i + 1, slaves));
      personWithSlaves.insert(par(personWithSlaves.size(), personActual));

      // coloca el valor actual del iterador para retomarlo
      totalSlaves.push_back(i);

      // Coloca el iterador maximo del siguiente
      totalSlaves.push_front(slaves.size());
      i = 0; // Reset slave
      iMap++;
    }

    if (!haveSlaves && !totalSlaves.empty()) {
      if (totalSlaves.front() == i) {
        totalSlaves.pop_front();
        i = totalSlaves.back();
        totalSlaves.pop_back();
        iMap--;
      }
    }
  }

  map<int, jobject>::iterator counter;
  auto init = personWithSlaves.begin();
  auto end = personWithSlaves.end();
  for (counter = init; counter != end; counter++) {
    jobject personActual = counter->second;
    personData.insert(par(personData.size(), personActual));
  }

  totalSlaves.clear();
  auxPersonData.clear();
  personWithSlaves.clear();

  return personData;
}

// Delete of the first position the root and set in the correct position
// @params1: an postorden list map
// @return: a postorden list sorted correctly
personMap sortPostorden(personMap postorden) {
  jobject root = postorden[0];
  personMap newPostorden;

  postorden.erase(0);

  map<int, jobject>::iterator iMap = postorden.begin();
  map<int, jobject>::iterator end = postorden.end();

  while (iMap != postorden.end()) {
    jobject personActual = iMap->second;
    newPostorden.insert(par(newPostorden.size(), personActual));

    if (iMap->first == postorden.size())
      newPostorden.insert(par(newPostorden.size(), root));

    iMap++;
  }

  return newPostorden;
}

// Delete of the first position the root and set in the correct position
// @params1: an inorden list map
// @return: an inorden list sorted correctly
personMap sortInorden(personMap inorden) {
  int position = inorden.size() / 2;
  jobject root = inorden[0];
  personMap newInorden;

  inorden.erase(0);

  map<int, jobject>::iterator iMap = inorden.begin();
  while (iMap != inorden.end()) {
    jobject personActual = iMap->second;
    if (iMap->first == position) {
      newInorden.insert(par(newInorden.size(), root));
    }
    newInorden.insert(par(newInorden.size(), personActual));
    iMap++;
  }

  return newInorden;
}

// Build an string of the type orden
// @params1 a map list with the data of the tree orden
// @params2 the mode to get the key of the json (cedula or nombre)
// @params3 PREORDEN, INORDEN, POSTORDEN, BYLEVEL
// @return an array in string format by the type orden
string buildTypeListInString(personMap ordenList, string mode,
                             string typeOrden) {
  vector<string> newOrdenList;
  map<int, jobject>::iterator iMap;

  newOrdenList.push_back(typeOrden);
  newOrdenList.push_back(":[\"");

  for (iMap = ordenList.begin(); iMap != ordenList.end(); ++iMap) {
    jobject personActual = iMap->second;

    if (mode == "cedula") {
      newOrdenList.push_back(personActual.get("cedula"));
    }

    if (mode == "nombre") {
      string fullname = formatName(personActual);
      newOrdenList.push_back(fullname);
    }

    newOrdenList.push_back("\",\"");
  }

  string finale = convertVectorToString(newOrdenList);
  finale.pop_back();
  finale.pop_back();
  finale.push_back(']');

  return finale;
}

// Show in prompt the result
// @params1 a json object with data
// @params2 the mode cedula or nombre
void showData(personMap personData, string mode) {
  personMap preorden = getPeoplePreorden(personData);

  personMap postorden = getPeoplePostorden(personData);
  postorden = sortPostorden(postorden);

  personMap inorden = getPeopleInorden(personData);
  inorden = sortInorden(inorden);

  personMap byLevel = getByLevel(personData);

  string preordenFinal = buildTypeListInString(preorden, mode, "PREORDEN");
  string inordenFinal = buildTypeListInString(inorden, mode, "INORDEN");
  string postordenFinal = buildTypeListInString(postorden, mode, "POSTORDEN");
  string byLevelFinal = buildTypeListInString(byLevel, mode, "NIVELES");

  string data = preordenFinal + "\n" + inordenFinal + "\n" + postordenFinal +
                "\n" + byLevelFinal;

  cout << data << endl;
}
//
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
  jobject rootPerson = jobject::parse(jsonString);

  personMap personData;
  personData.insert(par(0, rootPerson));
  jobject parsedSlaves = parsingSlaves(rootPerson);

  if (parsedSlaves.size() > 0) {
    showData(personData, mode);
  }

  return 0;
}
