#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <vector>
using namespace std;

template <class type> class Person {
private:
  string ci;
  string firstname;
  string lastname;
  vector<type> slaves;

public:
  Person();
  ~Person();

  void setCi(string ci);
  void setFirstname(string name);
  void setLastname(string name);
  void setSlaves(vector<type> slave);

  string getCi();
  string getFirstname();
  string getLastname();
  vector<type> getSlaves();
};

template <class type> Person<type>::Person() {
  this->ci = ' ';
  this->firstname = ' ';
  this->lastname = ' ';
};

template <class type> Person<type>::~Person() {
  this->ci = ' ';
  this->firstname = ' ';
  this->lastname = ' ';
  if (this->slaves.empty()) {
    this->slaves.clear();
  }
}

template <class type> void Person<type>::setCi(string ci) { this->ci = ci; };

template <class type> void Person<type>::setFirstname(string firstname) {
  this->firstname = firstname;
};

template <class type> void Person<type>::setLastname(string lastname) {
  this->lastname = lastname;
};

template <class type> void Person<type>::setSlaves(vector<type> slaves) {
  this->slaves = slaves;
};

template <class type> string Person<type>::getCi() { return this->ci; }

template <class type> string Person<type>::getFirstname() {
  return this->firstname;
}

template <class type> string Person<type>::getLastname() {
  return this->lastname;
}

template <class type> vector<type> Person<type>::getSlaves() {
  return this->slaves;
}

#endif /* ifndef PERSON_H */
