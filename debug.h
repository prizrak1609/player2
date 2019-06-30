#ifndef DEBUG_H
#define DEBUG_H

#include "defines.h"

#include <QDebug>

static void operator "" _debug(const char* text, std::size_t size) {
    Q_UNUSED(size)
    qDebug() << text;
}

#define D qDebug()

#endif // DEBUG_H
