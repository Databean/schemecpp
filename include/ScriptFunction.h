#ifndef SCRIPT_FUNCTION_H
#define SCRIPT_FUNCTION_H

#include "Object.h"

namespace pscheme {
	class ScriptFunction : public Function {
	public:
		ScriptFunction(Pair* parameters,Pair* expressions,Scope* s);
		virtual ~ScriptFunction();
		
		virtual Object* call(Object* params,Scope* s/* scope only used by macros */);
		
		virtual Type getType() { return TYPE_FUNCTION; }
	private:
		virtual Object* run(Scope* s);
		
		Pair* parameters;
		Pair* expressions;
		Scope* scope;
	};
};

#endif