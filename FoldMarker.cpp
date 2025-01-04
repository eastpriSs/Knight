#include "FoldMarker.h"
#include <QPainter>
#include <QMouseEvent>

FoldMarker::FoldMarker(QWidget *parent)
    : QWidget(parent), blockIndex_(-1), foldState_(true) {
    setFixedSize(15, 15);
}

void FoldMarker::setBlockIndex(int index) {
    blockIndex_ = index;
}

int FoldMarker::blockIndex() const {
    return blockIndex_;
}

void FoldMarker::setFoldState(bool isFolded) {
    foldState_ = isFolded;
    update();
}

bool FoldMarker::isFolded() const {
    return foldState_;
}

void FoldMarker::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit toggled(blockIndex_);
    }
}

void FoldMarker::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // Устанавливаем цвет маркера
    QColor markerColor = foldState_ ? Qt::darkBlue : Qt::darkGreen;
    painter.fillRect(rect(), markerColor);

    // Рисуем текст
    painter.setPen(Qt::white);
    QString symbol = foldState_ ? "+" : "-";
    painter.drawText(rect(), Qt::AlignCenter, symbol);
}
