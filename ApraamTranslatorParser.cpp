#include "ApraamTranslatorParser.h"
#include <QDebug>

ApraamTranslatorParser::ApraamTranslatorParser(Lexer* l)
    : Parser(l)
{
    products.push(ApraamTokType::startSymbol);
}

ApraamTranslatorParser::ApraamTranslatorParser(Lexer* l, Logger* lg)
    : Parser(l, lg)
{
    products.push(ApraamTokType::startSymbol);
}

void ApraamTranslatorParser::generateProductsForAnyOperand()
{
    products.push(ApraamTokType::regA);
    products.push(ApraamTokType::regB);
    products.push(ApraamTokType::id);
    products.push(ApraamTokType::shift);
    products.push(ApraamTokType::numberLiteral);
}

void ApraamTranslatorParser::generateMultctvOperatorProduct()
{
    generateProductsForAnyOperand();
    products.push(ApraamTokType::multiplicativeOperator);
}
void ApraamTranslatorParser::generateAdditOperatorProduct()
{
    generateProductsForAnyOperand();
    products.push(ApraamTokType::additiveOperator);
}


void ApraamTranslatorParser::generateProductsForLogicExpression()
{
    products.push(ApraamTokType::regA);
    products.push(ApraamTokType::regB);
    products.push(ApraamTokType::logicOperator);
    products.push(ApraamTokType::regA);
    products.push(ApraamTokType::regB);
    products.push(ApraamTokType::id);
    products.push(ApraamTokType::shift);
}

void ApraamTranslatorParser::generateProducts()
{
    qDebug() << "Generating for " << (int)currTkn.ttype;
    switch (currTkn.ttype) {

    // Definitions
    case ApraamTokType::VAR:
        products.push(ApraamTokType::numberLiteral);
        products.push(ApraamTokType::id);
        break;

    case ApraamTokType::label:
        break;

    // Expression
    case ApraamTokType::regA:
        generateMultctvOperatorProduct();
        generateAdditOperatorProduct();
        products.push(ApraamTokType::id);
        products.push(ApraamTokType::to);
        products.push(ApraamTokType::id);
        products.push(ApraamTokType::from);
        break;
    case ApraamTokType::regB:
        generateAdditOperatorProduct();
        products.push(ApraamTokType::id);
        products.push(ApraamTokType::to);
        products.push(ApraamTokType::id);
        products.push(ApraamTokType::from);
        break;

    // Trivial operators
    case ApraamTokType::SWAP:
    case ApraamTokType::stop:
        break;

    // Unary-trivial operators
    case ApraamTokType::PUSH:
    case ApraamTokType::POP:
        products.push(ApraamTokType::regA);
        products.push(ApraamTokType::regB);
        break;

    // Calling-unary operators
    case ApraamTokType::jmpConstruction:
    case ApraamTokType::call:
        products.push(ApraamTokType::id);
        break;

    // Unary-nontrivial operators
    case ApraamTokType::IN:
    case ApraamTokType::OUT:
        generateProductsForAnyOperand();
        break;

    // Condition operators
    case ApraamTokType::IF:
        products.push(ApraamTokType::id);
        products.push(ApraamTokType::then);
        generateProductsForLogicExpression();
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
    if (!matched) {
        currTkn.syntaxError = true;
        logger->write("Syntax error");
    }
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
