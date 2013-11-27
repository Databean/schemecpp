#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#define VARIABLE __LINE__
#define PASTER(x,y) x ## _ ## y
#define EVALUATOR(x,y)  PASTER(x,y)
#define NAME(fun) EVALUATOR(fun, VARIABLE)

#define VARIABLE2 __LINE__
#define PASTER2(x,y) x ## _ ## y ## _instance
#define EVALUATOR2(x,y)  PASTER2(x,y)
#define NAME2(fun) EVALUATOR2(fun, VARIABLE)

#define run(code) \
class NAME(a) { \
public: \
	NAME(a) () { \
	code \
	} \
}; \
NAME(a) NAME2(b);

#define schemeFn(fn) \
class secretclass_##fn { \
public: \
	secretclass_##fn() { \
		getRootScope()->defineValue(#fn,wrapFn(fn));\
	} \
}; \
secretclass_##fn secretinstance_##fn;

#define schemeNameFn(name, fn) \
class secretclass_##fn { \
public: \
	secretclass_##fn() { \
		getRootScope()->defineValue(name,wrapFn(fn));\
	} \
}; \
secretclass_##fn secretinstance_##fn;

#endif