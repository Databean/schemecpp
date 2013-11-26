#include "Object.h"
#include "Preprocessor.h"
#include "Number.h"

/**
 * Preprocessor macro to combine the similar code for <, >, <=, and >=.
 */
#define NUMERIC_COMPARISON_OPERATOR(NAME,O) \
class NAME : public Function { \
public: \
	NAME () {} \
	virtual ~ NAME () {} \
	virtual Object* call(Object* _params,Scope* _s) { \
		if(_params->getType() != TYPE_PAIR) { \
			throw "parameters passed are not a pair"; \
		} \
		Pair* params = reinterpret_cast<Pair*>(_params); \
		if(params->getLeft()->getType()!=TYPE_NUMBER) { \
			throw "left side is not a number"; \
		} \
		Number* left = reinterpret_cast<Number*>(params->getLeft()); \
		if(params->getRight()->getType()==TYPE_EMPTY_LIST) { \
			throw "expects two parameters"; \
		} else if(params->getRight()->getType()==TYPE_PAIR) { \
			Number* right = NULL; \
			right = reinterpret_cast<Number*>(reinterpret_cast<Pair*>(params->getRight())->getLeft()); \
			return (*left) O right; \
		} else { \
			throw "right side not a list or empty pair"; \
		} \
		return NULL; \
	} \
}; \
run(getRootScope()->defineValue(#O,new NAME ());)

using namespace std;
using namespace pscheme;

NUMERIC_COMPARISON_OPERATOR(LessThan,<)
NUMERIC_COMPARISON_OPERATOR(GreaterThan,>)
NUMERIC_COMPARISON_OPERATOR(LessThanOrEqualTo,<=)
NUMERIC_COMPARISON_OPERATOR(GreaterThanOrEqualTo,>=)