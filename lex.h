#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>

using namespace std;

enum token_type {ERROR, IDENT, INTTYPE, DBLTYPE, NUMLIT, PLUS, MINUS, MULT,
                DIV, MOD, EXP, NOT, AND, OR, XOR, ASSIGN, LT, GT, SHIFTL,
                SHIFTR, PLUSPLUS, PLUSEQ, MINUSMINUS, MINUSEQ, MULTEQ,
                DIVEQ, MODEQ, EXPEQ, NOTEQ, LOGAND, ANDEQ, LOGOR, OREQ,
                XOREQ, EQUALTO, SHIFTLEQ, LTE, SHIFTREQ, GTE, TILDA, RPAREN,
                LPAREN, SEMI, QUEST, COLON, COMMA, EOFT};


class Lex
{
 public:
  Lex( char * filename );
  ~Lex ();
  token_type get_token ();
  string get_token_name ( token_type t ) const;
  string get_lexeme () const;
  void error_message( string msg );
  ofstream output;

 private:
  ifstream input;
  string line;
  int linenum;
  int pos;
  string lexeme;
  int errors;
  
};

#endif
