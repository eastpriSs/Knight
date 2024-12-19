#include "MenuBarLogger.h"

MenuBarLogger::MenuBarLogger(QStatusBar* bar)
    :stbar(bar)
{
}

void MenuBarLogger::write(const QString& m)
{
    stbar->showMessage(m);
}
