#include "drawline.h"
#include "ui_drawline.h"

#include <QDebug>



Matrix::Matrix(){
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            Arr[i][j] = 0.0;
}

QPointF Matrix::operator*(const QPointF& curr_point) const{
    QPointF result;

    result.setX(curr_point.x() * Arr[0][0] + curr_point.y() * Arr[1][0]);
    result.setY(curr_point.x() * Arr[0][1] + curr_point.y() * Arr[1][1]);

    return result;
}


DrawLine::DrawLine(QWidget *parent) :
    QWidget(parent),
     a(4), step(0.1),
     quarter(3.14), colour("darkGray"),
     shift_x(0), shift_y(0),
     angle(0), pen_width(1),

    ui(new Ui::DrawLine)
{    ui->setupUi(this);
     scene = new QGraphicsScene(this);
     ui->view->setScene(scene);



}

DrawLine::~DrawLine()
{
    delete ui;
}

void DrawLine::paintEvent(QPaintEvent*)
{

    const double pi = 3.1415;
    double end = quarter + step;
    angle = angle * pi / 180;

    double Ky = height()/(2*a);
    double Kx = (width() - 110)/(2*a);
    double K = std::min(Kx, Ky);
    angle = ui->RotateBox->value();


    //QGraphicsView graphicsView;
   // QPainter pic(&graphicsView);
    QPainter pic(this);

    QPainterPath path;
    //path.moveTo(height()/2, width()/2);
  //  path.lineTo(10, 10);
   // scene->addPath(path);
   // QGraphicsScene scene;
   // QGraphicsView view(&scene);
  //  ui->setupUi(this);
   // scene = new QGraphicsScene(this);
  //  ui->view->setScene(scene);
   /* ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->view->setScene(scene);

    QPainterPath path;
    path.moveTo(50, 50);
    path.lineTo(10, 10);
    scene->addPath(path);*/

   // QPainterPath path;
   // path.moveTo(view.height()/2, view.width()/2);
   // path.lineTo(view.height()/3, view.width()/3);
  //  scene.addPath(path);
   // view.show();

    //line
    pic.setPen(Qt::darkGray);
    QPointF vertical1(width() / 2.0 - 50, height() / 9);
    QPointF vertical2(width() / 2.0 - 50, height() - height()/9);
    pic.drawLine(vertical1, vertical2);
    QPointF horizontal1(width() / 8 - 10, height() / 2);
    QPointF horizontal2(width() - width() / 8 -  90, height() / 2);
    pic.drawLine(horizontal1, horizontal2);


    pen.setColor(colour);
    pen.setWidth(pen_width);
    pic.setPen(pen);
    scene->clear();
    Matrix ToRotate;
    ToRotate.Arr[0][0] = ToRotate.Arr[1][1] = cos(angle);
    ToRotate.Arr[0][1] = (-1) * sin(angle);
    ToRotate.Arr[1][0] = sin(angle);

    QPointF shift(shift_x, shift_y);
    QPointF center(width() / 2.0 - 50, height() / 2.0);
    QPointF first = center + shift;
    double temp;

    for (double t = step; t < end; t += step)
    {

        QPointF second(a * sin(2*t) * cos(t), a * sin(2*t) * sin(t));
        temp = second.y();
        second.setY((- 1) * temp);
        second *= K;
        second = ToRotate * second;
        second += center;
        second += shift;
        path.moveTo(first.x(), first.y());
        path.lineTo(second.x(), second.y());
        scene->addPath(path);

      //  pic.drawLine(first, second);
        first = second;
    }
}



void DrawLine::on_Draw_clicked()
{
        step = ui->stepBox->value();
        quarter = ui->quarterdoubleBox->value();
        colour = ui->colourBox->currentText();
        shift_x = ui->RightLeftBox->value();
        shift_y = (-1)* ui->UpDownBox->value();
        angle = ui->RotateBox->value();
        pen_width = ui->WidthBox->value();
        repaint();
}
