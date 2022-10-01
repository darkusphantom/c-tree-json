#include "tree/ArbolBinario/ArbolBinario.h"
#include "tree/ArbolN-Ario/ArbolNario.h"
#include "utils/clean.cpp"
#include "utils/conversion.cpp"
#include "utils/file.cpp"
#include "utils/person.h"
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

// FormatName limpia todo el string dejando solo las letras.
string formatName(jobject person) {
  string firstname = person.get("nombre");
  string lastname = person.get("apellido");
  string fullname = firstname.append(lastname);

  fullname = cleanPunct(fullname);
  return fullname;
}

// Parsing slaves se usa cada vez que el array de subordinados pierde el parsing
jobject parsingSlaves(jobject person) {
  string slaves = person.get("subordinados");
  jobject parsedSlaves = jobject::parse(slaves);

  return parsedSlaves;
}

// Agrega todos los subordinados a una sola lista
// Tambien se usa para obtener la lista como un arbol por niveles
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
    jobject personActual = iMap->second.array(i);
    jobject slaves = jobject::parse(personActual.get("subordinados"));

    // Se agrega la persona actual junto a su key (personData.size())
    personData.insert(par(personData.size(), personActual));
    i++;

    // If exist an slave, insert in auxiliar personData map
    if (slaves.size() > 0) {
      auxPersonData.insert(par(j + 2, slaves));
      totalSlaves += slaves.size();
    }

    // Cuando llegue al máximo de subordinados, se reinicia el conteo hasta que
    // nadie tenga más subordinados
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

  // Se limpia los espacios para evitar problemas al guardar en el jobject
  for (int i = 0; i < jsonData.size(); ++i) {
    jsonData[i] = cleanSpace(jsonData[i]);
  }

  // Convierte todo el vector en un string para luego hacer parsing
  string jsonString = convertVectorToString(jsonData);
  jobject person = jobject::parse(jsonString);

  // Se añade el primer elemento del json para centrarse luego en sus
  // subordinados
  personMap personData;
  personData.insert(par(0, person));

  // Se hace parsing a los subordinados del primer elemento
  jobject parsedSlaves = parsingSlaves(person);

  if (parsedSlaves.size() > 0) {
    setAllPeople(personData);
    showPeople(personData);
  }

  return 0;
}
