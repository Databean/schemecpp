#include "Object.h"
#include "Number.h"
#include "Preprocessor.h"

using namespace std;
using namespace pscheme;

/**
 * Invoked as (cons a b). Creates a new pair out of the two parameters.
 */
class ConsFunction : public Function {
public:
	ConsFunction() {}
	virtual ~ConsFunction() {}
	virtual Object* call(Object* _params,Scope *s) {
		if(_params->getType()!=TYPE_PAIR) {
			throw "cons expects 2 parameters";
		}
		Pair* params = reinterpret_cast<Pair*>(_params);
		Object* left = params->getLeft();
		Object* r = params->getRight();
		if(r->getType()!=TYPE_PAIR) {
			throw "cons expects 2 parameters";
		}
		Pair* rl = reinterpret_cast<Pair*>(r);
		if(rl->getRight()->getType()!=TYPE_EMPTY_LIST) {
			throw "cons expects 2 parameters";
		}
		return new Pair(left,rl->getLeft());
	}
};
run(getRootScope()->defineValue("cons",new ConsFunction());)

/**
 * Invoked as (list a b c ...). Creates a list out of all the parameters given.
 */
class ListFunction : public Function {
public:
	ListFunction() {}
	virtual ~ListFunction() {}
	virtual Object* call(Object* _params,Scope* s) {
		return _params;
	}
};
run(getRootScope()->defineValue("list",new ListFunction());)