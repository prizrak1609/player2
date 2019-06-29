#include<QFile>
#include<QIODevice>
#include<QObject>
#include<QTextStream>
#include "player2_playlist.h"
#include"defines.h"
#ifdef DEBUG
#include<QDebug>
#endif

void save(const QStringList list, const QString path, const int type){
	QFile file(path);
	if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
#ifdef DEBUG
		qDebug()<<(QObject::tr("start save playlist"));
#endif
		QTextStream stream(&file);
		for(QString item:list){
			stream<<item<<"\n";
		}
		file.close();
#ifdef DEBUG
		qDebug()<<(QObject::tr("end save playlist"));
#endif
	}else{
#ifdef DEBUG
		qDebug()<<(QObject::tr("error open file"));
#endif
	}
}

QStringList read(const QString path,const int type){
	QFile file(path);
	QStringList list;
	if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
#ifdef DEBUG
		qDebug()<<(QObject::tr("start read playlist"));
#endif
		QTextStream stream(&file);
		while(!stream.atEnd()){
			list.append(stream.readLine());
		}
#ifdef DEBUG
		qDebug()<<(QObject::tr("end read playlist"));
#endif
		return list;
	}else{
#ifdef DEBUG
		qDebug()<<(QObject::tr("error open file"));
#endif
	}
	return list;
}
