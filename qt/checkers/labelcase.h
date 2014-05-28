#ifndef LABELCASE_H
#define LABELCASE_H

#include "include.h"

class LabelCase : public QLabel
{
    Q_OBJECT

private:
    int _x;
    int _y;

public:
    LabelCase(int x, int y);
    LabelCase();

public slots :
    void mouseReleaseEvent(QMouseEvent * ev);

signals:
    void clicked(int, int);
    void deselect();
};
#else
class LabelCase ;
#endif // LABELCASE_H
