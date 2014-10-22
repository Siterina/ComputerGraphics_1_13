#ifndef DRAWLINE_H
#define DRAWLINE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <cmath>
#include <cstdio>
#include <string.h>
#include <cstring>
#include <Qstring>
#include <Qpen>
#include <vector>
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class DrawLine;
}

class DrawLine : public QWidget
{
    Q_OBJECT

public:
    explicit DrawLine(QWidget *parent = 0);

    double a;
    double step;
    double quarter;
    QString colour;
    QPen pen;
    int shift_x;
    int shift_y;
    int pen_width;
    double angle;

    ~DrawLine();



private slots:
    void on_Draw_clicked();

private:
    Ui::DrawLine *ui;
    QGraphicsScene *scene;

protected:
    void paintEvent(QPaintEvent*);
};


class Matrix
{
public:

     double Arr[2][2];

     QPointF operator*(const QPointF& a) const;
     Matrix();
};


#endif // DRAWLINE_H
