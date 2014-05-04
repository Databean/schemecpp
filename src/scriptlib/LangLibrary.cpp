#include "Object.h"
#include "Preprocessor.h"
#include <iostream>

using std::string;

namespace pscheme {

	class LambdaFunction : public Macro {
	public:
		LambdaFunction() {}
		virtual ~LambdaFunction() {}
		virtual Object* call(Object* _params,Scope* s) {
			if(_params->getType()!=TYPE_PAIR) {
				throw "lambda requires arguments";
			}
			Pair* params = static_cast<Pair*>(_params);
			if(params->getLeft()->getType()!=TYPE_PAIR) {
				throw "lambda expects an identifier list as its first argument";
			}
			Pair* funcArguments = static_cast<Pair*>(params->getLeft());
			if(params->getRight()->getType()!=TYPE_PAIR) {
				throw "lambda expects a list of commands to run";
			}
			Pair* funcCommands = static_cast<Pair*>(params->getRight());
			return new ScriptFunction(funcArguments,funcCommands,s);
		}
	};
	run(getRootScope()->defineValue("lambda",new LambdaFunction());)

	class DefineFunction : public Macro {
	public:
		DefineFunction() {}
		virtual ~DefineFunction() {}
		virtual Object* call(Object* _params,Scope* s) {
			if(_params->getType()!=TYPE_PAIR) {
				throw "lambda requires arguments";
			} 
			Pair* params = static_cast<Pair*>(_params);
			if(params->getLeft()->getType()==TYPE_PAIR) {
				Pair* funcInfo = static_cast<Pair*>(params->getLeft());
				if(funcInfo->getLeft()->getType()!=TYPE_IDENTIFIER) {
					throw "func define expects func name identifier in first group";
				}
				Identifier* nameObj = static_cast<Identifier*>(funcInfo->getLeft());
				string name = nameObj->getName();
				Pair* r = nullptr;
				if(funcInfo->getRight()->getType()==TYPE_EMPTY_LIST) {
					r = new Pair(nullptr,new EmptyList());
				} else if(funcInfo->getRight()->getType()==TYPE_PAIR) {
					r = static_cast<Pair*>(funcInfo->getRight());
				} else {
					throw "right side of define function params should be list";
				}
				if(params->getRight()->getType()!=TYPE_PAIR) {
					throw "right side of define should be a list of commands";
				}
				ScriptFunction* ret = new ScriptFunction(r,static_cast<Pair*>(params->getRight()),s);
				s->defineValue(name,ret);
				return new Void();
			} else if(params->getLeft()->getType()==TYPE_IDENTIFIER) {
				Identifier* id = static_cast<Identifier*>(params->getLeft());
				if(params->getRight()->getType()!=TYPE_PAIR) {
					throw "define expected more parameters";
				}
				Pair* right = static_cast<Pair*>(params->getRight());
				if(right->getRight()->getType()!=TYPE_EMPTY_LIST) {
					throw "define received too many parameters";
				}
				s->defineValue(id->getName(),right->getLeft()->evaluate(s));
				return new Void();
			}
			throw "define passed invalid parameters";
		}
	};
	run(getRootScope()->defineValue("define",new DefineFunction());)

	class SetFunction : public Macro {
	public:
		SetFunction() {}
		virtual ~SetFunction() {}
		virtual Object* call(Object* _params, Scope* s) {
			if(_params->getType()!=TYPE_PAIR) {
				throw "lambda requires arguments";
			}
			Pair* params = static_cast<Pair*>(_params);
			if(params->getLeft()->getType()!=TYPE_IDENTIFIER) {
				throw "error: set! first parameter should be an identifier";
			}
			Identifier* id = static_cast<Identifier*>(params->getLeft());
			if(params->getRight()->getType()!=TYPE_PAIR) {
				throw "error: set! needs more than one parameter";
			}
			Pair* right = static_cast<Pair*>(params->getRight());
			if(right->getRight()->getType()!=TYPE_EMPTY_LIST) {
				throw "set! received too many parameters";
			}
			s->setValue(id->getName(),right->getLeft()->evaluate(s));
			return new Void();
		}
	};
	run(getRootScope()->defineValue("set!",new SetFunction());)
}
