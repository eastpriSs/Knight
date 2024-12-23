#include "CodeEditor.h"
#include <QPainter>
#include <QTextBlock>
#include <QFontMetrics>
#include <QToolTip>

#include "LanguageList.h"
#include "AnalyzerC.h"
#include "AnalyzerApraam.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);
    langList = nullptr;

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth();
    changeToLightTheme();
    QFont charFont = QFont();
    charFont.setPointSize(10); // magic const BIG TODO
    setFont(charFont);
    setTabsSize(tabsSize);
}

inline void CodeEditor::setTabsSize(int size) noexcept
{
    tabsSize = size;
    setTabStopDistance(QFontMetrics(QFont()).horizontalAdvance(' ') * size * 2);
}

int CodeEditor::lineNumberAreaWidth()
{
    return 100;
}

void CodeEditor::updateLineNumberAreaWidth()
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
        updateLineNumberAreaWidth();
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
    logger.hide();
    if (list->currentItem()->text() == "C")  {   // fix magic const
        highlighter.switchAnalyzer(new AnalyzerC());
    } else if (list->currentItem()->text() == "Apraam") {
        logger.show();
        highlighter.switchAnalyzer(new AnalyzerApraam(&logger));
    } else {
        highlighter.switchAnalyzer(new Analyzer());
    }
    highlighter.setDocument(document());
}

void CodeEditor::openSwitchingLanguageMenu()
{
    if (langList != nullptr)
        delete langList;
    langList = new LanguageList();
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

void CodeEditor::makeNewLine(QKeyEvent *event)
{
    static int amountOfTabs = 0;

    QString text = document()->toPlainText();
    int  cursorPos = textCursor().position();

    if (cursorPos != 0 && !text.isEmpty())
    {
        if (text[cursorPos - 1] == '{')
            amountOfTabs += 1;
        else if (text[cursorPos - 1] == '}')
            amountOfTabs -= 1;
    }

    QPlainTextEdit::keyPressEvent(event);
    for (int i = 0; i < amountOfTabs; ++i)
        insertPlainText("\t");
}

void CodeEditor::makeFormat(QKeyEvent* event)
{
    QString text = document()->toPlainText();
    int  cursorPos = textCursor().position();

    if (cursorPos >= 2)
    {
        if (text[cursorPos - 1] == '=' && text[cursorPos - 2] == '!'){
            text[cursorPos - 1] = L'≠';
            text[cursorPos - 2] = L' ';
            document()->setPlainText(text);
        }
    }
    QPlainTextEdit::keyPressEvent(event);
}

void CodeEditor::keyPressEventInEditMode(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        changeModeToCommandInput();
        break;
    case Qt::Key_Return:
        makeNewLine(event);
        break;
    case Qt::Key_Space:
        makeFormat(event);
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

    if (highlightEnabled && !isReadOnly()) {
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
            painter.drawText(0, top, lineNumberArea->width(), 20, // magic const height 20 BIG TODO
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
    currentLineColor = QColor::fromRgb(53, 57, 66);         // DarkBlue
    currentLineSymbolColor = QColor::fromRgb(173, 216, 230);// LightBlue
    highlightCurrentLine();
    highlighter.turnOnDarkTheme();
    highlighter.setDocument(document());
}

void CodeEditor::changeToLightTheme()
{
    setStyleSheet("color: black;");
    currentLineColor = QColor::fromRgb(173, 205, 255);      // LightBlue 2
    currentLineSymbolColor = QColor::fromRgb(32, 47, 92);   // DarkBlue 2
    highlightCurrentLine();
    highlighter.turnOnLightTheme();
    highlighter.setDocument(document());
}

void CodeEditor::turnOnCurrentLineHighlighter()
{
    highlightEnabled = true;
    highlightCurrentLine();
}

void CodeEditor::turnOffCurrentLineHighlighter()
{
    highlightEnabled = false;
    highlightCurrentLine();
}
