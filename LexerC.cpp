#include "LexerC.h"

LexerC::LexerC()
    : Lexer("")
{
    keywords.append({
    "_Alignas", "_Alignof", "_Atomic",
    "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn",
    "_Static_assert", "_Thread_local",
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "inline", "int", "long",
    "register", "restrict", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef",
    "typeof", "typeof_unqual", "union", "unsigned", "void",
    "volatile", "while"
    });
}


inline QString makeString(const QString::const_iterator& b,
                   const QString::const_iterator& e)
{
    QString res;
    for(auto i = b; i != e; ++i)
        res.append(*i);
    return res;
}

void LexerC::skipWhiteSpaces()
{
    while(it->isSpace()) ++it;
    forward = it + 1;
}

Token LexerC::scanNumber()
{
    Token res;
    while(forward->isDigit()) ++forward;
    res.stype = ShortType::num;
    return res;
}

Token LexerC::scanIdOrKeyword()
{
    Token res;
    while(forward->isLetterOrNumber() || forward->isSymbol()) ++forward;
    if (std::binary_search(keywords.begin(), keywords.end(), makeString(it, forward)))
        res.stype = ShortType::keyword;
    else
        res.stype = ShortType::id;
    return res;
}

Token LexerC::scanMacro()
{
    Token res;
    while(forward->isLetter()) ++forward;
    res.stype = ShortType::macro;
    return res;
}

Token LexerC::scanString()
{
    Token res;
    while(*forward != '"' && *forward != '\0')
        ++forward; // todo: add special symbols

    ++forward;
    res.stype = ShortType::stringLiter;
    return res;
}

Token LexerC::scan()
{
    Token scanningToken;
    skipWhiteSpaces();

    if (it->isNull())
        return scanningToken;
    else if (it->isDigit())
        scanningToken = scanNumber();
    else if (it->isLetter())
        scanningToken = scanIdOrKeyword();
    else if (*it == '#')
        scanningToken = scanMacro();
    else if (*it == '"')
        scanningToken = scanString();
    else
        scanningToken.stype = ShortType::unknown;

    scanningToken.posStartOfWord = it - begin;
    scanningToken.posEndOfWord   = forward - begin;

    qDebug() << "LexerC::scan() messeage:";
    qDebug() << makeString(it, forward) << ", type=" << static_cast<int>(scanningToken.stype);

    it = forward;
    forward = it + 1;
    return scanningToken;
}
