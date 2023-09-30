#include "qglobalshortcut.h"

bool QGlobalShortcut::QGlobalShortcutEventFilter::nativeEventFilter(const QByteArray &event_type, void *message, long *result)
{
    return false;
}

quint32 QGlobalShortcut::toNativeKeycode(Qt::Key k) {
    return 0;
}

quint32 QGlobalShortcut::toNativeModifiers(Qt::KeyboardModifiers m) {
    return 0;
}

void QGlobalShortcut::registerKey(quint32 k, quint32 m, quint32 id) {
}

void QGlobalShortcut::unregisterKey(quint32 k, quint32 m, quint32 id) {
}
