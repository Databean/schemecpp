#include "Object.h"
#include "Preprocessor.h"
#include <iostream>

using namespace pscheme;
using namespace std;

class DisplayFunction : public Function {
public:
	DisplayFunction() {}
	virtual ~DisplayFunction() {}
	virtual Object* call(Object* params,Scope* s) {
		cout << params->toString() << endl;
		return new Void();
	}
};
run(getRootScope()->defineValue("display",new DisplayFunction());)