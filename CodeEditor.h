#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QListWidget>

#include "SyntaxHighlighter.h"
#include "LanguageList.h"

namespace CodeEditorStates
{
enum codeEditorMode {commandMode, fullEditMode};
}

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    QString nameEditingFile = "untitled";
    CodeEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void changeToDarkTheme();
    void changeToLightTheme();
    void turnOnCurrentLineHighlighter();
    void turnOffCurrentLineHighlighter();

protected:
    void resizeEvent(QResizeEvent *event) override;

private :
    void changeModeToFullEdit();
    void changeModeToCommandInput();
    void keyPressEventInCommandMode(QKeyEvent *event);
    void keyPressEventInEditMode(QKeyEvent *event);
    void openSwitchingLanguageMenu();

private slots:
    void keyPressEvent(QKeyEvent *event) override;
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
    void languageChanged(QListWidget*);
    inline void setTabsSize(int size) noexcept;

private:
    int tabsSize = 4;
    SyntaxHiglighter highlighter = SyntaxHiglighter(document());;
    CodeEditorStates::codeEditorMode mode = CodeEditorStates::codeEditorMode::fullEditMode;
    QColor currentLineColor;
    QColor currentLineSymbolColor;

    bool highlightEnabled;

    QWidget *lineNumberArea;
    LanguageList *langList;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor){}

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

#endif // CODEEDITOR_H
