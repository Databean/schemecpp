#ifndef PSCHEME_SCRIPT_OBJECT_H
#define PSCHEME_SCRIPT_OBJECT_H

#include <string>
#include "Scope.h"

namespace pscheme {
	
	class Scope;
	
	enum Type {
		TYPE_NUMBER, TYPE_PAIR, TYPE_EMPTY_LIST, TYPE_SYMBOL, TYPE_FUNCTION, TYPE_MACRO, TYPE_IDENTIFIER, TYPE_BOOL, TYPE_VOID
	};
	
	class Object {
	public:
		Object() {}
		virtual ~Object() {}
		
		virtual Object* evaluate(Scope* s)=0;
		virtual Type getType()=0;
		virtual std::string toString()=0;
	};
	
	class Pair : public Object {
	public:
		Pair(Object* left,Object* right);
		virtual ~Pair();
		
		virtual Object* getLeft() { return left; }
		virtual Object* getRight() { return right; }
		
		virtual Pair* getEvaluated(Scope* s);
		
		virtual Object* evaluate(Scope* s);
		virtual Type getType() { return TYPE_PAIR; }
		virtual std::string toString();
		
		//virtual Object* nth();
	private:
		Object* left;
		Object* right;
	};
	
	class EmptyList : public Object {
	public:
		EmptyList() {}
		virtual ~EmptyList() {}
		
		virtual EmptyList* evaluate(Scope* s) { return this; }
		virtual Type getType() { return TYPE_EMPTY_LIST; }
		virtual std::string toString() { return "()"; }
	};
	
	class Bool : public Object {
	public:
		Bool(bool _b) { b = _b; }
		virtual ~Bool() {}
		
		virtual bool getValue() { return b; }
		
		virtual Bool* evaluate(Scope* s) { return this; }
		virtual Type getType() { return TYPE_BOOL; }
		virtual std::string toString() { return std::string("#")+(b?std::string("t"):std::string("f")); }
	private:
		bool b;
	};
	
	class Void : public Object {
	public:
		Void() {}
		virtual ~Void() {}
		
		virtual Void* evaluate(Scope* s) { return this; }
		virtual Type getType() { return TYPE_VOID; }
		virtual std::string toString() { return ""; }
	};
	
	class Symbol : public Object {
	public:
		Symbol(Object* _sym) { sym = _sym; }
		virtual ~Symbol() { delete sym; }
		
		virtual Object* getSym() { return sym; }
		
		virtual Object* evaluate(Scope* s) { return sym; }
		virtual Type getType() { return TYPE_SYMBOL; }
		virtual std::string toString() { return std::string("'")+sym->toString(); }
	private:
		Object* sym;
	};
	
	class Identifier : public Object {
	public:
		Identifier(std::string* _name) { name = *_name, delete _name; }
		Identifier(std::string _name) { name = _name; }
		virtual ~Identifier() {}
		
		std::string toString() { return name; }
		std::string getName() { return name; }
		
		virtual Object* evaluate(Scope* s);
		virtual Type getType() { return TYPE_IDENTIFIER; }
	private:
		std::string name;
	};
	
	class Function : public Object {
	public:
		Function() {}
		virtual ~Function() {}
		
		virtual Object* evaluate(Scope* s) { return this; }
		virtual Type getType() { return TYPE_FUNCTION; }
		virtual std::string toString() { return "function"; }
		
		virtual Object* call(Object* params,Scope* s/* scope only used by macros */)=0;
	};
	
	class Macro : public Function {
	public:
		Macro() {}
		virtual ~Macro() {}
		
		virtual Type getType() { return TYPE_MACRO; }
	};
	
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
	
}

#endif