#include<QFileInfo>
#include<QObject>
#include "player2_media_info.h"

void write_metadata(QTextEdit *text_edit,QMediaPlayer *player){
	if(player->isMetaDataAvailable())
		for (QString str : player->availableMetaData())
			text_edit->append(QString("%1: %2").arg(str).arg(player->metaData(str).toString()));
}

void write_media_info(QTextEdit *text_edit, QMediaPlayer *player){
	text_edit->append(QString(QObject::tr("audio length: %1:%2")).arg((player->duration()/1000)/60)
							   .arg((player->duration()/1000)%60));
	QString path=player->currentMedia().canonicalUrl().toLocalFile();
	QFileInfo info(path);
	text_edit->append(QString(QObject::tr("audio size: %1")).arg(info.size()));
	text_edit->append(QString(QObject::tr("url: %1")).arg(path));
}

void write_media_error(QTextEdit *text_edit,QMediaPlayer *player){
	QString error_str=player->errorString();
	if(!error_str.isEmpty())
		text_edit->append(QString(QObject::tr("error: %1")).arg(error_str));
}

QString get_text_list_item(const int index, QMediaPlayer *player){
	QString current_music_artist=player->metaData("AlbumArtist").toString();
	QString current_music_title=player->metaData("Title").toString();
	if(!current_music_artist.isEmpty()&&!current_music_title.isEmpty()) {
		return QString("%1  %2-%3").arg(index).arg(current_music_artist,current_music_title);
	}else{
		return "";
	}
}
