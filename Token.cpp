#include "Token.h"

Token::Token(ApraamTokType t, ShortTokType st)
{
    ttype = t;
    stype = st;
}

Token::Token(ShortTokType t)
{
    stype = t;
}

