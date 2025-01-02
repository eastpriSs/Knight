#include "LexerC.h"

#define TESTMODE

LexerC::LexerC()
    : Lexer()
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
    res.stype = ShortTokType::num;
    return res;
}

Token LexerC::scanIdOrKeyword()
{
    Token res;
    while(forward->isLetterOrNumber() || forward->isSymbol()) ++forward;

    QString lexem = makeString(it, forward);
    if (std::binary_search(keywords.begin(), keywords.end(), lexem))
        res.stype = ShortTokType::keyword;
    else
        res.stype = ShortTokType::id;

    return res;
}

Token LexerC::scanMacro()
{
    Token res;
    while(forward->isLetter()) ++forward;
    res.stype = ShortTokType::macro;
    return res;
}

Token LexerC::scanString()
{
    Token res;
    while(*forward != '"' && *forward != '\0')
        ++forward; // todo: add special symbols

    ++forward;
    res.stype = ShortTokType::stringLiter;
    return res;
}

void LexerC::tryAddLastLexemToCompleter()
{
    QStringList model = completerModel->stringList();
    if (!std::binary_search(model.constBegin(), model.constEnd(), lastLexem)){
        model.insert(std::upper_bound(model.constBegin(), model.constEnd(), lastLexem), lastLexem);
        completerModel->setStringList(model);
    }
}

Token LexerC::scan()
{
    Token scanningToken;

    if (it->isSpace()){
        tryAddLastLexemToCompleter();
        ++it;
    }

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
        scanningToken.stype = ShortTokType::unknown;

    scanningToken.posStartOfWord = it - begin;
    scanningToken.lengthOfWord   = forward - begin;

    lastLexem = makeString(it,forward);

    #ifdef TESTMODE
    qDebug() << "LexerC::scan() messeage:";
    qDebug() << makeString(it, forward) << ", type=" << static_cast<int>(scanningToken.stype);
    #endif

    it = forward;
    forward = it + 1;
    return scanningToken;
}
