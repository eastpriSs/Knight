#include "LanguageList.h"
#include <QKeyEvent>

LanguageList::LanguageList()
{
    addItems(languages);
}

void LanguageList::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Escape)
        this->close();
    QListWidget::keyPressEvent(event);
}
