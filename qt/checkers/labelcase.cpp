#include "labelcase.h"

LabelCase::LabelCase(int x, int y) : _x(x), _y(y)
{
}

void 	mouseReleaseEvent ( QMouseEvent * ev ){
    emit cliked(_x, _y);
}
