#ifndef TOKEN_H
#define TOKEN_H


enum class ShortType
{
    unknown, keyword, num, id, _operator, macro, stringLiter, eof
};

enum class ApraamTokType {
    PUSH,POP,SWAP,IN,OUT,IF,
    numberLiteral,id,unknown,assgm,
    to,from,plus,mul,sub,div,VAR,shift,operand,
    label,operLess,operBigger,operEqLess,operEqBig,operEq,
    operNotEqual,stop,jmpConstruction,call,ret,then,startSymbol,
    additiveOperator, logicOperator, multiplicativeOperator,
    assigmentOperator, regA, regB, blockSymbol,
    eof

};
// so big TODO
class Token
{
public:
    Token() = default;
    Token(ShortType);
    Token(ApraamTokType, ShortType);
    ShortType stype = ShortType::eof;
    ApraamTokType ttype = ApraamTokType::eof;
    int posStartOfWord = 0;
    int posEndOfWord = 0;
    int linePosition = 0;
    bool syntaxError = false;
};

#endif // TOKEN_H
