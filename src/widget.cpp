#include "widget.h"

#include <math.h>
#include <QEvent>
#include <QMessageBox>
#include <QStyle>
#include <QLocale>
#include <QDir>
#include <QFileInfoList>
#include <QMediaMetaData>
#include <QMimeData>
#include <QNetworkAccessManager>
#include <QMessageBox>

#include "settings/SettingsKey.h"
//#include"src/qglobalshortcut.h"
#include "defines.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);

    timer = new QTimer();
    timer_check_settings = new QTimer();

    font_button = new QFont();
    font_list_widget = new QFont();
    font_property_media = new QFont();

    mediaPlayer = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);

    clipboard = QApplication::clipboard();

    player2_dir = new QLibrary("player2_dir");
    player2_url = new QLibrary("player2_url");
    player2_help = new QLibrary("player2_help");
    player2_readme = new QLibrary("player2_readme");
    player2_playlist = new QLibrary("player2_playlist");
    player2_media_info = new QLibrary("player2_media_info");

    file_time_change_old = "";

    setAcceptDrops(true);
}

void Widget::dropEvent(QDropEvent *drop) {
    const QMimeData *mime=drop->mimeData();

    if(mime->hasUrls()) {
    "enter drop event "_debug;

        for (QUrl _url : mime->urls()) {
            D << QString("add url %1").arg(_url.path());

            QFileInfo info {_url.path()};
            if (info.isDir()) {
                playlist_list+=dir_scan_url(_url);
            } else {
                playlist_list+=_url.toString();
            }
        }
        updatePlayList(PLAYLIST_OLREADY_ADDED);
        showWidgetWithSlider();
    }
    drop->acceptProposedAction();
}

void Widget::dragEnterEvent(QDragEnterEvent *event) {
    "drag enter event "_debug;

    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

/* /CREATE WIDGET */
/**
 * @brief Widget::create_widget
 */
void Widget::create_widget() {
    "create window"_debug;

    timer->setInterval(settings.UPDATE.info_music.toInt());
    timer_check_settings->setInterval(500);//TODO add to settings
    //LOAD PLUGINS
    player2_dir->load();

    D << QString("load plugin %1: %2").arg("player2_dir", player2_dir->isLoaded() ? "true" : "false");

    player2_url->load();

    D << QString("load plugin %1: %2").arg("player2_url", player2_url->isLoaded() ? "true" : "false");

    player2_help->load();

    D << QString("load plugin %1: %2").arg("player2_help", player2_help->isLoaded() ? "true" : "false");

    player2_readme->load();

    D << QString("load plugin %1: %2").arg("player2_readme", player2_readme->isLoaded() ? "true" : "false");

    player2_playlist->load();

    D << QString("load plugin %1: %2").arg("player2_playlist", player2_playlist->isLoaded() ? "true" : "false");

    player2_media_info->load();

    D << QString("load plugin %1: %2").arg("player2_media_info", player2_media_info->isLoaded() ? "true" : "false");

    //plugin dir
    dir_scan = (typedef_dir_scan)player2_dir->resolve("scan");
    dir_scan_url = (typedef_dir_scan_url)player2_dir->resolve("scan_url");
    dir_open_dialog = (typedef_dir_open_dialog)player2_dir->resolve("open_dialog");
    dir_open_save_dialog = (typedef_dir_open_save_dialog)player2_dir->resolve("open_save_dialog");
    //plugin url
    url_info = (typedef_url_info)player2_url->resolve("info");
    url_parce = (typedef_url_parce)player2_url->resolve("parce");
    //plugin help
    help_show = (typedef_help_show)player2_help->resolve("show");
    //plugin readme
    readme_create = (typedef_readme_create)player2_readme->resolve("create");
    //plugin playlist
    playlist_save = (typedef_playlist_save)player2_playlist->resolve("save");
    playlist_read = (typedef_playlist_read)player2_playlist->resolve("read");
    //plugin media_info
    media_info_write_metadata = (typedef_media_info_write_metadata)player2_media_info->resolve("write_metadata");
    media_info_write_media_info = (typedef_media_info_write_media_info)player2_media_info->resolve("write_media_info");
    media_info_write_media_error = (typedef_media_info_write_media_error)player2_media_info->resolve("write_media_error");
    media_info_get_text_list_item = (typedef_media_info_get_text_list_item)player2_media_info->resolve("get_text_list_item");
    //END LOAD PLUGINS

    readme_create(settings.SETTINGS_FILE.path);

    this->setWindowIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    this->setStyleSheet("background-color:" + settings.WIDGET.background_color);

    font_button->setFamily(settings.BUTTON.font_family);
    font_button->setPointSize(settings.BUTTON.font_size.toInt());
    font_button->setWeight(settings.BUTTON.font_weight.toInt());
    font_list_widget->setFamily(settings.LIST.font_family);
    font_list_widget->setPointSize(settings.LIST.font_size.toInt());
    font_list_widget->setWeight(settings.LIST.font_weight.toInt());
    font_property_media->setFamily(settings.PROPERTY_MEDIA.font_family);
    font_property_media->setPointSize(settings.PROPERTY_MEDIA.font_size.toInt());
    font_property_media->setWeight(settings.PROPERTY_MEDIA.font_weight.toInt());

    ui->listWidget->setFont(*font_list_widget);
    ui->property_media->setFont(*font_property_media);
    ui->property_media->setTextColor(settings.PROPERTY_MEDIA.text_color);
    ui->media_info->setFont(*font_button);
    ui->musicButton->setFont(*font_button);
    ui->playlistCheck->setFont(*font_button);
    ui->exitButton->setFont(*font_button);
    //	ui->current_pos_media->setFont(*font_property_media);//TODO create font
    ui->current_pos_media->setStyleSheet("color:" + settings.PROPERTY_MEDIA.text_color +
                                         "; border:1px " + settings.SLIDER.handle_border_style +
                                         " blue; border-radius: " + settings.SLIDER.next_radius + "px;");
    ui->media_buffer_status->setStyleSheet("color:" + settings.PROPERTY_MEDIA.text_color +
                                           "; border:1px " + settings.SLIDER.handle_border_style +
                                           " blue; border-radius: " + settings.SLIDER.next_radius + "px;");
    ui->media_buffer_status->setGeometry(ui->slider->x()+ui->slider->width() / 2 - ui->media_buffer_status->width() / 2,
                                         ui->slider->y()+ui->slider->height() - 8,
                                         ui->media_buffer_status->width() + 5,
                                         ui->media_buffer_status->height());

    setTray();
    setShortcut();
    setButtons();
    setSize(settings.WIDGET.begin_width.toInt(),settings.WIDGET.begin_height.toInt());

    musicPlay = false;
    show_widget_with_slider = true;
    musicNext = true;
    update_media_info_i = 0;
    index = 0;
    oldPositionSlider = 0;

    ui->playlistCheck->hide();
    ui->media_info->hide();
    ui->slider->hide();

    connect(timer, SIGNAL(timeout()), this, SLOT(update_media_info()));
    connect(timer_check_settings, SIGNAL(timeout()), this, SLOT(check_settings()));

    timer_check_settings->start();
}

void Widget::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);

    switch (e->type()) {
    case QEvent::LanguageChange: ui->retranslateUi(this); break;
    case QEvent::WindowStateChange: /*this->hide();*/ break;
    default: break;
    }
}

void Widget::check_settings() {
    QFileInfo info {settings.FILE.path};

    QString last_modified = info.lastModified().toString();

    if (file_time_change_old != last_modified) {
        file_time_change_old = last_modified;

        settings.re_read();

        "start apply settings"_debug;

        timer->setInterval(settings.UPDATE.info_music.toInt());

        "recreate readme"_debug;

        readme_create(settings.SETTINGS_FILE.path);

        "set style sheet"_debug;

        this->setStyleSheet("background-color:" + settings.WIDGET.background_color);

        "set font button"_debug;

        font_button->setFamily(settings.BUTTON.font_family);
        font_button->setPointSize(settings.BUTTON.font_size.toInt());
        font_button->setWeight(settings.BUTTON.font_weight.toInt());

        "set font list"_debug;

        font_list_widget->setFamily(settings.LIST.font_family);
        font_list_widget->setPointSize(settings.LIST.font_size.toInt());
        font_list_widget->setWeight(settings.LIST.font_weight.toInt());

        "set font property media"_debug;

        font_property_media->setFamily(settings.PROPERTY_MEDIA.font_family);
        font_property_media->setPointSize(settings.PROPERTY_MEDIA.font_size.toInt());
        font_property_media->setWeight(settings.PROPERTY_MEDIA.font_weight.toInt());

        ui->property_media->setTextColor(settings.PROPERTY_MEDIA.text_color);

        ui->current_pos_media->setStyleSheet("color:" + settings.PROPERTY_MEDIA.text_color +
                                             "; border:1px " + settings.SLIDER.handle_border_style +
                                             " blue; border-radius: " + settings.SLIDER.next_radius + "px;");
        ui->media_buffer_status->setStyleSheet("color:" + settings.PROPERTY_MEDIA.text_color +
                                               "; border:1px " + settings.SLIDER.handle_border_style +
                                               " blue; border-radius: " + settings.SLIDER.next_radius + "px;");
        ui->slider->setStyleSheet(
                    "QSlider::groove{ border: " + settings.SLIDER.groove_border_size + "px " +
                    settings.SLIDER.groove_border_style + " " +
                    settings.SLIDER.groove_border_color + ";" +
                    " height: " + settings.SLIDER.groove_height + "px; }" +
                    " QSlider::handle{ background: " + settings.SLIDER.handle_background + ";" +
                    " border: " + settings.SLIDER.handle_border_size + "px " +
                    settings.SLIDER.handle_border_style + " " +
                    settings.SLIDER.handle_border_color + ";" +
                    " width: " + settings.SLIDER.handle_width + "px;" +
                    " border-radius: " + settings.SLIDER.next_radius + "px; }" +
                    " QSlider::add-page{ background: " + settings.SLIDER.next_background + ";" +
                    " border-radius: " + settings.SLIDER.next_radius + "px; }" +
                    " QSlider::sub-page{ background: " + settings.SLIDER.prev_background + ";" +
                    " border-radius: " + settings.SLIDER.prev_radius + "px; }"
                    );

        ui->listWidget->setFixedHeight(settings.PLAYLIST.check_widgetHeight.toInt()-ui->listWidget->y() - 5);
        ui->listWidget->item(index)->setBackground(QColor(settings.LIST.cur_mus_background_color));

        ui->property_media->setFixedHeight(settings.PLAYLIST.check_widgetHeight.toInt()-ui->property_media->y()-5);
        ui->property_media->setFixedWidth(settings.WIDGET.press_info_but_width.toInt()-ui->property_media->x()-5);

        ui->musicButton->setStyleSheet(QString("border-radius: %1px; background-color: %2; color: %3")
                                       .arg(settings.BUTTON.border_radius, settings.BUTTON.background_color,
                                            settings.BUTTON.text_color));
        ui->exitButton->setStyleSheet(QString("border-radius: %1px; background-color: %2; color: %3")
                                      .arg(settings.BUTTON.border_radius, settings.BUTTON.background_color,
                                           settings.BUTTON.text_color));

        "end apply settings"_debug;
    }
}

/**
 * @brief Widget::showWidgetWithSlider
 */
void Widget::showWidgetWithSlider() {
    if (show_widget_with_slider) {
        show_widget_with_slider = false;

        setSize(settings.WIDGET.press_mus_but_width.toInt(),
                settings.PLAYLIST.not_check_widgetHeight.toInt());

        ui->slider->setGeometry(ui->musicButton->x(), ui->musicButton->y()+ui->musicButton->height() + 10,
                                this->width() - 20, 20);

        ui->slider->setStyleSheet(
                    "QSlider::groove{ border: " + settings.SLIDER.groove_border_size + "px "+
                    settings.SLIDER.groove_border_style + " " +
                    settings.SLIDER.groove_border_color + ";" +
                    " height: " + settings.SLIDER.groove_height + "px; }" +
                    " QSlider::handle{ background: " + settings.SLIDER.handle_background + ";" +
                    " border: " + settings.SLIDER.handle_border_size + "px " +
                    settings.SLIDER.handle_border_style + " " +
                    settings.SLIDER.handle_border_color + ";" +
                    " width: " + settings.SLIDER.handle_width + "px;" +
                    " border-radius: " + settings.SLIDER.next_radius + "px; }" +
                    " QSlider::add-page{ background: " + settings.SLIDER.next_background + ";" +
                    " border-radius: " + settings.SLIDER.next_radius + "px; }" +
                    " QSlider::sub-page{ background: " + settings.SLIDER.prev_background + ";" +
                    " border-radius: " + settings.SLIDER.prev_radius + "px; }"
                    );
        ui->media_info->setGeometry(ui->musicButton->x() + ui->musicButton->width() + 20, ui->musicButton->y(),
                                    ui->musicButton->width(), ui->musicButton->height());
        ui->playlistCheck->setGeometry(ui->media_info->x() + ui->media_info->width() + 20, ui->media_info->y(),
                                       ui->media_info->width(), ui->media_info->height());
        ui->exitButton->setGeometry(ui->playlistCheck->x() + ui->playlistCheck->width() + 20, ui->musicButton->y(),
                                    ui->musicButton->width(), ui->musicButton->height());
        file_info = new QFileInfo(playlist_list[index]);

        this->setWindowTitle(QString::number(index+1)+ " "+file_info->fileName());

        ui->listWidget->setFixedHeight(settings.PLAYLIST.check_widgetHeight.toInt()-ui->listWidget->y()-5);
        ui->listWidget->item(index)->setBackground(QColor(settings.LIST.cur_mus_background_color));
        ui->listWidget->item(index)->setForeground(QColor("lime"));                                 /* / TODO add to settings */

        ui->property_media->setFixedHeight(settings.PLAYLIST.check_widgetHeight.toInt() - ui->property_media->y() - 5);
        ui->property_media->setFixedWidth(settings.WIDGET.press_info_but_width.toInt() - ui->property_media->x() - 5);

        ui->playlistCheck->setStyleSheet("color: lime");                                 /* /TODO add to settings */
        ui->media_info->setStyleSheet("color: lime");                                 /* /TODO add to settings */
        ui->playlistCheck->showNormal();
        ui->slider->showNormal();
        ui->media_info->showNormal();
        ui->musicButton->setText(tr("add music"));

        playlist->setCurrentIndex(index);

        mediaPlayer->setPlaylist(playlist);
        mediaPlayer->setVolume(100);//TODO add to settings and add slider |maybe
        mediaPlayer->play();
#ifdef MUTE
        mediaPlayer->setMuted(true);
#endif
        timer->start();

        ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        tray->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaPlay)));

        musicClicked = false;
        musicPaused = false;

        connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(seek(qint64)));
        connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(duration(qint64)));
        connect(ui->slider, SIGNAL(sliderMoved(int)), this, SLOT(changeaudio(int)));
        connect(ui->slider, SIGNAL(sliderReleased()), this, SLOT(slider_released()));
        connect(ui->slider, SIGNAL(valueChanged(int)), this, SLOT(slider_pressed()));
        connect(mediaPlayer, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(nexttitle(QMediaContent)));
        connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(clickedAudio(QListWidgetItem*)));

        "show widget with slider"_debug;
    }
}

/* /OPEN MUSIC */
/**
 * @brief Widget::on_musicButton_clicked
 */
void Widget::on_musicButton_clicked() {
    if (updatePlayList(PLAYLIST_ADD_OTHER_FILE)) {
        showWidgetWithSlider();
    }
}

/* /ADD FILE TO PLAYLIST */
/**
 * @brief Widget::updatePlayList
 * @param add_path
 * @return
 */
bool Widget::updatePlayList(const int add_path) {
    switch (add_path) {
    case PLAYLIST_ADD_NETWORK:
        playlist_list += network_music_adress->toPlainText().trimmed();

        D << QString("add network music %1").arg(network_music_adress->toPlainText().trimmed());
        break;
    case PLAYLIST_ADD_DIRECTORY:
        playlist_list += dir_scan(dir_patch);

        D << QString("widget: add directory %1").arg(dir_patch.trimmed());
        break;
    case PLAYLIST_ADD_OTHER_FILE:
        playlist_list += file_dialog->getOpenFileNames(nullptr, tr("Open"), settings.FILE.path.trimmed());

        "add file music"_debug;
        break;
    case PLAYLIST_OLREADY_ADDED: break;
    default: break;
    }
    if (playlistChange()) {
        for (int i = playlistCount; i<playlistLength; i++) {
            playlist->addMedia(url_parce(playlist_list[i].trimmed()));

            ui->listWidget->addItem(QString("%1  %2").arg(++playlistCount).arg(url_info(playlist_list[i].trimmed()).fileName().trimmed()));

            ui->listWidget->item(i)->setForeground(QColor("lime")); /* / TODO add to settings */
        }
        settings.FILE.path = url_info(playlist_list.last()).dir().absolutePath().trimmed();

        "update playlist"_debug;
        return true;
    }
    return false;
}

/* /TEST CHANGE PLAYLIST */
/**
 * @brief Widget::playlistChange
 * @return
 */
bool Widget::playlistChange() {

    "check playlist change"_debug;

    playlistCount = ui->listWidget->count();
    playlistLength = playlist_list.length();

    bool compare = playlistLength != playlistCount;

    D << QString("return %1").arg(compare);

    return compare;
}

void Widget::setSize(int width, int height) {
    Q_UNUSED(width)
    Q_UNUSED(height)
    //	this->setFixedSize(width,height);
}

/* /OPEN DIALOG CHOOSE DIR, UPDATE PLAYLIST, SHOW WIDGET WITH SLIDER */
/**
 * @brief Widget::open_dir
 */
void Widget::open_dir() {
    dir_patch = dir_open_dialog(settings.FILE.path, DIR_OPEN_DIALOG_DIRS_ONLY).trimmed();

    if (!dir_patch.isEmpty() || !dir_patch.isNull()) {
        settings.FILE.path = dir_patch;
        updatePlayList(PLAYLIST_ADD_DIRECTORY);
        showWidgetWithSlider();
    }
}

/* /CHANGE TITLE WHEN MUSIC CHANGED */
/**
 * @brief Widget::nexttitle
 * @param media
 */
void Widget::nexttitle(QMediaContent media) {
    if (musicClicked) {
        file_info = new QFileInfo(playlist_list[index].trimmed());
        musicClicked = false;
    } else {
        ui->listWidget->item(index)->setBackground(QColor(settings.LIST.prev_mus_background_color));
        ui->listWidget->item(index)->setForeground(QColor("lime")); /* / TODO add to settings */

        file_info = new QFileInfo(media.canonicalUrl().path().trimmed());

        musicNext ? index++ : index--;
        musicNext = true;

        if (index > playlistCount - 1) {
            disconnect(mediaPlayer, SIGNAL(currentMediaChanged(QMediaContent)),
                       this, SLOT(nexttitle(QMediaContent)));

            index = 0;

            playlist->setCurrentIndex(index);

            file_info = new QFileInfo(playlist_list[index].trimmed());

            connect(mediaPlayer, SIGNAL(currentMediaChanged(QMediaContent)),
                    this, SLOT(nexttitle(QMediaContent)));
        }
        if (index < 0) {
            disconnect(mediaPlayer, SIGNAL(currentMediaChanged(QMediaContent)),
                       this, SLOT(nexttitle(QMediaContent)));

            index = playlistCount - 1;

            playlist->setCurrentIndex(index);

            file_info = new QFileInfo(playlist_list[index].trimmed());

            connect(mediaPlayer, SIGNAL(currentMediaChanged(QMediaContent)),
                    this, SLOT(nexttitle(QMediaContent)));
        }
        ui->listWidget->item(index)->setBackground(QColor(settings.LIST.cur_mus_background_color));
        ui->listWidget->item(index)->setForeground(QColor("lime")); /* / TODO add to settings */
    }
    this->setWindowTitle(ui->listWidget->item(index)->text().trimmed());
}

/* /NEXT MUSIC WHEN PRESS KEY N */
/**
 * @brief Widget::next_music
 */
void Widget::next_music() {
    ui->listWidget->item(index)->setBackground(QColor(settings.LIST.prev_mus_background_color));
    ui->listWidget->item(index)->setForeground(QColor("lime"));                 /* / TODO add to settings */

    playlist->setCurrentIndex(index + 1);

    ui->listWidget->item(index)->setBackground(QColor(settings.LIST.cur_mus_background_color));
    ui->listWidget->item(index)->setForeground(QColor("lime"));                 /* / TODO add to settings */

    ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    tray->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaPlay)));

    update_media_info_i = 0;
}

/* /PREVIOUS MUSIC */
/**
 * @brief Widget::previus_music
 */
void Widget::previus_music(){
    ui->listWidget->item(index)->setBackground(QColor(settings.LIST.prev_mus_background_color));
    ui->listWidget->item(index)->setForeground(QColor("lime"));                 /* / TODO add to settings */

    musicNext = false;

    playlist->setCurrentIndex(index-1);

    ui->listWidget->item(index)->setBackground(QColor(settings.LIST.cur_mus_background_color));
    ui->listWidget->item(index)->setForeground(QColor("lime"));                 /* / TODO add to settings */

    ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    tray->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaPlay)));

    update_media_info_i = 0;
}

/* /OPEN NETWORK MUSIC */
/**
 * @brief Widget::open_network_music
 */
void Widget::open_network_music() { /* TODO MOVE TO QML */
    network_music = new QWidget();
    network_music_label = new QLabel(tr("paste network adress"), network_music);
    network_music_adress = new QTextEdit(network_music);
    get_network_adress = new QPushButton(tr("get network music"), network_music);
    network_music_label->setGeometry(0, 0, 200, 30);
    network_music_adress->setGeometry(0, network_music_label->y() + network_music_label->height(),
                                      network_music_label->width(), 100);
    get_network_adress->setGeometry(0, network_music_adress->y() + network_music_adress->height() + 5,
                                    network_music_adress->width(), network_music_label->height());
    network_music->setFixedSize(network_music_label->width(),
                                get_network_adress->y() + get_network_adress->height() + 5);
    network_music->show();
    connect(get_network_adress, SIGNAL(clicked()), this, SLOT(add_network_music_to_playlist()));

    "open network music"_debug;
}

/* /ADD NETWORK MUSIC TO PLAY LIST */
/**
 * @brief Widget::add_network_music_to_playlist
 */
void Widget::add_network_music_to_playlist() {
    updatePlayList(PLAYLIST_ADD_NETWORK);
    showWidgetWithSlider();
    disconnect(get_network_adress, SIGNAL(clicked()), this, SLOT(add_network_music_to_playlist()));
    network_music->close();
}

/* /CHANGE MUSIC WHEN CLICKED */
/**
 * @brief Widget::clickedAudio
 * @param item
 */
void Widget::clickedAudio(QListWidgetItem *item) {
    musicClicked = true;

    ui->listWidget->item(index)->setBackground(QColor(settings.LIST.prev_mus_background_color));
    ui->listWidget->item(index)->setForeground(QColor("lime"));                 /* / TODO add to settings */

    mediaPlayer->stop();

    for (int i = 0; i<playlistCount; i++) {
        if (ui->listWidget->item(i)->text() == item->text()) {
            index = i;
        }
    }
    playlist->setCurrentIndex(index);

    ui->listWidget->item(index)->setBackground(QColor(settings.LIST.cur_mus_background_color));
    ui->listWidget->item(index)->setForeground(QColor("lime"));                 /* / TODO add to settings */

    musicPaused = false;
    mediaPlayer->play();

    ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    tray->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaPlay)));

    update_media_info_i = 0;
}

/* /STEP PLAY MUSIC */
/**
 * @brief Widget::duration
 * @param i
 */
void Widget::duration(qint64 i) {
    ui->slider->setRange(0, i);
}

/* /VALUE MUSIC LOST */
/**
 * @brief Widget::seek
 * @param i
 */
void Widget::seek(qint64 i) {
    ui->slider->setValue(i);

    int temp = i - ui->slider->minimum();

    int sliderRange  =  ui->slider->maximum() - ui->slider->minimum();
    float temp1 = (float)temp / (float)sliderRange;
    float coord = floor(temp1 * ui->slider->width());

    if (coord+ui->current_pos_media->width()>this->width()) {
        coord = this->width() - ui->current_pos_media->width();
    }

    ui->current_pos_media->setText(QString("%1:%2").arg((mediaPlayer->position() / 1000) / 60)
                                   .arg((mediaPlayer->position() / 1000) % 60));
    ui->current_pos_media->setGeometry(coord, ui->slider->y() - 13, 41, 16);//TODO add to settings or const
}

/* /PLAY PAUSE MUSIC */
/**
 * @brief Widget::play_pause
 */
void Widget::play_pause() {
    if (musicPlay) {
        if (musicPaused) {
            mediaPlayer->play();

            timer->start(settings.UPDATE.info_music.toInt());

            musicPaused = false;

            ui->musicButton->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaPlay)));
            tray->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaPlay)));
        } else {
            timer->stop();
            mediaPlayer->pause();

            musicPaused = true;

            ui->musicButton->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaPause)));
            tray->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaPause)));
        }
    }
}

/* /WHEN SLIDER MOVE CHANGE VALUE AUDIO */
/**
 * @brief Widget::changeaudio
 * @param i
 */
void Widget::changeaudio(int i) {
    mediaPlayer->setPosition(i);

    if (oldPositionSlider<i) {
        ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
        tray->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaSeekForward)));
    } else {
        ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
        tray->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward)));
    }
    oldPositionSlider = i;
}

/* /TRAY ICON ACTIVITY */
/**
 * @brief Widget::click_tray
 * @param activation
 */
void Widget::click_tray(QSystemTrayIcon::ActivationReason activation){
    switch (activation) {
    case QSystemTrayIcon::Trigger: this->isVisible() ? this->hide() : this->showNormal(); break;
    case QSystemTrayIcon::MiddleClick: qApp->exit(); break;
    case QSystemTrayIcon::Unknown: case QSystemTrayIcon::DoubleClick: break;
    }
}

/* /TRAY MENU ACTION HELP */
/**
 * @brief Widget::program_help
 */
void Widget::program_help() { /*? MAYBE DELETE */
    help_show();
}

/* /SET TRAY */
/**
 * @brief Widget::setTray
 */
void Widget::setTray() {
    tray = new QSystemTrayIcon();
    tray->setIcon(QIcon(style()->standardIcon(QStyle::SP_MediaVolume)));

    trayMenu = new QMenu();

    setActions();

    trayMenu->setStyleSheet(                 /* TODO move to settings */
                                             "QMenu {"
                                             "background-color: black;"
                                             "margin: 10px;"
                                             "}"
                                             "QMenu::item {"
                                             "padding: 2px 25px 2px 20px;"
                                             "border: 3px solid lime;"
                                             "border-radius:10px;"
                                             "color: #10791D;"
                                             "}"
                                             "QMenu::item:selected {"
                                             "border-color: darkblue;"
                                             "background: rgba(100, 100, 100, 150);"
                                             "color: lime;"
                                             "}"
                                             "QMenu::icon:checked {"
                                             "background: gray;"
                                             "border: 1px inset gray;"
                                             "color: #42BC51;"
                                             "}");
    tray->setContextMenu(trayMenu);
    tray->show();

    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(click_tray(QSystemTrayIcon::ActivationReason)));
}

/* /CREATE ACTIONS */
/**
 * @brief Widget::setActions
 */
void Widget::setActions() {
    showAction = new QAction(tr("show"),this);
    hideAction = new QAction(tr("hide"),this);
    helpAction = new QAction(tr("help"),this);
    quitAction = new QAction(tr("quit"),this);

    trayMenu->addAction(showAction);
    trayMenu->addAction(hideAction);
    trayMenu->addAction(helpAction);
    trayMenu->addAction(quitAction);

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(showAction, SIGNAL(triggered()), this, SLOT(show()));
    connect(hideAction, SIGNAL(triggered()), this, SLOT(hide()));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(program_help()));
}

void Widget::add_file_from_bufer() {
    "add after ctrl+v "_debug;

    const QMimeData *mime = clipboard->mimeData();

    if (mime->hasUrls()) {
        for (QUrl _url : mime->urls()) {

            D << QString(tr("add url %1")).arg(_url.path());

            QFileInfo info(_url.path());

            if (info.isDir()) {
                playlist_list += dir_scan_url(_url);
            } else {
                playlist_list += _url.toString();
            }
        }
        updatePlayList(PLAYLIST_OLREADY_ADDED);
        showWidgetWithSlider();
    }
}

void Widget::save_playlist(){
    int type = 1;//TODO add to settings(types of playlist files)
    QString path = dir_open_save_dialog("");//TODO add to settings playlist/save_path

    playlist_save(playlist_list, path, type);
}

void Widget::load_playlist(){
    int type = 1;//TODO add to settings(types of playlist files)
    QString path = dir_open_dialog("",DIR_OPEN_DIALOG_ALL_FILES);//TODO load from settings playlist/save_path

    if (!path.isNull() && !path.isEmpty()) {
        ui->listWidget->clear();
        playlist_list = playlist_read(path,type);
        updatePlayList(PLAYLIST_OLREADY_ADDED);
        showWidgetWithSlider();
    }
}

/* /SET SHORTCUT */
/**
 * @brief Widget::setShortcut
 */
void Widget::setShortcut() { /* TODO move to settings */
    shortcutClose = new QShortcut(QKeySequence("Q"),this);
    shortcutOpenFile = new QShortcut(QKeySequence("O"),this);
    shortcutHide = new QShortcut(QKeySequence(Qt::Key_Escape),this);
    shortcutPause = new QShortcut(QKeySequence("P"),this);
    shortcutHelp = new QShortcut(QKeySequence("H"),this);
    shortcutNextMusic = new QShortcut(QKeySequence("N"),this);
    shortcutOpenNetworkMusic = new QShortcut(QKeySequence("Ctrl+O"),this);
    shortcutPreviusMusic = new QShortcut(QKeySequence("Ctrl+P"),this);
    shortcutOpenDir = new QShortcut(QKeySequence("D"),this);
    shortcutAddFile = new QShortcut(QKeySequence("Ctrl+V"),this);
    shortcutSavePlaylist = new QShortcut(QKeySequence("Ctrl+S"),this);
    shortcutLoadPlaylist = new QShortcut(QKeySequence("Ctrl+L"),this);

    connect(shortcutClose, SIGNAL(activated()), qApp, SLOT(quit()));
    connect(shortcutOpenFile, SIGNAL(activated()), this, SLOT(on_musicButton_clicked()));
    connect(shortcutHide, SIGNAL(activated()), this, SLOT(hide()));
    connect(shortcutPause, SIGNAL(activated()), this, SLOT(play_pause()));
    connect(shortcutHelp, SIGNAL(activated()), this, SLOT(program_help()));
    connect(shortcutNextMusic, SIGNAL(activated()), this, SLOT(next_music()));
    connect(shortcutOpenNetworkMusic, SIGNAL(activated()), this, SLOT(open_network_music()));
    connect(shortcutPreviusMusic, SIGNAL(activated()), this, SLOT(previus_music()));
    connect(shortcutOpenDir, SIGNAL(activated()), this, SLOT(open_dir()));
    connect(shortcutAddFile, SIGNAL(activated()), this, SLOT(add_file_from_bufer()));
    connect(shortcutSavePlaylist, SIGNAL(activated()), this, SLOT(save_playlist()));
    connect(shortcutLoadPlaylist, SIGNAL(activated()), this, SLOT(load_playlist()));
}

/* /SET BUTTONS STYLE AND ICON */
/**
 * @brief Widget::setButtons
 */
void Widget::setButtons() {
    ui->musicButton->setStyleSheet(QString("border-radius:%1px;background-color: %2;color:%3")
                                   .arg(settings.BUTTON.border_radius, settings.BUTTON.background_color,
                                        settings.BUTTON.text_color));
    ui->exitButton->setStyleSheet(QString("border-radius:%1px;background-color: %2;color:%3")
                                  .arg(settings.BUTTON.border_radius, settings.BUTTON.background_color,
                                       settings.BUTTON.text_color));
    ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_DirClosedIcon));
}

/* /MUSIC BUTTON PRESSED */
/**
 * @brief Widget::on_musicButton_pressed
 */
void Widget::on_musicButton_pressed() {
    ui->musicButton->setStyleSheet(QString("border-radius:%1px;background-color: %2;color:%3")
                                   .arg(settings.BUTTON.border_radius, settings.BUTTON.background_pressed_color,
                                        settings.BUTTON.text_color));
    ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
}

/* /MUSIC BUTTON RELEASED */
/**
 * @brief Widget::on_musicButton_released
 */
void Widget::on_musicButton_released(){
    ui->musicButton->setStyleSheet(QString("border-radius:%1px;background-color: %2;color:%3")
                                   .arg(settings.BUTTON.border_radius, settings.BUTTON.background_released_color,
                                        settings.BUTTON.text_color));
    ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_DirClosedIcon));
}

/* /SETTINGS BUTTON PRESSED */
/**
 * @brief Widget::on_settingsButton_pressed
 */
void Widget::on_exitButton_pressed() {
    ui->exitButton->setStyleSheet("border-radius:" + settings.BUTTON.border_radius + "px;background-color: " +
                                  settings.BUTTON.background_pressed_color + ";color:" + settings.BUTTON.text_color);
}

/* /SETTINGS BUTTON RELEASED */
/**
 * @brief Widget::on_settingsButton_released
 */
void Widget::on_exitButton_released() {
    ui->exitButton->setStyleSheet("border-radius:" + settings.BUTTON.border_radius + "px;background-color: " +
                                  settings.BUTTON.background_released_color + ";color:" + settings.BUTTON.text_color);
    qApp->quit();
}

/* /SLIDER RELEASED */
/**
 * @brief Widget::slider_released
 */
void Widget::slider_released(){
    if(musicPlay) {
        ui->musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        tray->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

/* /SLIDER PRESSED */
/**
 * @brief Widget::slider_pressed
 */
void Widget::slider_pressed() { /* TODO (not mine) maybe optimize */
    Qt::MouseButtons btns = QApplication::mouseButtons();
    QPoint localMousePos = ui->slider->mapFromGlobal(QCursor::pos());

    bool clickOnSlider = (btns & Qt::LeftButton) &&
            (localMousePos.x() >= 0 && localMousePos.y() >= 0 &&
             localMousePos.x() < ui->slider->size().width() &&
             localMousePos.y() < ui->slider->size().height());

    if (clickOnSlider) {
        float posRatio = (float)localMousePos.x() / (float)ui->slider->width();
        int sliderRange = ui->slider->maximum() - ui->slider->minimum();
        int sliderPosUnderMouse = ui->slider->minimum() + sliderRange * posRatio;
        seek(sliderPosUnderMouse);
        mediaPlayer->setPosition(sliderPosUnderMouse);
    }
}

/* /END */
/**
 * @brief Widget::~Widget
 */
Widget::~Widget(){
    mediaPlayer->stop();

    "stop mediaPlayer"_debug;

    if (player2_dir->unload()) {
        "unload player2_dir"_debug;
    }
    if (player2_url->unload()) {
        "unload player2_url"_debug;
    }
    if (player2_help->unload()) {
        "unload player2_help"_debug;
    }
    if (player2_readme->unload()) {
        "unload player2_readme"_debug;
    }
    if (player2_playlist->unload()) {
        "unload player2_playlist"_debug;
    }
    if (player2_media_info->unload()) {
        "unload player2_media_info"_debug;
    }
    delete ui;

    "exit"_debug;
}

void Widget::on_media_info_clicked() {
    if (ui->media_info->isChecked()) {
        setSize(settings.WIDGET.press_info_but_width.toInt(),
                settings.PLAYLIST.check_widgetHeight.toInt());

        ui->playlistCheck->setChecked(true);
    } else {
        if (ui->playlistCheck->isChecked()) {
            setSize(settings.WIDGET.press_mus_but_width.toInt(),
                    settings.PLAYLIST.check_widgetHeight.toInt());
        } else {
            setSize(settings.WIDGET.press_mus_but_width.toInt(),
                     settings.PLAYLIST.not_check_widgetHeight.toInt());
        }
    }
}

/* /WIDGET SIZE IF PLAYLIST CHECKED/UNCHECKED */
void Widget::on_playlistCheck_clicked() {
    if (ui->playlistCheck->isChecked()) {
        setSize(settings.WIDGET.press_mus_but_width.toInt(),
                settings.PLAYLIST.check_widgetHeight.toInt());
    } else {
        ui->media_info->setChecked(false);
        setSize(settings.WIDGET.press_mus_but_width.toInt(),
                settings.PLAYLIST.not_check_widgetHeight.toInt());
    }
}

void Widget::update_media_info() {
    ui->media_buffer_status->setText(QString(tr("buffer: %1")).arg(mediaPlayer->bufferStatus()));

    if (update_media_info_i < 3) {
        update_media_info_i++;

        list_item_text=media_info_get_text_list_item(index + 1,mediaPlayer);

        if (!list_item_text.isEmpty()) {
            this->setWindowTitle(list_item_text);
            ui->listWidget->item(index)->setText(list_item_text);
        }

        ui->property_media->clear();

        media_info_write_media_info(ui->property_media,mediaPlayer);
        media_info_write_metadata(ui->property_media,mediaPlayer);
        media_info_write_media_error(ui->property_media,mediaPlayer);
    }
}
