#include <iostream>
#include <list>
#include "ArbolBinario.h"
#include "json.h"

using namespace std;

int main() {
	// variables declaration
	string input = "{ \"hello\": \"world\" }";
	json::jobject result = json::jobject::parse(input);

	//code
	string value = result.get("hello");
	cout << value;

	return 0;
}
