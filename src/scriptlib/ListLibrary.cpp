#include "Object.h"
#include "Number.h"
#include "Preprocessor.h"

using namespace std;
using namespace pscheme;

/**
 * Invoked as (cons a b). Creates a new pair out of the two parameters.
 */
Object* cons(Object* _params, Scope* s) {
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
schemeFn(cons);

/**
 * Invoked as (list a b c ...). Creates a list out of all the parameters given.
 */
Object* list(Object* params, Scope* s) {
	return params;
}
schemeFn(list);
