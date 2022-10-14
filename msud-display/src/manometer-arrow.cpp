#include "manometer-arrow.h"

#include <QPainter>
#include <qmath.h>



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
ManometerArrow::ManometerArrow(QSize _size, int maxValScale, QWidget *parent)
    : QLabel(parent)
    , maxValScale_(maxValScale)
    , oldVal1_line_(-1)
    , oldVal2_arrow_(-1)
{
    this->resize(_size);
    this->setStyleSheet("border: 1px solid red");


    // 416 - диаметр круга
    QRect rect(-53, 10,
               416, 416 + 10);

    w_2_ = rect.x() + rect.width()/2.0;
    h_2_ = rect.y() + rect.height()/2.0;

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ManometerArrow::setVals(int val1_line, int val2_arrow)
{
    if (val1_line < 0) val1_line = 0;
    if (val2_arrow < 0) val2_arrow = 0;
    if (val1_line > maxValScale_) val1_line = maxValScale_;
    if (val2_arrow > maxValScale_) val2_arrow = maxValScale_;


    if ((oldVal1_line_ == val1_line) && (oldVal2_arrow_ == val2_arrow))
        return;



    drawArrow_(val1_line, val2_arrow);

    oldVal1_line_ = val1_line;
    oldVal2_arrow_ = val2_arrow;
}



//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ManometerArrow::drawArrow_(int val1_line, int val2_arrow)
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);


    double angleArcEnd = 46.7;
    double arcSplitLength = 273.3;


    double fooAngleDegrees1 = (360.0 - angleArcEnd) - (maxValScale_ - val1_line)*(360.0-arcSplitLength)/maxValScale_;
    double angle1 = qDegreesToRadians(fooAngleDegrees1);
    double fooAngleDegrees2 = (360.0 - angleArcEnd) - (maxValScale_ - val2_arrow)*(360.0-arcSplitLength)/maxValScale_;
    double angle2 = qDegreesToRadians(fooAngleDegrees2);
    double fooAngle = qDegreesToRadians(90.0);


    double r = 205.0;   // радиус (длина) стрелки
    double ht = 15.0;   // высота треугольника стрелки
    double bt = 5.0;    // длина основания треугольника


    //
    paint.setPen(QPen(Qt::red, 3, Qt::SolidLine));
    paint.drawLine(w_2_ + (r)*cos(angle1),
                   h_2_ + (r)*sin(angle1),
                   w_2_,
                   h_2_);



    //
    paint.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    paint.setBrush(Qt::black);
    paint.drawLine(w_2_ + (r - 10)*cos(angle2),
                   h_2_ + (r - 10)*sin(angle2),
                   w_2_,
                   h_2_);

    QPolygonF triangle;
    triangle << QPointF( w_2_ + (r)*cos(angle2),
                         h_2_ + (r)*sin(angle2) )
             << QPointF( w_2_ + (r - ht)*cos(angle2) + bt*cos(angle2+fooAngle),
                         h_2_ + (r - ht)*sin(angle2) + bt*sin(angle2+fooAngle) )
             << QPointF( w_2_ + (r - ht)*cos(angle2) + bt*cos(angle2-fooAngle),
                         h_2_ + (r - ht)*sin(angle2) + bt*sin(angle2-fooAngle) );
    paint.drawPolygon(triangle);



    paint.end();
    this->setPixmap(pix);
}
