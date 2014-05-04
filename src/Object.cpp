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
		if(left==nullptr) {
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
}
