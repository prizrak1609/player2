#pragma once

#include <QString>
#include <QSettings>

class Settings
{
    friend std::unique_ptr<Settings>;
public:
    static std::unique_ptr<Settings>& createInstance(QString _settings_file_path);
    static std::unique_ptr<Settings>& getInstance();

    void set(QString setting_path, QString value);
    QString get(QString setting_path, QString if_not_exists = "");

private:
    static std::unique_ptr<Settings> instance;

    QString settings_file_path;
    QSettings settings_file;

    Settings(QString _settings_file_path);
    ~Settings();

    void save();
};
