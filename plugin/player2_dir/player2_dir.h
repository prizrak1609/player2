#ifndef PLAYER2_DIR_H
#define PLAYER2_DIR_H

#include<QString>
#include<QUrl>
#include<QStringList>

extern "C"{
QStringList scan(const QString patch_dir);
QStringList scan_url(const QUrl patch_dir);
QString open_dialog(const QString path, const int type);
QString open_save_dialog(const QString path);
}

#endif // PLAYER2_DIR_H
