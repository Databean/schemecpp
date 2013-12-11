#include "Object.h"
#include "Preprocessor.h"
#include <iostream>

using std::cout;
using std::endl;

namespace pscheme {
	
	Object* display(Object* params) {
		cout << params->toString() << endl;
		return new Void();
	};
	schemeFn(display);
	
}
