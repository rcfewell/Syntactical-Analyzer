#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "lex.h"
#include "syn.h"
#include "SetLimits.h"

using namespace std;

int main( int argc, char * argv[] )
{

	if( argc < 2 )
	{
		cout << "format: proj2 <filename>:\n";
		exit( 1 );
	}

	SetLimits ();
	Syn Syn( argv[1] );
	Syn.program();


	return 0;
}

