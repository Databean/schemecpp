#include "y.tab.h"
#include "scanner.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "Object.h"

int yyparse();
int yylex();

using std::cout;
using std::endl;
using std::fstream;
using std::stringbuf;
using std::string;

using pscheme::Pair;
using pscheme::Object;
using pscheme::Scope;
using pscheme::getRootScope;

using pscheme::TYPE_VOID;
using pscheme::TYPE_PAIR;

Pair* root;

int main(int argc,char** args) {
	string filename;
	if(argc > 1) {
		filename = args[1];
	} else {
		cout << ">>parsing test.scm, no filename given" << endl;
		filename = "test.scm";
	}
	
	cout << ">>this is the file" << endl;
	
	fstream file(filename.c_str(), fstream::in);
	stringbuf text;
	file >> &text;
	file.close();
	
	cout << text.str() << endl;
	
	cout << ">>running parser, lexer" << endl;
	
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
	} catch(string s) {
		cout << s << endl;
	} catch(const char* c) {
		cout << c << endl;
	}
	
	cleanBufferState();
	
	
	cout << ">>done" <<endl;
}
