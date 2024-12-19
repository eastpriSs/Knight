#include "Parser.h"

Parser::Parser(Lexer* l)
{
    lex = l;
}

Parser::Parser(Lexer* l, Logger* lg)
{
    lex = l;
    logger = lg;
}

Token Parser::parse()
{
    return lex->scan();
}
