#include "Lexer.h"

Lexer::Lexer(const QString& block)
{
    begin = block.begin();
    it = begin;
    forward = it + 1;
}


inline void Lexer::setScanningBlock(const QString& b)
{
    begin = b.constBegin();
    it = begin;
    forward = it + 1;
}

void Lexer::addKeyword(QString&& kw)
{
    keywords.append(kw);
}

QString makeString(const QString::const_iterator& b,
                   const QString::const_iterator& e)
{
    QString res;
    for(auto i = b; i != e; ++i)
        res.append(*i);
    return res;
}

void Lexer::skipWhiteSpaces()
{
    while(it->isSpace()) ++it;
    forward = it + 1;
}

Token Lexer::scanNumber()
{
    Token res;
    while(forward->isDigit()) ++forward;
    res.stype = ShortType::num;
    return res;
}

Token Lexer::scanIdOrKeyword()
{
    Token res;
    while(forward->isLetterOrNumber() || forward->isSymbol()) ++forward;
    if (keywords.contains(makeString(it, forward)))
        res.stype = ShortType::keyword;
    else
        res.stype = ShortType::id;
    return res;
}


Token Lexer::scan()
{
    Token scanningToken;
    skipWhiteSpaces();

    if (it->isNull())
        return scanningToken;
    else if (it->isDigit())
        scanningToken = scanNumber();
    else if (it->isLetter())
        scanningToken = scanIdOrKeyword();
    else
        scanningToken.stype = ShortType::unknown;

    scanningToken.posStartOfWord = it - begin;
    scanningToken.posEndOfWord   = forward - begin;

    it = forward;
    forward = it + 1;
    return scanningToken;
}
