#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H

#include <QWidget>

namespace Ui {
class ConsoleOutput;
}

class ConsoleOutput : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleOutput(QWidget *parent = nullptr);
    ConsoleOutput(QString, QString, QWidget *parent = nullptr);
    ~ConsoleOutput();

private:
    Ui::ConsoleOutput *ui;
};

#endif // CONSOLEOUTPUT_H
