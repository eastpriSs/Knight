#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QTextBlock>
#include <QFileDialog>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    codeEditor = new CodeEditor();
    setCentralWidget(codeEditor);
}

MainWindow::~MainWindow()
{
    delete codeEditor;
    delete ui;
}



void MainWindow::on_loadAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                    tr("Выберите файл для загрузки"), ".", tr("Source code (*.txt *.cpp *.c *.lua *.h)"));
    codeEditor->setNameEditingFile(fileName);
    setWindowTitle(fileName);

    QFile f(fileName);
    if (f.open(QFile::ReadOnly))
        codeEditor->setPlainText(f.readAll());
    else
        ui->statusbar->showMessage("Файл не может быть прочитан. Возможно, файл архивирован.");
}


void MainWindow::on_saveAction_triggered()
{
    QFile f(fileName);
    if (!f.exists()){
        on_saveAsAction_triggered();
    }
    f.open(QFile::WriteOnly);
    QTextStream writeStream(&f);
    writeStream << codeEditor->toPlainText();
}


void MainWindow::on_saveAsAction_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как"),
                                                    ".",
                                                    tr("Source code (*.txt *.cpp *.c *.lua *.h)")); // <- only one lenguage
    QFile f(fileName);
    if (!f.open(QFile::WriteOnly)){
        ui->statusbar->showMessage("Файл не может быть открыт. Возможно, файл архивирован.");
        return;
    }
    QTextStream writeStream(&f);
    writeStream << codeEditor->toPlainText();
    codeEditor->setNameEditingFile(fileName);
    setWindowTitle(nameEditingFile);
}

