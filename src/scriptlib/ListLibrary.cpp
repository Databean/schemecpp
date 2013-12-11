#include "Object.h"
#include "Number.h"
#include "Preprocessor.h"
#include "CPPFunction.h"

#include <iostream>

namespace pscheme {

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

	Object* map(Function* func, Object* toMap) {
		if(func->getType() == TYPE_MACRO) {
			throw "Can't use map on macros";
		}
		if(dynamic_cast<EmptyList*>(toMap)) {
			return new EmptyList();
		} else if(dynamic_cast<Pair*>(toMap)) {
			Pair* pair = reinterpret_cast<Pair*>(toMap);
			return new Pair(func->call(new Pair(pair->getLeft(), new EmptyList()), NULL), map(func, pair->getRight()));
		}
		throw "map must be called on a proper list";
	}
	schemeFn(map, Function*, Object*)
}
