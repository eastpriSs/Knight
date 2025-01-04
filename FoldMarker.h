#ifndef FOLDMARKER_H
#define FOLDMARKER_H

#include <QWidget>

class FoldMarker : public QWidget {
    Q_OBJECT

public:
    explicit FoldMarker(QWidget *parent = nullptr);
    void setBlockIndex(int index);
    int blockIndex() const;
    void setFoldState(bool folded);
    bool isFolded() const;

signals:
    void toggled(int blockIndex);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    int blockIndex_;
    bool foldState_; // Хранит состояние свернутого/развернутого блока
};

#endif // FOLDMARKER_H
