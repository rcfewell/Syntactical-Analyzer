#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "lex.h"

class Syn 
{
public:
	Syn ( char * filename ) : lex( filename )
	{
		ct = lex.get_token();
		errors = 0; 
		string outputFile = filename;
		outputFile = outputFile.substr(0, outputFile.find('.') );
		// output.open( ( outputFile + ".lst").c_str() );
		debug.open( "debug.dbg" );
		// output.open( "output.lst", ios_base::app );
		
	}
	~Syn ();
	void program();
	


 private:
	token_type ct;
	int errors;
	Lex lex;
	ofstream debug;
	ofstream output;

	void more_stmts();
	void stmt();
	void decl();
	void ntype ();
	void decl_tail ();
	void more_decls ();
	void term ();
	void pre ();
	void uoppre();
	void var();
	void post();
	void stmt_tail();
	void binop();
	
	
	
	
	


};

#endif
