#ifndef APRAAMTRANSLATORPARSER_H
#define APRAAMTRANSLATORPARSER_H

#include "Parser.h"
#include <QStack>


class ApraamTranslatorParser final : public Parser
{
private:
    QStack<ApraamTokType> products;

    void generateProductsForLogicExpression();
    void generateProductsForAnyOperand();
    void generateMultctvOperatorProduct();
    void generateAdditOperatorProduct();
    void generateProducts();
    bool findInVariativeProducts(const ApraamTokType&);
    void checkTop();

public:
    ApraamTranslatorParser(Lexer*);
    ApraamTranslatorParser(Lexer*, Logger*);
    Token parse() override;
};

#endif // APRAAMTRANSLATORPARSER_H
