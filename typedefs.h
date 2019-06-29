#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <QStringList>
#include <QUrl>
#include <QFileInfo>
#include <QTextEdit>
#include <QMediaPlayer>

//plugin dir
typedef QStringList (*typedef_dir_scan)(const QString);
typedef QStringList (*typedef_dir_scan_url)(const QUrl);
typedef QString (*typedef_dir_open_dialog)(const QString,const int);
typedef QString (*typedef_dir_open_save_dialog)(const QString);
//plugin url
typedef QUrl (*typedef_url_parce)(const QString);
typedef QFileInfo (*typedef_url_info)(const QString);
//plugin help
typedef void (*typedef_help_show)(void);
//plugin readme
typedef void (*typedef_readme_create)(const QString);
//plugin playlist
typedef void (*typedef_playlist_save)(const QStringList,const QString,const int);
typedef QStringList (*typedef_playlist_read)(const QString,const int);
//plugin media_info
typedef void (*typedef_media_info_write_metadata)(QTextEdit *,QMediaPlayer *);
typedef void (*typedef_media_info_write_media_info)(QTextEdit *,QMediaPlayer *);
typedef void (*typedef_media_info_write_media_error)(QTextEdit *,QMediaPlayer *);
typedef QString (*typedef_media_info_get_text_list_item)(const int,QMediaPlayer *);

#endif // TYPEDEFS_H
