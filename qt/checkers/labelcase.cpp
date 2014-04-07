#include "labelcase.h"


LabelCase::LabelCase(int x, int y) : _x(x), _y(y)
{}

LabelCase::LabelCase(){}

void 	LabelCase::mouseReleaseEvent ( QMouseEvent * ev ){
    emit clicked(_x, _y);
    ev->accept();
    //qDebug() << "clic x : " << _x << ", y : " << _y << endl;
}
