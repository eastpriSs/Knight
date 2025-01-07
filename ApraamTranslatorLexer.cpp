#include "ApraamTranslatorLexer.h"

const QHash<QString, ApraamTranslatorLexer::TokenType> ApraamTranslatorLexer::table =
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
    : Lexer()
{
    keywords = {"call", "if", "in", "input", "jmp", "jn", "jnn", "jnz",
                "jp", "jv", "out", "pop", "push", "ret", "stop", "swap", "then", "var"};
}

inline QString makeString(const QString::const_iterator& b,
                   const QString::const_iterator& e)
{
    QString res;
    for(auto i = b; i != e; ++i)
        res.append(*i);
    return res;
}

QString ApraamTranslatorLexer::getLastLexem() const
{
    return lastLexem;
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
            return Token(TokenType::numberLiteral, ShortTokType::num);
        ++forward;
        while (forward->isLetterOrNumber())
            ++forward;

        if (*forward++ == ')')
            return Token(TokenType::shift, ShortTokType::id);
        else
            return Token(TokenType::unknown, ShortTokType::unknown);
    }
    else {
        while (forward->isLetter())
            ++forward;
        QString lexem = makeString(it, forward);

        if (std::binary_search(keywords.begin(), keywords.end(), lexem)) {
            return Token(table[lexem], ShortTokType::keyword);
        }
        else if (*forward != ':') {
            if (lexem == "a")
                return Token(TokenType::regA, ShortTokType::id);
            else if (lexem == "b")
                return Token(TokenType::regB, ShortTokType::id);
            return Token(TokenType::id, ShortTokType::id);
        }
        ++forward;
        return Token(TokenType::label, ShortTokType::id);
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
            return Token(TokenType::logicOperator, ShortTokType::_operator);
        }
        return Token(TokenType::assigmentOperator, ShortTokType::_operator);
        break;
    }
    case '!':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::logicOperator, ShortTokType::_operator);
        }
        return Token(TokenType::unknown, ShortTokType::unknown);
        break;
    }
    case '-':
    {
        switch (forward->toLatin1())
        {
        case '>':
            ++forward;
            return Token(TokenType::to, ShortTokType::_operator);
        case '=':
            ++forward;
            return Token(TokenType::additiveOperator, ShortTokType::_operator);
        }
        break;
    }
    case '<':
    {
        switch (forward->toLatin1())
        {
        case '-':
            ++forward;
            return Token(TokenType::from, ShortTokType::_operator);
        case '=':
            ++forward;
            return Token(TokenType::logicOperator, ShortTokType::_operator);
        }
        return Token(TokenType::logicOperator, ShortTokType::_operator);
        break;
    }
    case '>':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::logicOperator, ShortTokType::_operator);
        }
        return Token(TokenType::logicOperator, ShortTokType::_operator);
        break;
    }
    case '+':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::additiveOperator, ShortTokType::_operator);
        }
        break;
    }
    case '*':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::multiplicativeOperator, ShortTokType::_operator);
        }
        break;
    }
    case '/':
    {
        switch (forward->toLatin1())
        {
        case '=':
            ++forward;
            return Token(TokenType::multiplicativeOperator, ShortTokType::_operator);
        }
        break;
    }
    }
    return Token(TokenType::unknown, ShortTokType::unknown);
}

Token ApraamTranslatorLexer::scan()
{
    Token scanningToken(TokenType::eof, ShortTokType::eof);
    skipWhiteSpaces();

    if (it->isNull())
        return scanningToken;

    scanningToken = scanOperator();
    if (std::get<TokenType>(scanningToken.ttype) == TokenType::unknown)
        scanningToken = scanOperand();

    scanningToken.posStartOfWord = it - begin;
    scanningToken.lengthOfWord   = forward - begin;
    lastLexem = makeString(it, forward);
    #ifdef TESTMODE
    qDebug() << "ApraamTranslatorLexer::scan() messeage:";
    qDebug() << makeString(it, forward) << ", type=" << static_cast<int>(std::get<ApraamTokType>(scanningToken.ttype));
    #endif

    it = forward;
    forward = it + 1;
    return scanningToken;
}
