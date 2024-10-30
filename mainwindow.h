#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPlainTextEdit>

#include "CodeEditor.h"

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

private:
    QString nameEditingFile = "untitled";
    CodeEditor *codeEditor;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
