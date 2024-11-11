#ifndef LEXERC_H
#define LEXERC_H

#include "Lexer.h"
#include <QDebug>

class LexerC final : public Lexer
{
private:
    void skipWhiteSpaces();
    [[nodiscard]]
    Token scanNumber();
    [[nodiscard]]
    Token scanIdOrKeyword();
    [[nodiscard]]
    Token scanMacro();
    [[nodiscard]]
    Token scanString();

public:
    LexerC();
    Token scan() override;
};

#endif // LEXERC_H
