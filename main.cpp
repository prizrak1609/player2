#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QPluginLoader>
#include <QSplashScreen>
#include <QPixmap>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include "settings/Settings.h"

int main(int argc, char *argv[]) {
    set_qt_environment();
    
    QApplication app(argc, argv);
    
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [&url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
    
    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    
    //TODO change ui to use QML
    Settings::createInstance(app.applicationDirPath());
    auto& settings = Settings::getInstance();

    QPixmap splash_screen_image;

    // if (settings.SPLASH_SCREEN.path_to_image.isEmpty()) {
        // splash_screen_image.load(":/player2_splash.png");
    //     settings.set(SPLASH_SCREEN_IMAGE_PATH, ":/player2_splash.png");
    //     settings.save();
    // } else {
    //     splash_screen_image.load(settings.SPLASH_SCREEN.path_to_image);
    // }

    QSplashScreen splash { splash_screen_image };
    splash.show();
    splash.showMessage("set close window to false");

    app.setQuitOnLastWindowClosed(false);

    splash.showMessage("choose text codec");

#ifdef Q_OS_WIN
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    "set textcodec to Windows-1251"_debug;
#else
#ifdef Q_OS_LINUX
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    "set textcodec to UTF8"_debug;
#endif // Q_OS_LINUX

#endif // Q_OS_WIN

    splash.showMessage("load translate");

    QTranslator translator;

    // translator.load(settings.TRANSLATE.path_dir + "/" + QLocale::system().name());

    // D << QString("load translate: %1/%2").arg(settings.TRANSLATE.path_dir, QLocale::system().name());

    splash.showMessage("install translate");

    app.installTranslator(&translator);

    splash.showMessage(QObject::tr("create widget"));

    // Widget w;
    // w.setWindowFlags(Qt::SubWindow | Qt::WindowTitleHint);
    // w.settings = settings;

    splash.showMessage(QObject::tr("create widget"));

    // w.create_widget();

    splash.showMessage(QObject::tr("show widget"));

    // w.showNormal();

    // splash.finish(&w);
    
    engine.load(url);
    
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
