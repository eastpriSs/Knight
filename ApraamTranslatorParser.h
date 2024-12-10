#ifndef APRAAMTRANSLATORPARSER_H
#define APRAAMTRANSLATORPARSER_H

#include "Parser.h"
#include <QStack>


class ApraamTranslatorParser final : public Parser
{
private:
    QStack<ApraamTokType> products;

    void generateProducts();
    void checkTop();

public:
    ApraamTranslatorParser(Lexer*);
    Token parse() override;
};

#endif // APRAAMTRANSLATORPARSER_H
