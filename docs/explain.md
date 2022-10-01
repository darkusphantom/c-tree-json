# Explicación del código

En la explicación del código se explicará acerca de cómo está estructurado el proyecto y que hace cada método que se encuentra en el `main.cpp`. Explico el `main.cpp` a parte para mantener limpio ese archivo. Por otro lado, los códigos que se encuentran en `utils` está documentados en sus respectivos archivos.

## Estructura del código

El código esta estructurado de la siguiente manera:

- `docs`: Contiene la documentación del proyecto y la explicación del código.
- `json`: Contiene la librería de [Simpleson](https://github.com/gregjesl/simpleson). Este va asociado al archivo `json.cpp`
- `tree`: Contiene las librerías para trabajar con un árbol binario y N-ario
- `utils`: Contiene utilidades que ayuda en el trabajo del código.
- `entrada.in`: Contiene el formato de entrada, si será la lectura por nombre o cédula.
- `entrada.json`: Contiene los datos del json a trabajar.
- `main.cpp`: Contiene el código principal para trabajar en el proyecto.
- `makefile`: Se utiliza para compilar todo el proyecto.
- `proyecto`: Es el ejecutable del proyecto.
- `readme.md`: Contiene las instrucciones del proyecto.

## Explicación de main.cpp

- Importaciones:

```c++
#include "tree/ArbolBinario/ArbolBinario.h"
#include "tree/ArbolN-Ario/ArbolNario.h"
#include "utils/clean.cpp" // Para limpiar los strings
#include "utils/conversion.cpp" // Para convertir de un tipo a otro
#include "utils/file.cpp" // Para obtener datos de un archivo
#include "utils/utils.cpp" // Utilidades como lectura un tipo de dato en cadena
#include "json/json.h" // Libreria de simpleson
#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;
using namespace json;

typedef pair<int, jobject> par; // Pares que van dentro de map
typedef map<int, jobject> personMap; // Tipo de dato para trabajar con persona en formato map

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

// Convierte un map de json a una lista
// y guarda el valor que indica la llave
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

//Función para mostrar la llave y los valores de un map con json
void showPeople(personMap personData) {
  map<int, jobject>::iterator iMap;

  for (iMap = personData.begin(); iMap != personData.end(); ++iMap) {
    jobject personActual = iMap->second;

    cout << "Clave: " << iMap->first;
    cout << " Valor: " << personActual.get("nombre") << endl;
  }
}
```

- Main

```c++
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
  // Obtiene el valor que será la key a utilizar en el json
  string entradaFile = "entrada.in";
  string mode = readFile(entradaFile).back();

  if (mode != "cedula" && mode != "nombre") {
    cout << "Error. Coloca en entrada.in nombre o cedula" << endl;
    return 1;
  }

  // Obtiene la información del json y guarda cada linea
  // en cada espacio del vector
  string jsonFile = "entrada.json";
  vector<string> jsonData = readFile(jsonFile);

  // Se limpia los espacios para evitar problemas al guardar en el jobject
  // Si el string tiene espacios demás, al hacer parsing falla
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
    list<string> listPeople = convertMapJsonToList(personData, "nombre");
  }

  return 0;
}
```

