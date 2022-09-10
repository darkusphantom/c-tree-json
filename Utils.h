#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <list>

template <class type>
void readList(list<type> listElements) {
	int totalListElements = listElements.size();

	for (int i = 0; i < totalListElements; ++i) {
		cout << listElements.front() << endl;
		listElements.pop_front();
	}
}

void getListOrden(list<int> &principalList, list<string> &listType) {
	int value;
	string word, line, typeList;

	cin >> typeList;
	if (typeList != "\n") {
		listType.push_back(typeList);
		getline(cin, line);
		//cout << line << endl;

		stringstream stringLine(line);
		while (stringLine >> word) {
			value = stoi(word);
			principalList.push_back(value);
		}
	}
}

#endif
