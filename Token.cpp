#include "Token.h"

Token::Token(ApraamTokType t, ShortType st)
    : stype(st), ttype(t)
{}

Token::Token(ShortType t)
    : stype(t)
{
}

