#include "Object.h"
#include "Number.h"
#include "Preprocessor.h"

using namespace std;
using namespace pscheme;

class PlusFunction : public Function {
public:
	PlusFunction() {}
	virtual ~PlusFunction() {}
	virtual Object* call(Object* _params,Scope* _s) {
		if(_params->getType()==TYPE_EMPTY_LIST) {
			return new Number(0);
		} else if(_params->getType() != TYPE_PAIR) {
			throw "wtf...? parameters passed to function are not a pair";
		}
		Pair* params = reinterpret_cast<Pair*>(_params);
		if(params->getLeft()->getType()!=TYPE_NUMBER) {
			throw "left side of + is not a number";
		}
		Number* left = reinterpret_cast<Number*>(params->getLeft());
		if(params->getRight()->getType()==TYPE_EMPTY_LIST) {
			return left;
		} else if(params->getRight()->getType()==TYPE_PAIR) {
			Number* right = NULL;
			right = reinterpret_cast<Number*>(call(reinterpret_cast<Pair*>(params->getRight()),_s));
			return (*left)+right;
		} else {
			throw "right side of + not a list or empty pair";
		}
		return NULL;
	}
};
run(getRootScope()->defineValue("+",new PlusFunction());)

class MinusFunction : public Function {
public:
	MinusFunction() {
		plus = PlusFunction();
	}
	virtual ~MinusFunction() { }
	virtual Object* call(Object* _params,Scope* _s) {
		if(_params->getType()==TYPE_EMPTY_LIST) {
			throw "minus requires at least one parameter";
		} else if(_params->getType()!=TYPE_PAIR) {
			throw "parameters passed to minus not a list...?";
		}
		Pair* params = reinterpret_cast<Pair*>(_params);
		if(params->getLeft()->getType()!=TYPE_NUMBER) {
			throw "left side of - not a number";
		}
		Number* left = reinterpret_cast<Number*>(params->getLeft());
		if(params->getRight()->getType()==TYPE_EMPTY_LIST) {
			if(left->isExact()) {
				mpq_class res = -1 * left->getExact();
				return new Number(res);
			} else {
				mpf_class res = -1 * left->getInexact();
				return new Number(res);
			}
		} else if(params->getRight()->getType()==TYPE_PAIR) {
			Number* right = NULL;
			right = reinterpret_cast<Number*>(plus.call(reinterpret_cast<Pair*>(params->getRight()),_s));
			return (*left)-right;
		} else {
			throw "right side of + not a list or empty pair";
		}
	}
private:
	PlusFunction plus;
};
run(getRootScope()->defineValue("-",new MinusFunction());)

class MultiplyFunction : public Function {
public:
	MultiplyFunction() {}
	virtual ~MultiplyFunction() {}
	virtual Object* call(Object* _params, Scope* _s) {
		if(_params->getType()==TYPE_EMPTY_LIST) {
			return new Number(1);
		} else if(_params->getType() != TYPE_PAIR) {
			throw "wtf...? parameters passed to function are not a pair";
		}
		Pair* params = reinterpret_cast<Pair*>(_params);
		if(params->getLeft()->getType()!=TYPE_NUMBER) {
			throw "left side of * is not a number";
		}
		Number* left = reinterpret_cast<Number*>(params->getLeft());
		if(params->getRight()->getType()==TYPE_EMPTY_LIST) {
			return left;
		} else if(params->getRight()->getType()==TYPE_PAIR) {
			Number* right = NULL;
			right = reinterpret_cast<Number*>(call(reinterpret_cast<Pair*>(params->getRight()),_s));
			return (*left)*right;
		} else {
			throw "right side of * not a list or empty pair";
		}
		return NULL;
	}
};
run(getRootScope()->defineValue("*",new MultiplyFunction());)

class DivideFunction : public Function {
public:
	DivideFunction() {
		mult = MultiplyFunction();
	}
	virtual ~DivideFunction() {}
	virtual Object* call(Object* _params,Scope* s) {
		if(_params->getType()==TYPE_EMPTY_LIST) {
			throw "/ requires at least one parameter";
		} else if(_params->getType()!=TYPE_PAIR) {
			throw "parameters passed to / not a list...?";
		}
		Pair* params = reinterpret_cast<Pair*>(_params);
		if(params->getLeft()->getType()!=TYPE_NUMBER) {
			throw "left side of / not a number";
		}
		Number* left = reinterpret_cast<Number*>(params->getLeft());
		if(params->getRight()->getType()==TYPE_EMPTY_LIST) {
			if(left->isExact()) {
				return new Number(mpq_class(1/left->getExact()));
			} else {
				return new Number(mpf_class(1/left->getInexact()));
			}
		} else if(params->getRight()->getType()==TYPE_PAIR) {
			Object* _right = mult.call(params->getRight(),s);
			if(_right->getType()!=TYPE_NUMBER) {
				throw "* gave incorrect intermediate result";
			}
			Number* right = reinterpret_cast<Number*>(_right);
			return (*left)/right;
		} else {
			throw "params to / not a proper list";
		}
	}
private:
	MultiplyFunction mult;
};
run(getRootScope()->defineValue("/",new DivideFunction());)