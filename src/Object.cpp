#include "Object.h"
#include <iostream>

using std::string;

namespace pscheme {
	
	Pair::Pair(Object* left,Object* right) {
		this->left = left;
		this->right = right;
	}
	Pair::~Pair() {
		delete left;
		delete right;
	}
	Object* Pair::evaluate(Scope* s) {
		if(left==NULL) {
			throw "attempting to call empty pair";
		}
		Object* leval = left->evaluate(s);
		if(leval->getType()==TYPE_FUNCTION||leval->getType()==TYPE_MACRO) {
			Function* f = static_cast<Function*>(leval);
			if(right->getType()==TYPE_PAIR) {
				if(f->getType()==TYPE_FUNCTION) {
					return f->call(static_cast<Pair*>(right)->getEvaluated(s),s);
				} else {
					return f->call(right,s);
				}
			} else if(right->getType()==TYPE_EMPTY_LIST) {
				return f->call(right,s);
			} else {
				throw "error: right side of function call is not a list....?";
			}
		}
		else {
			throw "error: left side of (...) is not a function";
		}
	}
	Pair* Pair::getEvaluated(Scope* s) {
		Object* newLeft = left->evaluate(s);
		Object* newRight;
		if(right->getType()==TYPE_PAIR) {
			newRight = static_cast<Pair*>(right)->getEvaluated(s);
		} else {
			newRight = right->evaluate(s);
		}
		return new Pair(newLeft,newRight);
	}
	string Pair::toString() {
		string s = "(";
		Object* r = this;
		while(true) {
			if(r->getType()==TYPE_PAIR) {
				Pair* rl = static_cast<Pair*>(r);
				s += rl->getLeft()->toString();
				if(rl->getRight()->getType()!=TYPE_EMPTY_LIST) {
					s += " ";
				}
				r = rl->getRight();
			} else if(r->getType()==TYPE_EMPTY_LIST) {
				break;
			} else {
				s += ". " + r->toString();
				break;
			}
		}
		s += ")";
		return s;
	}
	/*
	Object Pair::nth(int n) {
		if(n == 0) {
			return left;
		} else {
			if(right->getType() == TYPE_PAIR) {
				return static_cast<Pair*>(right)->nth(n-1);
			} else {
				throw "error: list is not long enough for nth";
			}
		}
	}*/
	
	Object* Identifier::evaluate(Scope* s) { 
		Object* ret = s->getValue(name);
		if(!ret) {
			throw "no object in scope with name " + name;
		}
		return ret;
	}
	
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
		if(p->getLeft()==NULL) {
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
