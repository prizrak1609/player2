#ifndef PLAYER2_MEDIA_INFO_H
#define PLAYER2_MEDIA_INFO_H
#include<QMediaPlayer>
#include<QTextEdit>
#include<QString>

extern "C"{
void write_metadata(QTextEdit *text_edit,QMediaPlayer *player);
void write_media_info(QTextEdit *text_edit,QMediaPlayer *player);
void write_media_error(QTextEdit *text_edit,QMediaPlayer *player);
QString get_text_list_item(const int index,QMediaPlayer *player);
}

#endif // PLAYER2_MEDIA_INFO_H
