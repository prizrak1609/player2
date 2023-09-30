#ifndef WIDGET_H
#define WIDGET_H

#include <QAction>
#include <QFileDialog>
#include <QFileInfo>
#include <QLabel>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QShortcut>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <QtMultimedia>
#include <QKeyEvent>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <QTimer>
#include <QFont>
#include <QClipboard>
#include <QDropEvent>
#include <QLibrary>
#include "src/settings/Settings.h"
#include "src/plugins/PluginDir.h"
#include "src/plugins/PluginHelp.h"
#include "src/plugins/PluginMediaInfo.h"
#include "src/plugins/PluginPlaylist.h"
#include "src/plugins/PluginReadme.h"
#include "src/plugins/PluginUrl.h"

namespace Ui { class Widget; }

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void create_widget();
private:
    QString current_music_title,current_music_artist,list_item_text;
    QFont *font_list_widget,*font_property_media,*font_button;
    QTimer *timer,*timer_check_settings;
    //		class_help *help;
    //		class_readme *readme;
    //		class_dir *dir;
    //		class_url *url;
    bool playlistChange();
    void setSize(int width,int height);
    bool updatePlayList(const int add_path);
    bool musicPlay,musicClicked,musicPaused,bool_add_network_music,show_widget_with_slider;
    bool musicNext,musicPrevius;
    int update_media_info_i;
    void showWidgetWithSlider();
    void setTray();
    void setShortcut();
    void setActions();
    void setButtons();
    bool dropMimeData();
    QMediaPlayer *mediaPlayer;
    /*				QVideoWidget *video_widget; */
    QFileDialog *file_dialog;
    QStringList playlist_list,list_dir_temp;
    QFileInfo *file_info;
    QFileInfoList info_list_dir;
    QMediaPlaylist *playlist;
    QWidget *settingswidget,*network_music;
    QShortcut *shortcutClose,*shortcutOpenFile,*shortcutHide,*shortcutPause,*shortcutHelp;
    QShortcut *shortcutOpenNetworkMusic,*shortcutPreviusMusic,*shortcutOpenDir,*shortcutNextMusic;
    QShortcut *shortcutAddFile,*shortcutSavePlaylist,*shortcutLoadPlaylist;
    QSystemTrayIcon *tray;
    QMenu *trayMenu;
    QAction *quitAction,*showAction,*hideAction,*helpAction;
    QLineEdit *buttonBackgroundColor,*buttonTextColor,*beginWidgetWidth,*beginWidgetHeight;
    QLineEdit *pathToFile,*afterPressMusicButtonWidgetWidth,*ifPlaylistCheckedWidgetHeight;
    QLineEdit *ifPlaylistNotCheckedWidgetHeight,*textColor,*buttonPressedBackgroundColor;
    QLineEdit *buttonReleasedBackgroundColor,*backgroundColor;
    QLabel *network_music_label,*buttonBackgroundColorLabel,*buttonTextColorLabel;
    QLabel *beginWidgetWidthLabel,*beginWidgetHeightLabel,*backgroundColorLabel,*pathToFileLabel;
    QLabel *afterPressMusicButtonWidgetWidthLabel,*ifPlaylistCheckedWidgetHeightLabel;
    QLabel *ifPlaylistNotCheckedWidgetHeightLabel,*textColorLabel,*buttonPressedBackgroundColorLabel;
    QLabel *buttonReleasedBackgroundColorLabel;
    QTextEdit *labelhelp,*network_music_adress;
    QPushButton *save,*get_network_adress;
    QClipboard *clipboard;
    QLibrary *player2_dir,*player2_url,*player2_help,*player2_readme,*player2_playlist,*player2_media_info;
    PluginDir* pluginDir;
    PluginUrl* pluginUrl;
    PluginHelp* pluginHelp;
    PluginReadme* pluginReadme;
    PluginPlaylist* pluginPlaylist;
    PluginMediaInfo* pluginMediaInfo;
    int index,playlistLength,playlistCount,oldPositionSlider;
    QString file_time_change_old;
    QKeyEvent *keyEvent;
    QString system_language,dir_patch;
    Ui::Widget *ui;

protected:
    void changeEvent(QEvent *e);

public slots:
    void add_network_music_to_playlist();
    void open_network_music();
    void next_music();
    void previus_music();
    void on_musicButton_clicked();
    void changeaudio(int i);
    void slider_released();
    void slider_pressed();
    void seek(qint64 i);
    void duration(qint64 i);
    void clickedAudio(QListWidgetItem* item);
    void nexttitle(QMediaContent media);
    void on_musicButton_pressed();
    void on_musicButton_released();
    void on_exitButton_pressed();
    void on_exitButton_released();
    void click_tray(QSystemTrayIcon::ActivationReason activation);
    void program_help();
    void play_pause();
    void open_dir();
    void update_media_info();
private slots:
    void dropEvent(QDropEvent *drop);
    void dragEnterEvent(QDragEnterEvent* event);
    void add_file_from_bufer();
    void on_media_info_clicked();
    void on_playlistCheck_clicked();
    void save_playlist();
    void load_playlist();
    void check_settings();
};

#endif /* WIDGET_H */
