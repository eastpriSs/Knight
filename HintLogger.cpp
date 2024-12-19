#include "HintLogger.h"
#include <QToolTip>

HintLogger::HintLogger(QPlainTextEdit* t)
    :text(t)
{
}

void HintLogger::write(const QString& m)
{
    QToolTip::showText(text->mapToGlobal(text->cursorRect().center()), m, text, text->cursorRect());
}
