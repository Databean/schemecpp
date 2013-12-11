#include <Object.h>
#include "Preprocessor.h"

namespace pscheme {

	/**
	* Called as (if condition then_expr else_expr).
	* condition is checked, and based on the result of that, either
	* the then_expr or the else_expr is evaluated and returned.
	* This has to be a macro because only one of the then_expr and else_expr
	* expressions should be invoked.
	*/
	class IfFunction : public Macro {
	public:
		IfFunction() {}
		virtual ~IfFunction() {}
		virtual Object* call(Object* _params,Scope* s) {
			if(_params->getType()!=TYPE_PAIR) {
				throw "if requires arguments";
			}
			Pair* params = reinterpret_cast<Pair*>(_params);
			Object* condition = params->getLeft();
			Object* _thenGroup = params->getRight();
			if(_thenGroup->getType()!=TYPE_PAIR) {
				throw "if requires to be passed 3 parameters";
			}
			Pair* thenGroup = reinterpret_cast<Pair*>(_thenGroup);
			Object* then = thenGroup->getLeft();
			Object* _elseGroup = thenGroup->getRight();
			if(_elseGroup->getType()!=TYPE_PAIR) {
				throw "if requires to be passed a proper list";
			}
			Pair* elseGroup = reinterpret_cast<Pair*>(_elseGroup);
			Object* els = elseGroup->getLeft();
			if(elseGroup->getRight()->getType()!=TYPE_EMPTY_LIST) {
				throw "if requires to be passed a proper list of 3 parameters";
			}
			Object* _conditionResult = condition->evaluate(s);
			if(_conditionResult->getType()!=TYPE_BOOL) {
				throw "if condition return type has to be a bool";
			}
			Bool* conditionResult = reinterpret_cast<Bool*>(_conditionResult);
			if(conditionResult->getValue()) {
				return then->evaluate(s);
			} else {
				return els->evaluate(s);
			}
		}
	};
	run(getRootScope()->defineValue("if",new IfFunction());)
}
