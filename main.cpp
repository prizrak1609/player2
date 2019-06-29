#include "widget.h"
#include"class_settings.h"
#include"settings_key.h"
#include"defines.h"
#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include<QPluginLoader>
#include<QSplashScreen>
#include<QPixmap>
#ifdef DEBUG
#include"debug.h"
#endif

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    //TODO change ui
    QPixmap *splash_screen_image=new QPixmap();
    class_settings *settings=new class_settings(app.applicationDirPath());
    if(settings->SETTINGS_FILE->path.isEmpty()){
        settings->set(SETTINGS_FILE_PATH,app.applicationDirPath());
        settings->save();
    }
    if(settings->SPLASH_SCREEN->path_to_image.isEmpty()){
        splash_screen_image->load(":/player2_splash.png");
        settings->set(SPLASH_SCREEN_IMAGE_PATH,":/player2_splash.png");
        settings->save();
    }else{
        splash_screen_image->load(settings->SPLASH_SCREEN->path_to_image);
    }
    QSplashScreen splash(*splash_screen_image);
    splash.show();
    splash.showMessage("set close window to false");
    app.setQuitOnLastWindowClosed(false);
    splash.showMessage("choose text codec");
#ifdef Q_OS_WIN
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
#ifdef DEBUG
    qDebug()<<QObject::tr("set textcodec to Windows-1251");
#endif
#else
#ifdef Q_OS_LINUX
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
#ifdef DEBUG
    qDebug()<<(QObject::tr("set textcodec to UTF8"));
#endif
#endif
#endif
    splash.showMessage("create translate variable");
    QTranslator translator;
    splash.showMessage("load translate");
    translator.load(settings->TRANSLATE->path_dir+"/"+QLocale::system().name());
#ifdef DEBUG
    debug_(QString(QObject::tr("load translate: %1/%2")).arg(settings->TRANSLATE->path_dir,QLocale::system().name()));
#endif
    splash.showMessage("install translate");
    app.installTranslator(&translator);
    splash.showMessage(QObject::tr("create widget variable"));
    Widget w;
    splash.showMessage(QObject::tr("set windows flags"));
    w.setWindowFlags(Qt::SubWindow | Qt::WindowTitleHint);
    splash.showMessage(QObject::tr("copy settings to widget"));
    w.settings=settings;
    splash.showMessage(QObject::tr("create widget"));
    w.create_widget();
    splash.showMessage(QObject::tr("show widget normal"));
    w.showNormal();
    splash.finish(&w);
    return app.exec();
}
