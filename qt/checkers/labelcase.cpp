#include "labelcase.h"


LabelCase::LabelCase(int x, int y) : _x(x), _y(y)
{}

LabelCase::LabelCase(){}

void 	LabelCase::mouseReleaseEvent ( QMouseEvent * ev ){
    if (ev->button() == Qt::LeftButton){
        emit clicked(_x, _y);
        ev->accept();
        //qDebug() << "clic x : " << _x << ", y : " << _y << endl;
    }else emit deselect();
}
