#include <QPainter>
#include <QTextBlock>
#include <QFileDialog>
#include <QLabel>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingmenusendaction.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    codeEditor = new CodeEditor();
    consoleOutput = nullptr;
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
    codeEditor->nameEditingFile = fileName;
    setWindowTitle(fileName);

    QFile f(fileName);
    if (f.open(QFile::ReadOnly))
        codeEditor->setPlainText(f.readAll());
    else
        ui->statusbar->showMessage("Файл не может быть прочитан. Возможно, файл архивирован.");
}


void MainWindow::on_saveAction_triggered()
{
    QFile f(codeEditor->nameEditingFile);
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
    codeEditor->nameEditingFile = fileName;
    setWindowTitle(codeEditor->nameEditingFile);
}


void MainWindow::on_sendSettingAction_triggered()
{
    SettingMenuSendAction* settingMenu = new SettingMenuSendAction(this);
    settingMenu->setWindowModality(Qt::WindowModal);
    settingMenu->exec();
    delete settingMenu;
}


void startCmdProc(QProcess& cmdProc, const QString& command)
{
    cmdProc.setArguments(QStringList() << "/c" << command);
    cmdProc.setProgram("cmd.exe");
    cmdProc.start();
    cmdProc.waitForFinished();
}

QString readLineFormFile(const QString& fn)
{
    QFile compilerSettingFile(fn);
    compilerSettingFile.open(QIODevice::ReadOnly);
    QTextStream in(&compilerSettingFile);
    return in.readLine();
}

void MainWindow::on_sendAction_triggered()
{
    QString compilerName = readLineFormFile("compiler.cfg");
    QString command = compilerName + ' ' + codeEditor->nameEditingFile;
    QProcess cmdProc;

    ui->statusbar->showMessage("Sending command: " + command);
    startCmdProc(cmdProc, command);

    QByteArray standardOut = cmdProc.readAllStandardOutput();
    QByteArray errorOut = cmdProc.readAllStandardError();
    QString    result = "";

    if (errorOut.isEmpty())
        result = "Compile is succesful";

    if (consoleOutput != nullptr)
        delete consoleOutput;

    consoleOutput = new ConsoleOutput(standardOut, errorOut, result);
    consoleOutput->show();
}

