#include <iostream>
#include <list>
#include "tree/ArbolBinario/ArbolBinario.h"
#include "tree/ArbolN-Ario/ArbolNario.h"
#include "utils/person.h"

using namespace std;

int main() {
  Person<string> *person = new Person<string>();
  person->setCi("25");
  person->setFirstname("Dorime");
  person->setLastname("Ameno");

  cout << person->getCi() << endl;
  cout << person->getFirstname() << endl;
  cout << person->getLastname() << endl;

  vector<Person<string>> people;
  people.push_back(*person);
  people.push_back(*person);

  cout << "People: " << people.back().getCi() << endl;
  cout << "Length" << people.size() << endl;

  return 0;
}
