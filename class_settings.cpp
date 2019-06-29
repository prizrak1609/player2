#include "class_settings.h"
#include "settings_key.h"
#include"defines.h"
#include<QObject>
#ifdef DEBUG
#include<QDebug>
#endif

class_settings::class_settings(){}

/**
 * @brief class_settings::class_settings
 * @param _settings_file_path
 */
class_settings::class_settings(QString _settings_file_path){
    BUTTON=new struct_button();
    FILE=new struct_file();
    LIST=new struct_list();
    WIDGET=new struct_widget();
    PLAYLIST=new struct_playlist();
    SLIDER=new struct_slider();
    SETTINGS_FILE=new struct_settings_file();
    UPDATE=new struct_update();
    PROPERTY_MEDIA=new struct_property_media();
    TRANSLATE=new struct_translate();
    //FONT=new struct_font();
    SPLASH_SCREEN=new struct_splash_screen();
    settings_file_path=_settings_file_path;
    settings_file=new QSettings(_settings_file_path+"/.player2_settings",QSettings::IniFormat);
#ifdef DEBUG
    qDebug()<<QString(QObject::tr("open %1/.player2_settings")).arg(_settings_file_path);
#endif
    readStartSettings();
}

/* /READ SETTINGS */
/**
 * @brief class_settings::readStartSettings
 */
void class_settings::readStartSettings(){
#ifdef DEBUG
    qDebug()<<QObject::tr("read start settings");
#endif
    BUTTON->background_color=get(BUTTON_BACKGROUND_COLOR,"rgb(0,42,3)");
    BUTTON->background_pressed_color=get(BUTTON_PRESSED_BACKGROUNG_COLOR,"rgb(0,100,3)");
    BUTTON->background_released_color=get(BUTTON_RELEASED_BACKGROUND_COLOR,"rgb(0,42,3)");
    BUTTON->text_color=get(BUTTON_TEXT_COLOR,"lime");
    BUTTON->border_radius=get(BUTTON_BORDER_RADIUS,"16");
    BUTTON->font_family=get(BUTTON_FONT_FAMILY,"Comic Sans MS");
    BUTTON->font_size=get(BUTTON_FONT_SIZE,"13");
    BUTTON->font_weight=get(BUTTON_FONT_WEIGHT,"5");
    FILE->path=get(FILE_PATH," ");
    LIST->cur_mus_background_color=get(LIST_CURRENT_MUSIC_BACKGROUND,"blue");
    LIST->prev_mus_background_color=get(LIST_PREVIOUS_MUSIC_BACKGROUND,"black");
    LIST->font_family=get(LIST_FONT_FAMILY,"Comic Sans MS");
    LIST->font_size=get(LIST_FONT_SIZE,"13");
    LIST->font_weight=get(LIST_FONT_WEIGHT,"5");
    SLIDER->groove_border_color=get(SLIDER_GROOVE_BORDER_COLOR,"palette(window)");
    SLIDER->groove_border_style=get(SLIDER_GROOVE_BORDER_STYLE,"solid");
    SLIDER->groove_border_size=get(SLIDER_GROOVE_BORDER_SIZE,"0");
    SLIDER->groove_height=get(SLIDER_GROOVE_HEIGHT,"10");
    SLIDER->handle_border_color=get(SLIDER_HANDLE_BORDER_COLOR,"palette(window)");
    SLIDER->handle_border_style=get(SLIDER_HANDLE_BORDER_STYLE,"solid");
    SLIDER->handle_border_size=get(SLIDER_HANDLE_BORDER_SIZE,"0");
    SLIDER->handle_background=get(SLIDER_HANDLE_BACKGROUND,"palette(window)");
    SLIDER->handle_radius=get(SLIDER_HANDLE_RADIUS,"5");
    SLIDER->handle_width=get(SLIDER_HANDLE_WIDTH,"15");
    SLIDER->next_radius=get(SLIDER_NEXT_RADIUS,"5");
    SLIDER->prev_radius=get(SLIDER_PREV_RADIUS,"5");
    SLIDER->next_background=get(SLIDER_NEXT_BACKGROUND,"#009090");
    SLIDER->prev_background=get(SLIDER_PREV_BACKGOUND,"darkblue");
    WIDGET->background_color=get(WIDGET_BACKGROUND_COLOR,"rgb(0,0,0)");
    WIDGET->press_mus_but_width=get(WIDGET_AFTER_PRESS_MUSIC_BUTTON_WIDTH,"500");
    WIDGET->press_info_but_width=get(WIDGET_AFTER_PRESS_INFO_BUTTON_WIDTH,"965");
    WIDGET->begin_height=get(WIDGET_BEGIN_HEIGHT,"54");
    WIDGET->begin_width=get(WIDGET_BEGIN_WIDTH,"270");
    PLAYLIST->check_widgetHeight=get(PLAYLIST_CHECKED_WIDGET_HEIGHT,"500");
    PLAYLIST->not_check_widgetHeight=get(PLAYLIST_NOT_CHECKED_WIDGET_HEIGHT,"90");
    UPDATE->info_music=get(UPDATE_INFO_MUSIC,"1000");
    SETTINGS_FILE->path=get(SETTINGS_FILE_PATH,settings_file_path);
    PROPERTY_MEDIA->font_family=get(PROPERTY_MEDIA_FONT_FAMILY,"Comic Sans MS");
    PROPERTY_MEDIA->font_size=get(PROPERTY_MEDIA_FONT_SIZE,"13");
    PROPERTY_MEDIA->font_weight=get(PROPERTY_MEDIA_FONT_WEIGHT,"5");
    PROPERTY_MEDIA->text_color=get(PROPERTY_MEDIA_TEXT_COLOR,"lime");
    TRANSLATE->path_dir=get(TRANSLATE_PATH_DIR,settings_file_path+"/translate");
    SPLASH_SCREEN->path_to_image=get(SPLASH_SCREEN_IMAGE_PATH,":/player2_splash.png");
}

void class_settings::re_read(){
#ifdef DEBUG
    qDebug()<<QObject::tr("start re read settings");
#endif
    delete BUTTON;
    delete FILE;
    delete LIST;
    delete WIDGET;
    delete SLIDER;
    delete PLAYLIST;
    delete SETTINGS_FILE;
    delete UPDATE;
    delete PROPERTY_MEDIA;
    delete TRANSLATE;
#ifdef DEBUG
    qDebug()<<QObject::tr("delete old settings");
#endif
    BUTTON=new struct_button();
    FILE=new struct_file();
    LIST=new struct_list();
    WIDGET=new struct_widget();
    PLAYLIST=new struct_playlist();
    SLIDER=new struct_slider();
    SETTINGS_FILE=new struct_settings_file();
    UPDATE=new struct_update();
    PROPERTY_MEDIA=new struct_property_media();
    TRANSLATE=new struct_translate();
    readStartSettings();
#ifdef DEBUG
    qDebug()<<QObject::tr("end read settings");
#endif
}

/* /SAVE SETTINGS */
/**
 * @brief class_settings::saveSettingsFile
 */
void class_settings::saveSettingsFile(){
#ifdef DEBUG
    qDebug()<<QObject::tr("save settings");
#endif
    set(BUTTON_BACKGROUND_COLOR,BUTTON->background_color);
    set(BUTTON_BORDER_RADIUS,BUTTON->border_radius);
    set(BUTTON_PRESSED_BACKGROUNG_COLOR,BUTTON->background_pressed_color);
    set(BUTTON_RELEASED_BACKGROUND_COLOR,BUTTON->background_released_color);
    set(BUTTON_TEXT_COLOR,BUTTON->text_color);
    set(BUTTON_FONT_FAMILY,BUTTON->font_family);
    set(BUTTON_FONT_SIZE,BUTTON->font_size);
    set(BUTTON_FONT_WEIGHT,BUTTON->font_weight);
    set(FILE_PATH,FILE->path);
    set(LIST_CURRENT_MUSIC_BACKGROUND,LIST->cur_mus_background_color);
    set(LIST_PREVIOUS_MUSIC_BACKGROUND,LIST->prev_mus_background_color);
    set(SLIDER_GROOVE_HEIGHT,SLIDER->groove_height);
    set(SLIDER_GROOVE_BORDER_COLOR,SLIDER->groove_border_color);
    set(SLIDER_GROOVE_BORDER_SIZE,SLIDER->groove_border_size);
    set(SLIDER_GROOVE_BORDER_STYLE,SLIDER->groove_border_style);
    set(SLIDER_HANDLE_RADIUS,SLIDER->handle_radius);
    set(SLIDER_HANDLE_WIDTH,SLIDER->handle_width);
    set(SLIDER_HANDLE_BACKGROUND,SLIDER->handle_background);
    set(SLIDER_HANDLE_BORDER_COLOR,SLIDER->handle_border_color);
    set(SLIDER_HANDLE_BORDER_SIZE,SLIDER->handle_border_size);
    set(SLIDER_HANDLE_BORDER_STYLE,SLIDER->handle_border_style);
    set(SLIDER_NEXT_BACKGROUND,SLIDER->next_background);
    set(SLIDER_NEXT_RADIUS,SLIDER->next_radius);
    set(SLIDER_PREV_BACKGOUND,SLIDER->prev_background);
    set(SLIDER_PREV_RADIUS,SLIDER->prev_radius);
    set(WIDGET_AFTER_PRESS_MUSIC_BUTTON_WIDTH,WIDGET->press_mus_but_width);
    set(WIDGET_AFTER_PRESS_INFO_BUTTON_WIDTH,WIDGET->press_info_but_width);
    set(WIDGET_BACKGROUND_COLOR,WIDGET->background_color);
    set(WIDGET_BEGIN_HEIGHT,WIDGET->begin_height);
    set(WIDGET_BEGIN_WIDTH,WIDGET->begin_width);
    set(PLAYLIST_CHECKED_WIDGET_HEIGHT,PLAYLIST->check_widgetHeight);
    set(PLAYLIST_NOT_CHECKED_WIDGET_HEIGHT,PLAYLIST->not_check_widgetHeight);
    set(SETTINGS_FILE_PATH,SETTINGS_FILE->path);
    set(UPDATE_INFO_MUSIC,UPDATE->info_music);
    set(LIST_FONT_FAMILY,LIST->font_family);
    set(LIST_FONT_SIZE,LIST->font_size);
    set(LIST_FONT_WEIGHT,LIST->font_weight);
    set(PROPERTY_MEDIA_FONT_FAMILY,PROPERTY_MEDIA->font_family);
    set(PROPERTY_MEDIA_FONT_SIZE,PROPERTY_MEDIA->font_size);
    set(PROPERTY_MEDIA_FONT_WEIGHT,PROPERTY_MEDIA->font_weight);
    set(PROPERTY_MEDIA_TEXT_COLOR,PROPERTY_MEDIA->text_color);
    set(TRANSLATE_PATH_DIR,TRANSLATE->path_dir);
    set(SPLASH_SCREEN_IMAGE_PATH,SPLASH_SCREEN->path_to_image);
    save();
}

/* /GET SETTINGS VALUE */
/**
 * @brief class_settings::get
 * @param setting_path
 * @param if_not_exists
 * @return
 */
QString class_settings::get(QString setting_path,QString if_not_exists){
#ifdef DEBUG
    qDebug()<<QString(QObject::tr("settings %1 get %2")).arg(setting_path,settings_file->value(setting_path,if_not_exists).toString());
#endif
    return settings_file->value(setting_path,if_not_exists).toString();
}

/* /SET SETTINGS VALUE */
/**
 * @brief class_settings::set
 * @param setting_path
 * @param value
 */
void class_settings::set(QString setting_path, QString value){
#ifdef DEBUG
    qDebug()<<QString(QObject::tr("set %1 to %2")).arg(setting_path,value);
#endif
    settings_file->setValue(setting_path,value);
}

/// SAVE
/**
 * @brief class_settings::save
 */
void class_settings::save(){
    settings_file->sync();
#ifdef DEBUG
    qDebug()<<QObject::tr("save settings file");
#endif
}

class_settings::~class_settings(){
    saveSettingsFile();
#ifdef DEBUG
    qDebug()<<QObject::tr("delete struct BUTTON");
#endif
    delete BUTTON;
#ifdef DEBUG
    qDebug()<<QObject::tr("delete struct FILE");
#endif
    delete FILE;
#ifdef DEBUG
    qDebug()<<QObject::tr("delete struct LIST");
#endif
    delete LIST;
#ifdef DEBUG
    qDebug()<<QObject::tr("delete struct WIDGET");
#endif
    delete WIDGET;
#ifdef DEBUG
    qDebug()<<QObject::tr("delete struct SLIDER");
#endif
    delete SLIDER;
#ifdef DEBUG
    qDebug()<<QObject::tr("delete struct PLAYLIST");
#endif
    delete PLAYLIST;
#ifdef DEBUG
    qDebug()<<QObject::tr("delete struct SETTINGS_FILE");
#endif
    delete SETTINGS_FILE;
#ifdef DEBUG
    qDebug()<<QObject::tr("delete struct UPDATE");
#endif
    delete UPDATE;
#ifdef DEBUG
    qDebug()<<QObject::tr("delete struct PROPERTY_MEDIA");
#endif
    delete PROPERTY_MEDIA;
#ifdef DEBUG
    qDebug()<<QObject::tr("delete struct TRANSLATE");
#endif
    delete TRANSLATE;
}
