#ifndef PLAYER2_URL_H
#define PLAYER2_URL_H

#include<QUrl>
#include<QFileInfo>

extern "C"{
QUrl parce(const QString url);
QFileInfo info(const QString url);
}

#endif // PLAYER2_URL_H
