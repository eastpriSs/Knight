#include <QPainter>
#include <QTextBlock>
#include <QFileDialog>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SettingMenuSendAction.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    consoleOutput = nullptr;
    setCentralWidget(&codeEditor);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_loadAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                    tr("Выберите файл для загрузки"), ".", tr("Source code (*.txt *.cpp *.c *.lua *.h)"));
    codeEditor.nameEditingFile = fileName;
    setWindowTitle(fileName);

    QFile f(fileName);
    if (f.open(QFile::ReadOnly))
        codeEditor.setPlainText(f.readAll());
    else
        ui->statusbar->showMessage("Файл не может быть прочитан. Возможно, файл архивирован.");
}


void MainWindow::on_saveAction_triggered()
{
    QFile f(codeEditor.nameEditingFile);
    if (!f.exists()){
        on_saveAsAction_triggered();
    }
    f.open(QFile::WriteOnly);
    QTextStream writeStream(&f);
    writeStream << codeEditor.toPlainText();
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
    writeStream << codeEditor.toPlainText();
    codeEditor.nameEditingFile = fileName;
    setWindowTitle(codeEditor.nameEditingFile);
}

QString readLineFormFile(QFile& fn)
{
    QTextStream in(&fn);
    return in.readLine();
}

void MainWindow::on_sendSettingAction_triggered()
{
    SettingMenuSendAction* settingMenu;
    QFile compilerSettingFile("compiler.cfg");
    if (compilerSettingFile.open(QIODevice::ReadOnly))
        settingMenu = new SettingMenuSendAction(readLineFormFile(compilerSettingFile), this);
    else
        settingMenu = new SettingMenuSendAction(this);

    compilerSettingFile.close();
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


void MainWindow::on_sendAction_triggered()
{
    QFile compilerSettingFile("compiler.cfg");
    if (!compilerSettingFile.open(QIODevice::ReadOnly)){
        compilerSettingFile.close();
        ui->statusbar->showMessage("File \"compiler.cfg\" did not found.");
        return;
    }
    QString compilerName = readLineFormFile(compilerSettingFile);
    QString command = compilerName + ' ' + codeEditor.nameEditingFile;
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

    compilerSettingFile.close();
    consoleOutput = new ConsoleOutput(standardOut, errorOut, result);
    consoleOutput->show();
}

void MainWindow::on_turnOnDarkTheme_triggered()
{
    qApp->setStyleSheet(
        "QWidget { background-color: #2e2f30; color: white; }"
        "QPushButton, QLabel, QLineEdit, QTreeWidget, QMenuBar, QMenu::item { color: white; }"
        );
    codeEditor.changeToDarkTheme();

}

void MainWindow::on_turnOnLightTheme_triggered()
{
    qApp->setStyleSheet(
        "QWidget { background-color: white; color: black; }"
        "QPushButton, QLabel, QLineEdit, QTreeWidget, QMenuBar, QMenu::item { color: black; }"
        );
    codeEditor.changeToLightTheme();

}

void MainWindow::on_turnOnCurrentLineHighlighter_triggered()
{
    codeEditor.turnOnCurrentLineHighlighter();
}

void MainWindow::on_turnOffCurrentLineHighlighter_triggered()
{
    codeEditor.turnOffCurrentLineHighlighter();
}

