#include "LanguageList.h"
#include <QKeyEvent>

LanguageList::LanguageList(const QList<QString>& list)
    : languages(list)
{
    addItems(languages);
}

void LanguageList::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Escape)
        this->close();
    QListWidget::keyPressEvent(event);
}
