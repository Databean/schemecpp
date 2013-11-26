#include "Number.h"
#include <sstream>

#define OPERATOR(O) \
	Number* Number::operator O (Number* other) { \
		if(isexact && other->isexact) { \
			mpq_class ret = exact O other->exact; \
			return new Number(ret); \
		} else if(isexact && !(other->isexact)) { \
			mpf_class ret = exact O other->inexact; \
			return new Number(ret); \
		} else if((!isexact) && other->isexact) { \
			mpf_class ret = inexact O other->exact; \
			return new Number(ret); \
		} else { \
			mpf_class ret = inexact O other->inexact; \
			return new Number(ret); \
		} \
	}

#define COMP_OPERATOR(O) \
	Bool* Number::operator O (Number* other) { \
	if(isexact && other->isexact) { \
		bool ret = exact O other->exact; \
		return new Bool(ret); \
	} else if(isexact && !(other->isexact)) { \
		bool ret = exact O other->inexact; \
		return new Bool(ret); \
	} else if((!isexact) && other->isexact) { \
		bool ret = inexact O other->exact; \
		return new Bool(ret); \
	} else { \
		bool ret = inexact O other->inexact; \
		return new Bool(ret); \
	} \
}

using namespace std;

namespace pscheme {
	
	Number::Number(int i) { 
		exact = mpq_class(i);
		isexact = true;
	}
	Number::Number(mpq_class m) {
		isexact = true;
		exact = m;
	}
	Number::Number(mpf_class i) {
		isexact = false;
		inexact = i;
	}
	Number::~Number() { }
	Number* Number::evaluate(Scope* s) { 
		return this; 
	}
	string Number::toString() {
		stringstream s;
		if(isexact) {
			s << exact;
		} else {
			s << inexact;
		}
		return s.str();
	}
	mpq_class Number::getExact() {
		return exact;
	}
	mpf_class Number::getInexact() {
		return inexact;
	}
	bool Number::isExact() { 
		return isexact;
	}
	OPERATOR(+)
	OPERATOR(-)
	OPERATOR(*)
	OPERATOR(/)
	COMP_OPERATOR(<)
	COMP_OPERATOR(>)
	COMP_OPERATOR(<=)
	COMP_OPERATOR(>=)
}