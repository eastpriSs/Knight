#include "Parser.h"

Parser::Parser(Lexer* l)
{
    lex = l;
}

Token Parser::parse()
{
    return lex->scan();
}
