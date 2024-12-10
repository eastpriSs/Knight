#include "ApraamTranslatorParser.h"
#include <QDebug>

ApraamTranslatorParser::ApraamTranslatorParser(Lexer* l)
    : Parser(l)
{
    products.push(ApraamTokType::startSymbol);
}

void ApraamTranslatorParser::generateProducts()
{
    qDebug() << "Generating for " << (int)currTkn.ttype;
    switch (currTkn.ttype) {
    case ApraamTokType::VAR:
        products.push(ApraamTokType::numberLiteral);
        products.push(ApraamTokType::id);
        break;
    case ApraamTokType::id:
        products.push(ApraamTokType::id);
        products.push(ApraamTokType::shift);
        products.push(ApraamTokType::numberLiteral);
        products.push(ApraamTokType::arithmOperator);
        break;
    default:
        currTkn.syntaxError = true;
        break;
    }
}

void ApraamTranslatorParser::checkTop()
{
    bool matched = true;
    ApraamTokType expected = products.pop();
    while (currTkn.ttype != expected) {
        if (products.top() == ApraamTokType::startSymbol) {
            matched = false;
            break;
        }
        expected = products.pop();
    }
    if (!matched)
        currTkn.syntaxError = true;

    qDebug() << "SyntaxError:" << currTkn.syntaxError << "type:" << (int)currTkn.ttype << "expected:" << (int)expected;
}

Token ApraamTranslatorParser::parse()
{
    currTkn = lex->scan();
    if (products.top() == ApraamTokType::startSymbol)
        generateProducts();
    else
        checkTop();

    return currTkn;
}
