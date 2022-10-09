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
// @return a jobject of slaves
jobject parsingSlaves(jobject person) {
  string slaves = person.get("subordinados");
  jobject parsedSlaves = jobject::parse(slaves);
  return parsedSlaves;
}

// get a map list by level
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
    personMap preorden = getPeoplePreorden(personData);
    showPeople(preorden);
    cout << endl;
    personMap byLevel = getByLevel(personData);
    showPeople(byLevel);
  }

  return 0;
}
