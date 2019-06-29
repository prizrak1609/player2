#include "qglobalshortcut.h"
#include <QCoreApplication>

QMultiHash<quint32, QGlobalShortcut*> QGlobalShortcut::shortcuts_;
QGlobalShortcut::QGlobalShortcutEventFilter QGlobalShortcut::global_shortcut_event_;

QGlobalShortcut::QGlobalShortcut(QObject* parent)
	: QObject(parent)
{
	initialize();
}

QGlobalShortcut::QGlobalShortcut(const QKeySequence &keyseq, QObject *parent)
	: QObject(parent)
{
	initialize();
	setKey(keyseq);
}

static bool initialized = false;
void QGlobalShortcut::initialize() {
	if (!initialized) {
		qApp->installNativeEventFilter(&global_shortcut_event_);
		initialized = true;
	}
}

QGlobalShortcut::~QGlobalShortcut() {
	unsetKey();
}

QKeySequence QGlobalShortcut::key() const
{
	return keyseq_;
}

void QGlobalShortcut::setKey(const QKeySequence& keyseq)
{
	if (!keyseq_.isEmpty()) {
		unsetKey();
	}
	quint32 keyid = calcId(keyseq);
	if (shortcuts_.count(keyid) == 0) {
		quint32 keycode = toNativeKeycode(getKey(keyseq));
		quint32 mods = toNativeModifiers(getMods(keyseq));
		registerKey(keycode, mods, keyid);
	}
	this->keyseq_ = keyseq;
	shortcuts_.insert(keyid, this);
}

void QGlobalShortcut::unsetKey() {
	quint32 keyid = calcId(keyseq_);
	if (shortcuts_.remove(keyid, this) > 0) {
		if (shortcuts_.count(keyid) == 0) {
			quint32 keycode = toNativeKeycode(getKey(keyseq_));
			quint32 mods = toNativeModifiers(getMods(keyseq_));
			unregisterKey(keycode, mods, keyid);
		}
	}
}

bool QGlobalShortcut::activate(quint32 id) {
	if (shortcuts_.contains(id)) {
		foreach (QGlobalShortcut* s, shortcuts_.values(id)) {
			emit s->activated();
		}
		return true;
	}
	return false;
}

quint32 QGlobalShortcut::calcId(const QKeySequence& keyseq) {
	quint32 keycode = toNativeKeycode(getKey(keyseq));
	quint32 mods    = toNativeModifiers(getMods(keyseq));
	return calcId(keycode, mods);
}

Qt::Key QGlobalShortcut::getKey(const QKeySequence& keyseq) {
	if (keyseq.isEmpty()) {
		return Qt::Key(0);
	}
    return Qt::Key(static_cast<uint>(keyseq[0]) & ~Qt::KeyboardModifierMask);
}

Qt::KeyboardModifiers QGlobalShortcut::getMods(const QKeySequence& keyseq) {
	if (keyseq.isEmpty()) {
        return Qt::KeyboardModifiers(nullptr);
	}
    return Qt::KeyboardModifiers(static_cast<uint>(keyseq[0]) & Qt::KeyboardModifierMask);
}
