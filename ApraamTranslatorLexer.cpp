#include "ApraamTranslatorLexer.h"
#include <QDebug>

QHash<QString, ApraamTranslatorLexer::TokenType> ApraamTranslatorLexer::table =
{
    {"push", TokenType::PUSH},
    {"pop", TokenType::POP},
    {"swap", TokenType::SWAP},
    {"in", TokenType::IN},
    {"out", TokenType::OUT},
    {"if", TokenType::IF},
    {"var", TokenType::VAR},
    {"input", TokenType::IN},
    {"push", TokenType::PUSH},
    {"pop", TokenType::POP},
    {"swap", TokenType::SWAP},
    {"jmp", TokenType::jmpConstruction},
    {"jn", TokenType::jmpConstruction},
    {"jz", TokenType::jmpConstruction},
    {"jp", TokenType::jmpConstruction},
    {"jv", TokenType::jmpConstruction},
    {"jnn", TokenType::jmpConstruction},
    {"jnz", TokenType::jmpConstruction},
    {"call", TokenType::call},
    {"ret", TokenType::ret},
    {"stop", TokenType::stop},
    {"then", TokenType::then},
    {"out", TokenType::OUT}
};

ApraamTranslatorLexer::ApraamTranslatorLexer()
    : Lexer("")
{
}

inline QString makeString(const QString::const_iterator& b,
                   const QString::const_iterator& e)
{
    QString res;
    for(auto i = b; i != e; ++i)
        res.append(*i);
    return res;
}

void ApraamTranslatorLexer::skipWhiteSpaces()
{
    while(it->isSpace()) ++it;
    forward = it + 1;
}

inline bool ishex(QChar c) {
    return ('0' <= c && c <= '9') || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f');
}

Token ApraamTranslatorLexer::scanOperand()
{
    if (*it == '0') {
        while (ishex(*forward))
            ++forward;
        if (*forward != '(')
            return Token(TokenType::numberLiteral, ShortType::num);
        ++forward;
        while (forward->isLetterOrNumber())
            ++forward;

        if (*forward++ == ')')
            return Token(TokenType::shift, ShortType::id);
        else
            return Token(TokenType::unknown, ShortType::unknown);
    }
    else {
        while (forward->isLetter())
            ++forward;
        QString lexem = makeString(it, forward);

        if (table.contains(lexem))
            return Token(table[lexem], ShortType::keyword);
        else if (*forward != ':')
            return Token(TokenType::id, ShortType::id);

        ++forward;
        return Token(TokenType::label, ShortType::id);
    }


}

Token ApraamTranslatorLexer::scanOperator()
{
    switch (it->toLatin1())
    {
    case '=':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::logicOperator, ShortType::_operator);
        }
        return Token(TokenType::arithmOperator, ShortType::_operator);
        break;
    }
    case '!':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::logicOperator, ShortType::_operator);
        }
        return Token(TokenType::unknown, ShortType::unknown);
        break;
    }
    case '-':
    {
        switch (forward->toLatin1())
        {
        case '>':
            ++forward;
            return Token(TokenType::arithmOperator, ShortType::_operator);
        case '=':
            ++forward;
            return Token(TokenType::arithmOperator, ShortType::_operator);
        }
        break;
    }
    case '<':
    {
        switch (forward->toLatin1())
        {
        case '-':
            ++forward;
            return Token(TokenType::arithmOperator, ShortType::_operator);
        case '=':
            ++forward;
            return Token(TokenType::logicOperator, ShortType::_operator);
        }
        return Token(TokenType::logicOperator, ShortType::_operator);
        break;
    }
    case '>':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::logicOperator, ShortType::_operator);
        }
        return Token(TokenType::logicOperator, ShortType::_operator);
        break;
    }
    case '+':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::arithmOperator, ShortType::_operator);
        }
        break;
    }
    case '*':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::arithmOperator, ShortType::_operator);
        }
        break;
    }
    case '/':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::arithmOperator, ShortType::_operator);
        }
        break;
    }
    }
    return Token(TokenType::unknown, ShortType::unknown);
}

Token ApraamTranslatorLexer::scan()
{
    Token scanningToken;
    skipWhiteSpaces();

    if (it->isNull())
        return scanningToken;

    scanningToken = scanOperator();

    if (scanningToken.ttype == TokenType::unknown)
        scanningToken = scanOperand();

    scanningToken.posStartOfWord = it - begin;
    scanningToken.posEndOfWord   = forward - begin;

    qDebug() << "ApraamTranslatorLexer::scan() messeage:";
    qDebug() << makeString(it, forward) << ", type=" << static_cast<int>(scanningToken.ttype);

    it = forward;
    forward = it + 1;
    return scanningToken;
}
