#include "CommandInfoList.h"

const QStringList CommandInfoList::infoLabels =
{
    "[ ESC ] - Сменить режим редактора.",
    "[ L ] - Выбор синтаксиса.",
    "[ I ] - Увеличить размер шрифта.",
    "[ R ] - Уменьшить размер шрифта.",
    "[ Q ] - Быстрый поиск подстроки.",
    "[ E ] - RE поиск.",
    "[ H ] - Замена подстроки.",
    "[ J ] - RE замена.",
};

CommandInfoList::CommandInfoList(QWidget* parent)
    : QListWidget(parent)
{
    addItems(infoLabels);
}
