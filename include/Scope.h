#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <string>
#include "Object.h"

namespace pscheme {
	
	class Object;
	
	class Scope {
	public:
		Scope(Scope& parent);
		Scope(Scope* parent);
		virtual ~Scope();
		
		virtual Object* getValue(std::string var);
		virtual void defineValue(std::string var,Object* value);
		virtual void setValue(std::string var,Object* value);
		
	private:
		std::map<std::string,Object*> variables;
		Scope* parent;
	};
	
	Scope* getRootScope();
	
}

#endif