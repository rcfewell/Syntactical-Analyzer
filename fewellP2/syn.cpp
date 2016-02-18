#include "syn.h"
#include <cstdlib>


Syn::~Syn ()
{

  cout << errors << " errors found in input file" << endl;
  //output << errors << " errors found in input file" << endl;
}


void Syn::program()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <program>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == INTTYPE || ct == DBLTYPE )
    decl ();
  else
    stmt ();

  if( ct == SEMI )
    {
      ct = lex.get_token ();
      debug << "SHOULD GET SEMI IN <program>" << endl;
    }
  else
  {
    errors++;
    lex.error_message( "; expected." );
  }
  
  more_stmts ();

  debug << "ending <program>" << endl;
  lex.output << errors << " errors found in input file" << endl;

}

void Syn::more_stmts ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <more_stmts>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == INTTYPE || ct == DBLTYPE )
    decl ();
  else  
    stmt ();

  debug << "SHOULD SEE SEMI IN <more_stmts>" << endl;
  if( ct == SEMI )
  {
    
    ct = lex.get_token ();
    //more_stmts ();
  }
  else
  {
    errors++;
    lex.error_message( "; expected" );
  }

  more_stmts ();

  debug << "Ending <more_stmts>" << endl;

}

void Syn::stmt()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <stmt>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  term();
  stmt_tail();

  debug << "Ending <stmt>" << endl;

}

void Syn::decl ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <decl>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;
  
  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  ntype();

  if( ct == IDENT )
  {
    ct = lex.get_token ();
    decl_tail ();
    more_decls ();
  }
  else
  {
    errors++;
    lex.error_message( " Identifier expected" );
  }

  debug << "Ending <decl>" << endl;

}

void Syn::ntype ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <ntype>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == INTTYPE || ct == DBLTYPE )
    ct = lex.get_token ();
  else
  {
    errors++;
    lex.error_message( "Int or double expected" );
  }

  debug << "Ending <ntype>" << endl;

}

void Syn::decl_tail ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <decl_tail>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == ASSIGN )
  {
    ct = lex.get_token();
    stmt ();
  }
  else
  {
    errors++;
    lex.error_message( "= expected" );
  }

  debug << "Ending <decl_tail>" << endl;

}

void Syn::more_decls ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <more_decls>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == COMMA )
  { 
    ct = lex.get_token ();

    if( ct == IDENT )
    {
      ct = lex.get_token ();
      decl_tail ();
      more_decls ();
    }
    else
    {
      errors++;
      lex.error_message( "Identifier expected" );
    }
  }
  //else
  //{
  //errors++;
  //lex.error_message( ", expected" );
  //}

  debug << "Ending <more_decls>" << endl;

}

void Syn::term ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <term>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == LPAREN )
  {
    ct = lex.get_token ();
    stmt ();

    if( ct == RPAREN )
      ct = lex.get_token ();
    else
    {
      errors++;
      lex.error_message( ") expected." );
    }
  }

  else
  {
    pre ();
    var ();
    post ();
  }

  debug << "Ending <term>" << endl;

}


void Syn::pre ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <pre>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == PLUS || ct == MINUS || ct == NOT || ct == TILDA || ct == PLUSPLUS || ct == MINUSMINUS ) 
  {
    uoppre ();
    pre ();
  }
  //else {}

  debug << "Ending <pre>" << endl;

}

void Syn::uoppre ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <uoppre>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == PLUS || ct == MINUS || ct == NOT || ct == TILDA || ct == PLUSPLUS || ct == MINUSMINUS )
    ct = lex.get_token();
  else
  {
    errors++;
    lex.error_message( "Unary operator expected" );
  }

  debug << "Ending <uoppre>" << endl;

}

void Syn::var ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <var>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();
  
  if( ct == IDENT || ct == NUMLIT )
    ct = lex.get_token (); 
  else
  {
    errors++;
    lex.error_message( "Identifier or numeric literal expected" );
  }

  debug << "Ending <var>" << endl;

}

void Syn::post ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <post>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == PLUSPLUS || ct == MINUSMINUS )
    ct = lex.get_token ();
  
  // else 
  // {}

  debug << "Ending <post>" << endl;

}

void Syn::stmt_tail ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <stmt_tail>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == PLUS || ct == MINUS || ct == MULT || ct == DIV || ct == MOD || 
      ct == AND || ct == OR || ct == XOR || ct == ASSIGN || ct == LT || 
      ct == GT || ct == SHIFTL || ct == SHIFTR || ct == PLUSEQ || ct == MINUSEQ ||
      ct == MULTEQ || ct == DIVEQ || ct == MODEQ || ct == NOTEQ || ct == LOGAND ||
      ct == ANDEQ || ct == LOGOR || ct == OREQ || ct == XOREQ || ct == EQUALTO ||
      ct == SHIFTLEQ || ct == LTE || ct == SHIFTREQ || ct == GTE || ct == COMMA ||
      ct == EXP || ct == EXPEQ )
  {
    binop ();
    stmt ();
  }

  else if( ct == QUEST )
  {
    ct = lex.get_token ();
    stmt ();

    if( ct == COLON )
    {
      ct = lex.get_token ();
      stmt ();
    }
    else
    {
      errors++;
      lex.error_message( ": expected" );
    }
  }

  // else
  // {}
  
  debug << "Ending <stmt_tail>" << endl;

}

void Syn::binop ()
{
  string type = lex.get_token_name( ct );
  string lexeme = lex.get_lexeme();
  debug << "Starting <binop>" << endl;
  debug << "token: " << type << " Lexeme: " << lex.get_lexeme () << endl;

  if( ct == EOFT )
    return;
  if( ct == ERROR )
    ct = lex.get_token ();

  if( ct == PLUS || ct == MINUS || ct == MULT || ct == DIV || ct == MOD || 
      ct == AND || ct == OR || ct == XOR || ct == ASSIGN || ct == LT || 
      ct == GT || ct == SHIFTL || ct == SHIFTR || ct == PLUSEQ || ct == MINUSEQ ||
      ct == MULTEQ || ct == DIVEQ || ct == MODEQ || ct == NOTEQ || ct == LOGAND ||
      ct == ANDEQ || ct == LOGOR || ct == OREQ || ct == XOREQ || ct == EQUALTO ||
      ct == SHIFTLEQ || ct == LTE || ct == SHIFTREQ || ct == GTE || ct == COMMA ||
      ct == EXP || ct == EXPEQ )
    
    ct = lex.get_token ();
  else
  {
    errors++;
    lex.error_message( "Binary operator expected" );
  }

  debug << "Ending <binop>" << endl;

}




