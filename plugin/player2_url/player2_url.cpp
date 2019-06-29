#include "player2_url.h"
#include"defines.h"
#ifdef DEBUG
#include<QDebug>
#endif

QUrl parce(const QString url){
#ifdef DEBUG
	qDebug()<<(QString(QObject::tr("parce url %1")).arg(url));
#endif
		QFileInfo info(url);
		return info.isFile() ? QUrl::fromLocalFile(url) : QUrl(url);
}

QFileInfo info(const QString url){
	QFileInfo info(url);
	return info;
}
