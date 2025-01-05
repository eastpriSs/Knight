#ifndef APRAAMTRANSLATORPARSER_H
#define APRAAMTRANSLATORPARSER_H

#include "Parser.h"
#include <QStack>


class ApraamTranslatorParser final : public Parser
{
private:
    QStack<ApraamTokType> products;
    QList<ApraamTokType> expected;
    bool isSyntaxErrorExist;

    void generateProductsForLogicExpression();
    void generateProductsForAnyOperand();
    void generateMultctvOperatorProduct();
    void generateAdditOperatorProduct();
    void generateProducts();
    void checkTop();

public:
    ApraamTranslatorParser(Lexer*);
    ApraamTranslatorParser(Lexer*, Logger*);
    Token parse() override;
    void prepare() override;
};

#endif // APRAAMTRANSLATORPARSER_H
