#ifndef CPP_FUNCTION_H
#define CPP_FUNCTION_H

#include "Object.h"

#include <tuple>

// From Stack Overflow
// http://stackoverflow.com/a/10766422/1290655
namespace detail
{
	template <typename F, typename Tuple, bool Done, int Total, int... N>
	struct call_impl
	{
		static pscheme::Object* call(F f, Tuple && t)
		{
			return call_impl<F, Tuple, Total == 1 + sizeof...(N), Total, N..., sizeof...(N)>::call(f, std::forward<Tuple>(t));
		}
	};
	
	template <typename F, typename Tuple, int Total, int... N>
	struct call_impl<F, Tuple, true, Total, N...>
	{
		static pscheme::Object* call(F f, Tuple && t)
		{
			return f(std::get<N>(std::forward<Tuple>(t))...);
		}
	};
}

// user invokes this
template <typename F, typename Tuple>
pscheme::Object* fn_call(F f, Tuple && t)
{
	typedef typename std::decay<Tuple>::type ttype;
	return detail::call_impl<F, Tuple, 0 == std::tuple_size<ttype>::value, std::tuple_size<ttype>::value>::call(f, std::forward<Tuple>(t));
}
// End From Stack Overflow

namespace pscheme {
	
	template<class T>
	std::tuple<T> parametersToTuple(Object* input) {
		if(input->getType() == TYPE_EMPTY_LIST) {
			throw "error: not enough items in this list for the function.";
		} else if(input->getType() == TYPE_PAIR) {
			Pair* pair = reinterpret_cast<Pair*>(input);
			if(pair->getRight()->getType() == TYPE_EMPTY_LIST) {
				if(dynamic_cast<T>(pair->getLeft())) {
					return std::make_tuple(reinterpret_cast<T>(pair->getLeft()));
				} else {
					throw "error: invalid type";
				}
			}
		}
		throw "error: too many items in this list for the function.";
	}
	/*
	std::tuple<> parametersToTuple(Object* input) {
		if(input->getType() == TYPE_EMPTY_LIST) {
			return std::make_tuple();
		} else {
			throw "error: not enough items in this list for the function.";
		}
	}*/
	
	template<typename T, typename S, typename... Args>
	std::tuple<T, S, Args...> parametersToTuple(Object* input) {
		if(input->getType() == TYPE_EMPTY_LIST) {
			throw "error: not enough items in this list for the function.";
		} else if(input->getType() == TYPE_PAIR) {
			Pair* pair = reinterpret_cast<Pair*>(input);
			if(dynamic_cast<T>(pair->getLeft())) {
				return std::tuple_cat(std::make_tuple(reinterpret_cast<T>(pair->getLeft())), parametersToTuple<S, Args...>(pair->getRight()));
			} else {
				throw "error: invalid type";
			}
		} else {
			throw "error: unknown parameter type";
		}
	}
	
	template<typename... Args>
	class CPPFunction : public Function {
	private:
		typedef Object* (*Fn)(Args...);
		Fn function;
	public:
		CPPFunction(Fn function) : function(function) {}
		virtual ~CPPFunction() {}
		
		virtual Object* call(Object* params, Scope* s /*scope only used by macros */) {
			std::tuple<Args...> argsTuple = parametersToTuple<Args...>(params);
			return fn_call(function, argsTuple);
		}
	};
	
	template<typename... Args>
	Function* wrapFn(Object* (*function)(Args...)) {
		return new CPPFunction<Args...>(function);
	}
	
	template<class Fn>
	class CPPFunctionRaw : public Function {
	private:
		Fn function;
	public:
		CPPFunctionRaw(Fn function) : function(function) {}
		virtual ~CPPFunctionRaw() {}
		
		virtual Object* call(Object* params, Scope* s) {
			return function(params, s);
		}
	};
	
	template<class Fn>
	Function* wrapFnRaw(Fn function) {
		return new CPPFunctionRaw<Fn>(function);
	}
}

#endif