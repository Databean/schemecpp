#include "Scope.h"

using std::string;

namespace pscheme {
	
	Scope::Scope(Scope* _parent) { parent = _parent; }
	Scope::~Scope() { }
	void Scope::defineValue(string name,Object* value) {
		variables[name]=value;
	}
	void Scope::setValue(string name,Object* value) {
		if(!(variables.count(name))) {
			if(parent) { parent->setValue(name,value); }
			else { throw "no such variable " + name; }
		} else {
			variables[name] = value;
		}
	}
	Object* Scope::getValue(string name) {
		if(!(variables.count(name))) {
			if(parent) { return parent->getValue(name); }
			else { return nullptr; }
		} else {
			return variables[name];
		}
	}
	
	Scope* getRootScope() {
		static Scope* r = new Scope(nullptr);
		return r;
	}
	
}