#include "Object.h"
#include "Number.h"
#include "Preprocessor.h"
#include "CPPFunction.h"

#include <iostream>

using namespace std;
using namespace pscheme;

/**
 * Invoked as (cons a b). Creates a new pair out of the two parameters.
 */
Object* cons(Object* left, Object* right) {
	return new Pair(left,right);
}
schemeFn(cons, Object*, Object*);

/**
 * Invoked as (list a b c ...). Creates a list out of all the parameters given.
 */ 
Object* list(Object* params, Scope* s) {
	return params;
}
schemeNameFnRaw("list", list);

/**
 * Invoked as (car mylist). Returns the first value in the list.
 */
Object* car(Pair* pair) {
	return pair->getLeft();
}
schemeFn(car, Pair*);

/**
 * Invoked as (cdr mylist). Returns the rest of the list.
 */
Object* cdr(Pair* pair) {
	return pair->getRight();
}
schemeFn(cdr, Pair*);
