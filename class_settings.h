#ifndef SETTINGS_FORM_H
#define SETTINGS_FORM_H
#include <QCheckBox>
#include <QFile>
#include <QIODevice>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QtWidgets/QWidget>

struct struct_file {
    QString path;
};

struct struct_button {
    QString background_color, background_pressed_color, background_released_color, text_color, border_radius;
    QString font_family, font_size, font_weight;
};

struct struct_list {
    QString cur_mus_background_color, prev_mus_background_color;
    QString font_family, font_size, font_weight;
};

struct struct_widget {
    QString width, begin_height, begin_width, background_color, press_mus_but_width, press_info_but_width;
};

struct struct_playlist {
    QString check_widgetHeight, not_check_widgetHeight;
};

struct struct_slider {
    QString next_background, next_radius, prev_background, prev_radius, groove_border_color, groove_border_style;
    QString groove_border_size, groove_height, handle_border_color, handle_border_style, handle_border_size;
    QString handle_background, handle_radius, handle_width;
};

struct struct_settings_file {
    QString path;
};

struct struct_update {
    QString info_music;
};

//struct struct_font{
//	QString listWidget_family, listWidget_size, listWidget_weight;
//	QString property_media_family, property_media_size, property_media_weight;
//	QString element_family, element_size, element_weight;
//};

struct struct_property_media {
    QString text_color;
    QString font_family, font_size, font_weight;
};

struct struct_translate {
    QString path_dir;
};

struct struct_splash_screen {
    QString path_to_image;
};

class class_settings {
public:
    class_settings();
    ~class_settings();
    void operator= (const class_settings& settings);
    class_settings(const QString& _settings_file_path);
    QString get(const QString& setting_path, const QString& if_not_exists=" ");
    void set(const QString& setting_path, const QString& value);
    void save();
    void re_read();
    struct_button BUTTON;
    struct_file FILE;
    struct_list LIST;
    struct_widget WIDGET;
    struct_playlist PLAYLIST;
    struct_slider SLIDER;
    struct_settings_file SETTINGS_FILE;
    struct_update UPDATE;
    struct_property_media PROPERTY_MEDIA;
    struct_translate TRANSLATE;
    //	struct_font *FONT;
    struct_splash_screen SPLASH_SCREEN;
    QString app_dir_path;

private:
    QString settings_file_path;
    QSettings* settings_file;
    void readStartSettings();
    void createSettingsFile();
    void saveSettingsFile();
};

#endif /* SETTINGS_FORM_H */
