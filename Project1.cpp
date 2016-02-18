#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "lex.h"
#include "syn.h"
#include "SetLimits.h"

int main( int argc, char * argv[] )
{
	if( argc < 2 )
	{
		printf( "format: proj1 <filename>\n" );
		exit( 1 );
	}

	SetLimits();
	Lex lex( argv[1] );
	token_type t;

	while( ( t = lex.get_token() ) != EOFT )
		cout << '\t' << left << setw( 10 ) << lex.get_token_name( t ) << '\t' << lex.get_lexeme () << endl << right;
	return 0;
}
