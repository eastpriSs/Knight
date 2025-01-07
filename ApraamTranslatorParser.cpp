#include "ApraamTranslatorParser.h"
#include <QHash>


inline const QHash<ApraamTokType, QString> tokenStrEquivalent =
    {
        {ApraamTokType::PUSH, "PUSH"},
        {ApraamTokType::POP, "POP"},
        {ApraamTokType::SWAP, "SWAP"},
        {ApraamTokType::IN, "IN"},
        {ApraamTokType::OUT, "OUT"},
        {ApraamTokType::IF, "IF"},
        {ApraamTokType::numberLiteral, "Числовой литерал"},
        {ApraamTokType::id, "Идентификатор"},
        {ApraamTokType::unknown, "Неизвестный"},
        {ApraamTokType::assgm, "Присваивание"},
        {ApraamTokType::plus, "Плюс"},
        {ApraamTokType::mul, "Умножение"},
        {ApraamTokType::sub, "Минус"},
        {ApraamTokType::div, "Деление"},
        {ApraamTokType::VAR, "Переменная"},
        {ApraamTokType::shift, "Сдвиг"},
        {ApraamTokType::operand, "Операнд"},
        {ApraamTokType::label, "Метка"},
        {ApraamTokType::operLess, "Оператор меньше"},
        {ApraamTokType::operBigger, "Оператор больше"},
        {ApraamTokType::operEqLess, "Оператор меньше или равно"},
        {ApraamTokType::operEqBig, "Оператор больше или равно"},
        {ApraamTokType::operEq, "Оператор равно"},
        {ApraamTokType::operNotEqual, "Оператор не равно"},
        {ApraamTokType::stop, "Стоп"},
        {ApraamTokType::jmpConstruction, "Конструкция перехода"},
        {ApraamTokType::call, "Вызов"},
        {ApraamTokType::ret, "Возврат"},
        {ApraamTokType::then, "Тогда"},
        {ApraamTokType::startSymbol, "Начальный символ"},
        {ApraamTokType::additiveOperator, "Аддитивный оператор"},
        {ApraamTokType::logicOperator, "Логический оператор"},
        {ApraamTokType::multiplicativeOperator, "Мультипликативный оператор"},
        {ApraamTokType::assigmentOperator, "Оператор присваивания"},
        {ApraamTokType::regA, "Регистр A"},
        {ApraamTokType::regB, "Регистр B"},
        {ApraamTokType::to, "to"},
        {ApraamTokType::from, "from"},
        {ApraamTokType::eof, "Конец файла"}
};


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

QString makeInfoMessage(const QList<ApraamTokType>& expctd,
                        const ApraamTokType& found,
                        const QString& foundLexem)
{
    QString message = "Ожидался один из следующих символов:\n";
    foreach (const ApraamTokType& i, expctd) {
        message += tokenStrEquivalent[i];
        message += ",\n";
    }
    message += "но найден ";
    message += tokenStrEquivalent[found];
    message += "(\"";
    message += foundLexem;
    message += "\")";
    return message;
}

void ApraamTranslatorParser::generateProductsForAnyOperand()
{
    products.push(ApraamTokType::blockSymbol);
    products.push(ApraamTokType::regA);
    products.push(ApraamTokType::regB);
    products.push(ApraamTokType::id);
    products.push(ApraamTokType::shift);
    products.push(ApraamTokType::numberLiteral);
}

void ApraamTranslatorParser::generateMultctvOperatorProduct()
{
    generateProductsForAnyOperand(); // a /= b ??
    products.push(ApraamTokType::blockSymbol);
    products.push(ApraamTokType::multiplicativeOperator);
}
void ApraamTranslatorParser::generateAdditOperatorProduct()
{
    generateProductsForAnyOperand();
    products.push(ApraamTokType::additiveOperator);
}


void ApraamTranslatorParser::generateProductsForLogicExpression()
{
    products.push(ApraamTokType::numberLiteral);
    products.push(ApraamTokType::regB);
    products.push(ApraamTokType::regA);
    products.push(ApraamTokType::blockSymbol);
    products.push(ApraamTokType::logicOperator);
    products.push(ApraamTokType::blockSymbol);
    products.push(ApraamTokType::regA);
    products.push(ApraamTokType::regB);
    products.push(ApraamTokType::id);
    products.push(ApraamTokType::shift);
}

void ApraamTranslatorParser::generateProducts()
{
    const ApraamTokType& currTknType = std::get<ApraamTokType>(currTkn.ttype);

    if (currTknType != ApraamTokType::eof)
        logger->clear();

    switch (currTknType) {

    // Definitions
    case ApraamTokType::VAR:
        products.push(ApraamTokType::blockSymbol);
        products.push(ApraamTokType::numberLiteral);
        products.push(ApraamTokType::blockSymbol);
        products.push(ApraamTokType::id);
        break;

    case ApraamTokType::label:
        break;

        // Expression
    case ApraamTokType::regB:
    case ApraamTokType::regA:
        generateProductsForAnyOperand(); // a /= b ??
        products.push(ApraamTokType::blockSymbol);
        products.push(ApraamTokType::multiplicativeOperator);
        products.push(ApraamTokType::additiveOperator);
        products.push(ApraamTokType::assigmentOperator);
        products.push(ApraamTokType::to);
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
        products.push(ApraamTokType::blockSymbol);
        products.push(ApraamTokType::id);
        products.push(ApraamTokType::blockSymbol);
        products.push(ApraamTokType::then);
        products.push(ApraamTokType::blockSymbol);
        generateProductsForLogicExpression();
        break;

    case ApraamTokType::eof:
        break;

    default:
        currTkn.syntaxError = true;
        logger->write("Этот токен просто дешевка.");
        break;
    }
}

void ApraamTranslatorParser::checkTop()
{
    const ApraamTokType& currTknType = std::get<ApraamTokType>(currTkn.ttype);

    if (currTknType == ApraamTokType::eof)
        return;

    while (currTknType != products.top())
    {
        if (products.top() == ApraamTokType::startSymbol || products.top() == ApraamTokType::blockSymbol)
            break;
        expected += products.pop();
    }

    if (currTknType != products.top()) {
        logger->write(makeInfoMessage(expected, currTknType, lex->getLastLexem()));
        currTkn.syntaxError = true;
    } else {
        while (products.top() != ApraamTokType::startSymbol && products.top() != ApraamTokType::blockSymbol)
            products.pop();
    }

    if (products.top() == ApraamTokType::blockSymbol)
        products.pop();
}

void ApraamTranslatorParser::prepare()
{
    products.clear();
    products.push(ApraamTokType::startSymbol);
}

Token ApraamTranslatorParser::parse()
{
    currTkn = lex->scan();
    expected.clear();
    if (products.top() == ApraamTokType::startSymbol)
        generateProducts();
    else
        checkTop();

    return currTkn;
}
