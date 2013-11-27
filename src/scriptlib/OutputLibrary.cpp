#include "Object.h"
#include "Preprocessor.h"
#include <iostream>

using namespace pscheme;
using namespace std;

Object* display(Object* params,Scope* s) {
	cout << params->toString() << endl;
	return new Void();
};
schemeFn(display);
