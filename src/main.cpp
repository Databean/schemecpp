#include "y.tab.h"
#include "scanner.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "Object.h"

int yyparse();
int yylex();

using namespace std;
using namespace pscheme;

Pair* root;

int main(int i,char** args) {
	std::string filename;
	if(!args) {
		filename = args[0];
	} else {
		std::cout << ">>parsing test.scm, no filename given" << std::endl;
		filename = "test.scm";
	}
	
	std::cout << ">>this is the file" << std::endl;
	
	std::fstream file("test.scm", std::fstream::in);
	std::stringbuf text;
	file >> &text;
	file.close();
	
	std::cout << text.str() << std::endl;
	
	std::cout << ">>running parser, lexer" << std::endl;
	
	chooseStr(text.str().c_str());
	
	yyparse();
	Scope* s = new Scope(getRootScope());
	cout << ">>running file" << endl;
	try {
		Pair* p = root;
		while(true) {
			cout << ">>running command" << endl;
			Object* ret = p->getLeft()->evaluate(s);
			if(ret->getType()!=TYPE_VOID) {
				cout << ret->toString() << endl;
			} 
			if(p->getRight()->getType()==TYPE_PAIR) {
				p = reinterpret_cast<Pair*>(p->getRight());
			} else {
				break;
			}
		}
	} catch(std::string s) {
		cout << s << endl;
	} catch(const char* c) {
		cout << c << endl;
	}
	
	cleanBufferState();
	
	
	std::cout << ">>done" <<std::endl;
}