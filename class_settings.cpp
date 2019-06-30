#include "class_settings.h"

#include <QObject>

#include "settings_key.h"
#include "defines.h"
#include "debug.h"

class_settings::class_settings() {}

class_settings::class_settings(const QString& _settings_file_path) {
    settings_file_path = _settings_file_path;

    settings_file = new QSettings(_settings_file_path + "/.player2_settings", QSettings::IniFormat);

    D << QString("open %1/.player2_settings").arg(_settings_file_path);

    readStartSettings();
}

void class_settings::operator= (const class_settings& settings) {
    BUTTON = settings.BUTTON;
    FILE = settings.FILE;
    LIST = settings.LIST;
    WIDGET = settings.WIDGET;
    PLAYLIST = settings.PLAYLIST;
    SLIDER = settings.SLIDER;
    SETTINGS_FILE = settings.SETTINGS_FILE;
    UPDATE = settings.UPDATE;
    PROPERTY_MEDIA = settings.PROPERTY_MEDIA;
    TRANSLATE = settings.TRANSLATE;
    SPLASH_SCREEN = settings.SPLASH_SCREEN;
    app_dir_path = settings.app_dir_path;
    settings_file_path = settings.settings_file_path;
    settings_file = settings.settings_file;
}

void class_settings::readStartSettings() {

    "read start settings"_debug;

    BUTTON.background_color = get(BUTTON_BACKGROUND_COLOR, "rgb(0,42,3)");
    BUTTON.background_pressed_color = get(BUTTON_PRESSED_BACKGROUNG_COLOR, "rgb(0,100,3)");
    BUTTON.background_released_color = get(BUTTON_RELEASED_BACKGROUND_COLOR, "rgb(0,42,3)");
    BUTTON.text_color = get(BUTTON_TEXT_COLOR, "lime");
    BUTTON.border_radius = get(BUTTON_BORDER_RADIUS, "16");
    BUTTON.font_family = get(BUTTON_FONT_FAMILY, "Comic Sans MS");
    BUTTON.font_size = get(BUTTON_FONT_SIZE, "13");
    BUTTON.font_weight = get(BUTTON_FONT_WEIGHT, "5");
    FILE.path = get(FILE_PATH, " ");
    LIST.cur_mus_background_color = get(LIST_CURRENT_MUSIC_BACKGROUND, "blue");
    LIST.prev_mus_background_color = get(LIST_PREVIOUS_MUSIC_BACKGROUND, "black");
    LIST.font_family = get(LIST_FONT_FAMILY, "Comic Sans MS");
    LIST.font_size = get(LIST_FONT_SIZE, "13");
    LIST.font_weight = get(LIST_FONT_WEIGHT, "5");
    SLIDER.groove_border_color = get(SLIDER_GROOVE_BORDER_COLOR, "palette(window)");
    SLIDER.groove_border_style = get(SLIDER_GROOVE_BORDER_STYLE, "solid");
    SLIDER.groove_border_size = get(SLIDER_GROOVE_BORDER_SIZE, "0");
    SLIDER.groove_height = get(SLIDER_GROOVE_HEIGHT, "10");
    SLIDER.handle_border_color = get(SLIDER_HANDLE_BORDER_COLOR, "palette(window)");
    SLIDER.handle_border_style = get(SLIDER_HANDLE_BORDER_STYLE, "solid");
    SLIDER.handle_border_size = get(SLIDER_HANDLE_BORDER_SIZE, "0");
    SLIDER.handle_background = get(SLIDER_HANDLE_BACKGROUND, "palette(window)");
    SLIDER.handle_radius = get(SLIDER_HANDLE_RADIUS, "5");
    SLIDER.handle_width = get(SLIDER_HANDLE_WIDTH, "15");
    SLIDER.next_radius = get(SLIDER_NEXT_RADIUS, "5");
    SLIDER.prev_radius = get(SLIDER_PREV_RADIUS, "5");
    SLIDER.next_background = get(SLIDER_NEXT_BACKGROUND, "#009090");
    SLIDER.prev_background = get(SLIDER_PREV_BACKGOUND, "darkblue");
    WIDGET.background_color = get(WIDGET_BACKGROUND_COLOR, "rgb(0, 0, 0)");
    WIDGET.press_mus_but_width = get(WIDGET_AFTER_PRESS_MUSIC_BUTTON_WIDTH, "500");
    WIDGET.press_info_but_width = get(WIDGET_AFTER_PRESS_INFO_BUTTON_WIDTH, "965");
    WIDGET.begin_height = get(WIDGET_BEGIN_HEIGHT, "54");
    WIDGET.begin_width = get(WIDGET_BEGIN_WIDTH, "270");
    PLAYLIST.check_widgetHeight = get(PLAYLIST_CHECKED_WIDGET_HEIGHT, "500");
    PLAYLIST.not_check_widgetHeight = get(PLAYLIST_NOT_CHECKED_WIDGET_HEIGHT, "90");
    UPDATE.info_music = get(UPDATE_INFO_MUSIC, "1000");
    SETTINGS_FILE.path = get(SETTINGS_FILE_PATH, settings_file_path);
    PROPERTY_MEDIA.font_family = get(PROPERTY_MEDIA_FONT_FAMILY, "Comic Sans MS");
    PROPERTY_MEDIA.font_size = get(PROPERTY_MEDIA_FONT_SIZE, "13");
    PROPERTY_MEDIA.font_weight = get(PROPERTY_MEDIA_FONT_WEIGHT, "5");
    PROPERTY_MEDIA.text_color = get(PROPERTY_MEDIA_TEXT_COLOR, "lime");
    TRANSLATE.path_dir = get(TRANSLATE_PATH_DIR, settings_file_path+"/translate");
    SPLASH_SCREEN.path_to_image = get(SPLASH_SCREEN_IMAGE_PATH, ":/player2_splash.png");
}

void class_settings::re_read() {
    "start re read settings"_debug;

    BUTTON = {};
    FILE = {};
    LIST = {};
    WIDGET = {};
    PLAYLIST = {};
    SLIDER = {};
    SETTINGS_FILE = {};
    UPDATE = {};
    PROPERTY_MEDIA = {};
    TRANSLATE = {};
    readStartSettings();

    "end read settings"_debug;
}

void class_settings::saveSettingsFile() {
    "start save settings"_debug;

    set(BUTTON_BACKGROUND_COLOR, BUTTON.background_color);
    set(BUTTON_BORDER_RADIUS, BUTTON.border_radius);
    set(BUTTON_PRESSED_BACKGROUNG_COLOR, BUTTON.background_pressed_color);
    set(BUTTON_RELEASED_BACKGROUND_COLOR, BUTTON.background_released_color);
    set(BUTTON_TEXT_COLOR, BUTTON.text_color);
    set(BUTTON_FONT_FAMILY, BUTTON.font_family);
    set(BUTTON_FONT_SIZE, BUTTON.font_size);
    set(BUTTON_FONT_WEIGHT, BUTTON.font_weight);
    set(FILE_PATH, FILE.path);
    set(LIST_CURRENT_MUSIC_BACKGROUND, LIST.cur_mus_background_color);
    set(LIST_PREVIOUS_MUSIC_BACKGROUND, LIST.prev_mus_background_color);
    set(SLIDER_GROOVE_HEIGHT, SLIDER.groove_height);
    set(SLIDER_GROOVE_BORDER_COLOR, SLIDER.groove_border_color);
    set(SLIDER_GROOVE_BORDER_SIZE, SLIDER.groove_border_size);
    set(SLIDER_GROOVE_BORDER_STYLE, SLIDER.groove_border_style);
    set(SLIDER_HANDLE_RADIUS, SLIDER.handle_radius);
    set(SLIDER_HANDLE_WIDTH, SLIDER.handle_width);
    set(SLIDER_HANDLE_BACKGROUND, SLIDER.handle_background);
    set(SLIDER_HANDLE_BORDER_COLOR, SLIDER.handle_border_color);
    set(SLIDER_HANDLE_BORDER_SIZE, SLIDER.handle_border_size);
    set(SLIDER_HANDLE_BORDER_STYLE, SLIDER.handle_border_style);
    set(SLIDER_NEXT_BACKGROUND, SLIDER.next_background);
    set(SLIDER_NEXT_RADIUS, SLIDER.next_radius);
    set(SLIDER_PREV_BACKGOUND, SLIDER.prev_background);
    set(SLIDER_PREV_RADIUS, SLIDER.prev_radius);
    set(WIDGET_AFTER_PRESS_MUSIC_BUTTON_WIDTH, WIDGET.press_mus_but_width);
    set(WIDGET_AFTER_PRESS_INFO_BUTTON_WIDTH, WIDGET.press_info_but_width);
    set(WIDGET_BACKGROUND_COLOR, WIDGET.background_color);
    set(WIDGET_BEGIN_HEIGHT, WIDGET.begin_height);
    set(WIDGET_BEGIN_WIDTH, WIDGET.begin_width);
    set(PLAYLIST_CHECKED_WIDGET_HEIGHT, PLAYLIST.check_widgetHeight);
    set(PLAYLIST_NOT_CHECKED_WIDGET_HEIGHT, PLAYLIST.not_check_widgetHeight);
    set(SETTINGS_FILE_PATH, SETTINGS_FILE.path);
    set(UPDATE_INFO_MUSIC, UPDATE.info_music);
    set(LIST_FONT_FAMILY, LIST.font_family);
    set(LIST_FONT_SIZE, LIST.font_size);
    set(LIST_FONT_WEIGHT, LIST.font_weight);
    set(PROPERTY_MEDIA_FONT_FAMILY, PROPERTY_MEDIA.font_family);
    set(PROPERTY_MEDIA_FONT_SIZE, PROPERTY_MEDIA.font_size);
    set(PROPERTY_MEDIA_FONT_WEIGHT, PROPERTY_MEDIA.font_weight);
    set(PROPERTY_MEDIA_TEXT_COLOR, PROPERTY_MEDIA.text_color);
    set(TRANSLATE_PATH_DIR, TRANSLATE.path_dir);
    set(SPLASH_SCREEN_IMAGE_PATH, SPLASH_SCREEN.path_to_image);
    save();

    "end save settings"_debug;
}

QString class_settings::get(const QString& setting_path, const QString& if_not_exists) {
    const QString result = settings_file->value(setting_path, if_not_exists).toString();

    D << QString("settings %1 get %2").arg(setting_path, result);

    return result;
}

void class_settings::set(const QString& setting_path, const QString& value){
    D << QString("set %1 to %2").arg(setting_path, value);

    settings_file->setValue(setting_path, value);
}

void class_settings::save() {
    settings_file->sync();

    "save settings file"_debug;
}

class_settings::~class_settings(){
    saveSettingsFile();
}
