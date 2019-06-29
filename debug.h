#ifndef DEBUG_H
#define DEBUG_H
#include<QDebug>

void debug_(QString text) {
    qDebug()<<text;
}
#endif // DEBUG_H
