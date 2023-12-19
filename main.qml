
/* This file is generated and only relevant for integrating the project into a Qt 6 and cmake based
C++ project. */
import QtQuick 6.2
import QtQuick.Controls 6.2
import content

Loader {
    id: loader
    sourceComponent: splash
    active: true
    visible: true
    onStatusChanged: {
        if (loader.status === Loader.Ready) {
            item.show()
        }
    }

    Component {
        id: splash
        Window {
            id: splashWindow
            signal timeout
            width: 300
            height: 200
            modality: Qt.ApplicationModal
            flags: Qt.SplashScreen
            color: "transparent"
            Image {
                id: splashImage
                source: "/player2_splash.png"
            }
            ProgressBar {
                id: progress
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                value: 0
                to: 100
                from: 0
            }
            Timer {
                id: timer
                interval: 50
                running: true
                repeat: true
                onTriggered: {
                    progress.value++
                    if (progress.value >= 100) {
                        timer.stop()
                        splashWindow.timeout()
                    }
                }
            }
        }
    }

    Component {
        id: app_window
        App {}
    }

    Connections {
        id: connection
        target: loader.item
        onTimeout: {
            connection.target = null
            loader.sourceComponent = app_window
        }
    }
}
