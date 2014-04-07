#ifndef LABELCASE_H
#define LABELCASE_H

class LabelCase :
        public QLabel
{

private:
    int _x;
    int _y;

public:
    LabelCase(int x, int y);

signals:
    void cliked(int, int);
};

#endif // LABELCASE_H
