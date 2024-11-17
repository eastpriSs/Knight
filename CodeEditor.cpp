#include "CodeEditor.h"
#include <QPainter>
#include <QTextBlock>
#include <QFontMetrics>
#include <memory>

#include "LanguageList.h"
#include "AnalyzerC.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);
    langList = nullptr;

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    currentLineSymbolColor = Qt::black;
    currentLineColor = Qt::lightGray;
    highlightCurrentLine();
    setTabsSize(tabsSize);
}

inline void CodeEditor::setTabsSize(int size) noexcept
{
    // add font to code editor
    tabsSize = size;
    setTabStopDistance(QFontMetrics(QFont()).horizontalAdvance(' ') * size * 2);
}

int CodeEditor::lineNumberAreaWidth()
{
    return 100;
}

void CodeEditor::updateLineNumberAreaWidth(int)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::changeModeToCommandInput()
{
    mode = CodeEditorStates::codeEditorMode::commandMode;
    setFixedHeight(height() - 100);
    setReadOnly(true);
}

void CodeEditor::changeModeToFullEdit()
{
    mode = CodeEditorStates::codeEditorMode::fullEditMode;
    setFixedHeight(height() + 100);
    setReadOnly(false);
}

void CodeEditor::languageChanged(QListWidget* list)
{
    if (list->currentItem()->text() == "C") // todo: remove magic const
        highlighter.switchAnalyzer(new AnalyzerC());
    else
        highlighter.switchAnalyzer(new Analyzer());

    highlighter.setDocument(document());
}

void CodeEditor::openSwitchingLanguageMenu()
{
    if (langList != nullptr)
        delete langList;
    langList = new LanguageList();
    langList->addItems({"C", "Java", "Non"}); // todo: remove magic const
    langList->setWindowModality(Qt::WindowModal);
    langList->setFocus();
    connect(langList, &QListWidget::itemSelectionChanged, this,
            [this]()
            {
                this->languageChanged(langList);
            }
    );
    langList->show();
    QEventLoop loop;
    connect(this, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();
}

void CodeEditor::keyPressEventInCommandMode(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        changeModeToFullEdit();
        break;
    case Qt::Key_L:
        openSwitchingLanguageMenu();
    }
}

void CodeEditor::keyPressEventInEditMode(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        changeModeToCommandInput();
        break;
    default:
        QPlainTextEdit::keyPressEvent(event);
    }
}

void CodeEditor::keyPressEvent(QKeyEvent *event)
{
    using namespace CodeEditorStates;

    if (mode == codeEditorMode::commandMode)
        keyPressEventInCommandMode(event);
    else if (mode == codeEditorMode::fullEditMode)
        keyPressEventInEditMode(event);
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(currentLineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.format.setForeground(currentLineSymbolColor);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void CodeEditor::changeToDarkTheme()
{
    setStyleSheet("color: white;");
    currentLineColor = QColor::fromRgb(46, 47, 48);
    currentLineSymbolColor = QColor::fromRgb(181,104,43);
    highlightCurrentLine();
    highlighter.turnOnDarkTheme();
    highlighter.setDocument(document());
}

void CodeEditor::changeToBrightTheme()
{
    setStyleSheet("color: black;");
    currentLineColor = Qt::lightGray;
    currentLineSymbolColor = Qt::black;
    highlightCurrentLine();
}

void CodeEditor::changeToCustomTheme()
{

}
