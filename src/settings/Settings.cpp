#include "Settings.h"

#include <QObject>
#include <QFile>
#include <mutex>

#include "SettingsKey.h"

Settings::Settings(QString _settings_file_path) :
    settings_file_path{_settings_file_path},
    settings_file{_settings_file_path + "/.player2_settings", QSettings::IniFormat}
{
    if(!QFile{_settings_file_path + "/.player2_settings"}.exists())
    {
        qDebug() << "set default settings";
        set(BUTTON_BACKGROUND_COLOR, "rgb(0,42,3)");
        set(BUTTON_PRESSED_BACKGROUNG_COLOR, "rgb(0,100,3)");
        set(BUTTON_RELEASED_BACKGROUND_COLOR, "rgb(0,42,3)");
        set(BUTTON_TEXT_COLOR, "lime");
        set(BUTTON_BORDER_RADIUS, "16");
        set(BUTTON_FONT_FAMILY, "Comic Sans MS");
        set(BUTTON_FONT_SIZE, "13");
        set(BUTTON_FONT_WEIGHT, "5");
        set(FILE_PATH, " ");
        set(LIST_CURRENT_MUSIC_BACKGROUND, "blue");
        set(LIST_PREVIOUS_MUSIC_BACKGROUND, "black");
        set(LIST_FONT_FAMILY, "Comic Sans MS");
        set(LIST_FONT_SIZE, "13");
        set(LIST_FONT_WEIGHT, "5");
        set(SLIDER_GROOVE_BORDER_COLOR, "palette(window)");
        set(SLIDER_GROOVE_BORDER_STYLE, "solid");
        set(SLIDER_GROOVE_BORDER_SIZE, "0");
        set(SLIDER_GROOVE_HEIGHT, "10");
        set(SLIDER_HANDLE_BORDER_COLOR, "palette(window)");
        set(SLIDER_HANDLE_BORDER_STYLE, "solid");
        set(SLIDER_HANDLE_BORDER_SIZE, "0");
        set(SLIDER_HANDLE_BACKGROUND, "palette(window)");
        set(SLIDER_HANDLE_RADIUS, "5");
        set(SLIDER_HANDLE_WIDTH, "15");
        set(SLIDER_NEXT_RADIUS, "5");
        set(SLIDER_PREV_RADIUS, "5");
        set(SLIDER_NEXT_BACKGROUND, "#009090");
        set(SLIDER_PREV_BACKGOUND, "darkblue");
        set(WIDGET_BACKGROUND_COLOR, "rgb(0, 0, 0)");
        set(WIDGET_AFTER_PRESS_MUSIC_BUTTON_WIDTH, "500");
        set(WIDGET_AFTER_PRESS_INFO_BUTTON_WIDTH, "965");
        set(WIDGET_BEGIN_HEIGHT, "54");
        set(WIDGET_BEGIN_WIDTH, "270");
        set(PLAYLIST_CHECKED_WIDGET_HEIGHT, "500");
        set(PLAYLIST_NOT_CHECKED_WIDGET_HEIGHT, "90");
        set(UPDATE_INFO_MUSIC, "1000");
        set(PROPERTY_MEDIA_FONT_FAMILY, "Comic Sans MS");
        set(PROPERTY_MEDIA_FONT_SIZE, "13");
        set(PROPERTY_MEDIA_FONT_WEIGHT, "5");
        set(PROPERTY_MEDIA_TEXT_COLOR, "lime");
        set(TRANSLATE_PATH_DIR, settings_file_path+"/translate");
        get(SPLASH_SCREEN_IMAGE_PATH, ":/player2_splash.png");
    }
}

QString Settings::get(QString setting_path, QString if_not_exists) {
    QString result = settings_file.value(setting_path, if_not_exists).toString();

    qDebug() << QString("settings %1 get %2").arg(setting_path, result);

    return result;
}

void Settings::set(QString setting_path, QString value){
    qDebug() << QString("set %1 to %2").arg(setting_path, value);

    settings_file.setValue(setting_path, value);
}

void Settings::save()
{
    settings_file.sync();

    qDebug() << "save settings file";
}

Settings::~Settings()
{
    save();
}

std::unique_ptr<Settings>& Settings::createInstance(QString _settings_file_path) {
    static std::once_flag flag;
    std::call_once(flag, [&](){
        instance.reset(new Settings(_settings_file_path));
    });

    return instance;
}

std::unique_ptr<Settings>& Settings::getInstance() {
    return instance;
}
