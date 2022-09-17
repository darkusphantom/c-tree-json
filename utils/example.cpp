#include "tree/ArbolBinario/ArbolBinario.h"
#include "tree/ArbolN-Ario/ArbolNario.h"
#include "utils/person.h"
#include "json/json.h"
#include <iostream>
#include <list>

using namespace std;

int main() {
  // JSON
  // variables declaration
  string input = "{ \"hello\": \"world\" }";
  json::jobject result = json::jobject::parse(input);
  // code
  string value = result.get("hello");
  cout << value << endl;

  // Utils - People
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
