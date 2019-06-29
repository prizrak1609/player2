#ifndef PLAYER2_PLAYLIST_H
#define PLAYER2_PLAYLIST_H

#include<QStringList>
#include<QString>

extern "C"{
void save(const QStringList list,const QString path,const int type);
QStringList read(const QString path,const int type);
}

#endif // PLAYER2_PLAYLIST_H
