#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPlainTextEdit>
#include <QProcess>

#include "CodeEditor.h"
#include "ConsoleOutput.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadAction_triggered();
    void on_saveAction_triggered();
    void on_saveAsAction_triggered();

    void on_sendSettingAction_triggered();

    void on_sendAction_triggered();

    void on_turnOnDarkTheme_triggered();

    void on_turnOnLightTheme_triggered();

    void on_turnOnCurrentLineHighlighter_triggered();

    void on_turnOffCurrentLineHighlighter_triggered();

private:
    CodeEditor codeEditor;
    ConsoleOutput* consoleOutput;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
