#include "ScriptFunction.h"

namespace pscheme {
	ScriptFunction::ScriptFunction(Pair* parameters,Pair* expressions,Scope* s) {
		this->parameters = parameters;
		this->expressions = expressions;
		this->scope = new Scope(s);
	}
	
	ScriptFunction::~ScriptFunction() {
		
	}
	
	Object* ScriptFunction::call(Object* paramVals,Scope* _s /* unused - this is just for lambda */) {
		Pair* p = parameters;
		//Object* v = paramVals;
		Scope* s = new Scope(scope);
		if(p->getLeft()==nullptr) {
			if(paramVals->getType()==TYPE_EMPTY_LIST) {
				return run(s);
			} else {
				throw "function expects 0 parameters";
			}
		}
		if(paramVals->getType()==TYPE_EMPTY_LIST) {
			throw "function expects more than 0 parameters";
		}
		Pair* paramPair = static_cast<Pair*>(paramVals);
		while(true) {
			if(p->getLeft()->getType()!=TYPE_IDENTIFIER) {
				throw "non identifier in func param list";
			}
			Identifier* i = static_cast<Identifier*>(p->getLeft());
			s->defineValue(i->getName(),paramPair->getLeft());
			switch(p->getRight()->getType()) {
				case TYPE_EMPTY_LIST:
					if(paramPair->getRight()->getType()==TYPE_EMPTY_LIST) {
						return run(s);
					} else {
						throw "wrong amount of parameters";
					}
					break;
				case TYPE_IDENTIFIER: //dump the rest of the params in here, it's a varargs funcction
					s->defineValue(static_cast<Identifier*>(p->getRight())->getName(),paramPair->getRight());
					return run(s);
					break;
				case TYPE_PAIR:
					if(paramPair->getRight()->getType()!=TYPE_PAIR) {
						throw "function expected more parameters";
					} else {
						paramPair = static_cast<Pair*>(paramPair->getRight());
						p = static_cast<Pair*>(p->getRight());
					}
					break;
				default:
					throw "unexpected type in param list";
			}
		}
	}
	
	Object* ScriptFunction::run(Scope* s) {
		Pair* p = expressions;
		while(true) {
			Object* tempVal = p->getLeft()->evaluate(s);
			switch (p->getRight()->getType()) {
				case TYPE_EMPTY_LIST:
					return tempVal;
					break;
				case TYPE_PAIR:
					p = static_cast<Pair*>(p->getRight());
					break;
				default:
					throw "unexpected value in expression list";
					break;
			}
		}
	}
}