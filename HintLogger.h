#ifndef HINTLOGGER_H
#define HINTLOGGER_H

#include <QPlainTextEdit>
#include "Logger.h"

class HintLogger : public Logger
{
private:
    QPlainTextEdit* text = nullptr;
public:
    HintLogger(QPlainTextEdit*);
    void write(const QString&) override;
};

#endif // HINTLOGGER_H
