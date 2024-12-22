#include "HintLogger.h"
#include <QToolTip>

HintLogger::HintLogger(QPlainTextEdit* t)
    :text(t)
{
}

void HintLogger::write(const QString& m)
{
    QToolTip::showText(text->mapToGlobal(QPoint(text->width()/2, text->height()/2)), m, text, QRect(100,100,100,100), 3000);
}
