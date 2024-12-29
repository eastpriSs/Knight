#ifndef APRAAMTRANSLATORLEXER_H
#define APRAAMTRANSLATORLEXER_H

#include "Lexer.h"
#include "Token.h"
#include <QHash>

class ApraamTranslatorLexer final : public Lexer
{
private:
    typedef ApraamTokType TokenType;
    const static QHash<QString, TokenType> table;

    void skipWhiteSpaces();
    [[nodiscard]]
    Token scanOperator();
    [[nodiscard]]
    Token scanOperand();

public:
    ApraamTranslatorLexer();
    Token scan() override;
};


#endif // APRAAMTRANSLATORLEXER_H
