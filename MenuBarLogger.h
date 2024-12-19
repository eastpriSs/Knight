#ifndef MENUBARLOGGER_H
#define MENUBARLOGGER_H

#include "Logger.h"
#include <QStatusBar>

class MenuBarLogger final : public Logger
{
private:
    QStatusBar* stbar = nullptr;
public:
    void write(const QString&) override;
    MenuBarLogger(QStatusBar*);
};

#endif // MENUBARLOGGER_H
