#ifndef LEXERC_H
#define LEXERC_H

#include "Lexer.h"
#include <QStringListModel>
#include <QHash>

class LexerC final : public Lexer
{
private:
    QString lastLexem = {};
    ShortTokType lastLexemType = {};

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

    void tryAddLastLexemToCompleter();

public:
    LexerC();
    Token scan() override;
};

#endif // LEXERC_H
