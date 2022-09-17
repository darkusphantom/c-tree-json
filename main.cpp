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
#include <map>
#include <string>

using namespace std;
using namespace json;

typedef pair<int, jobject> par;
typedef map<int, jobject> personMap;

string formatName(jobject person) {
  string firstname = person.get("nombre");
  string lastname = person.get("apellido");
  string fullname = firstname.append(lastname);

  fullname = cleanPunct(fullname);
  return fullname;
}

jobject parsingSlaves(jobject person) {
  string slaves = person.get("subordinados");
  jobject parsedSlaves = jobject::parse(slaves);

  return parsedSlaves;
}

void setAllPeople(personMap &personData) {
  // Iterators
  int i = 0, j = 0;

  // Total slaves if for the person slave actual
  int totalSlaves = 0;

  // Parsing slaves an get the max
  jobject personSlave = parsingSlaves(personData.at(0));
  int maxSlaves = personSlave.size();

  // insert the slaves obtained
  personMap auxPersonData;
  auxPersonData.insert(par(1, personSlave));

  // Get iterator of the map and start loop
  map<int, jobject>::iterator iMap = auxPersonData.begin();

  while (j < maxSlaves + 1) {
    jobject otherPerson = iMap->second.array(i);
    jobject slaves = jobject::parse(otherPerson.get("subordinados"));

    personData.insert(par(personData.size(), otherPerson));
    i++;

    // If exist an slave, insert in auxiliar personData map
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

void showPeople(personMap personData) {
  map<int, jobject>::iterator iMap;

  for (iMap = personData.begin(); iMap != personData.end(); ++iMap) {
    jobject otherPerson = iMap->second;

    cout << "Clave: " << iMap->first;
    cout << " Valor: " << otherPerson.get("nombre") << endl;
  }
}

int main() {
  string entradaFile = "entrada.in";
  string entradaInData = readFile(entradaFile).back();

  if (entradaInData != "cedula" && entradaInData != "nombre") {
    cout << "Error. Coloca en entrada.in nombre o cedula" << endl;
    return 1;
  }

  string jsonFile = "entrada.json";
  vector<string> jsonData = readFile(jsonFile);

  // Se limpia los espacios para evitar problemas al guardar en el jobject
  cleanSpace(jsonData);

  string jsonString = convertVectorToString(jsonData);
  jobject person = jobject::parse(jsonString);

  personMap personData;
  personData.insert(par(0, person));

  jobject parsedSlaves = parsingSlaves(person);

  if (parsedSlaves.size() > 0) {
    setAllPeople(personData);
    //showPeople(personData);
  }

  return 0;
}
