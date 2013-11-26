#include "Object.h"
#include "gmpxx.h"

namespace pscheme {
	
	class Number : public Object {
	public:
		Number(int i);
		Number(mpq_class);
		Number(mpf_class);
		virtual ~Number();
		
		virtual Number* evaluate(Scope* s);
		virtual Type getType() { return TYPE_NUMBER; }
		virtual std::string toString();
		virtual bool isExact();
		virtual mpq_class getExact();
		virtual mpf_class getInexact();
		
		virtual Number* operator+(Number* other);
		virtual Number* operator-(Number* other);
		virtual Number* operator*(Number* other);
		virtual Number* operator/(Number* other);
		virtual Bool* operator<(Number* other);
		virtual Bool* operator<=(Number* other);
		virtual Bool* operator>=(Number* other);
		virtual Bool* operator>(Number* other);
		
	private:
		bool isexact;
		mpq_class exact;
		mpf_class inexact;
	};
	
}