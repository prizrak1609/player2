#include<QFileInfoList>
#include<QDir>
#include<QFileDialog>
#include "player2_dir.h"
#include"defines.h"
#ifdef DEBUG
#include<QDebug>
void debug_(QString text){
	qDebug()<<text;
}
#endif
#define DIR_OPEN_DIALOG_DIRS_ONLY 4
#define DIR_OPEN_DIALOG_ALL_FILES 5

QStringList scan(const QString patch_dir){
	#ifdef DEBUG
		qDebug()<<(QString("start scan dir: %1").arg(patch_dir));
	#endif
		QStringList list_dir_temp;
		QFileInfoList info_list_dir=QDir(patch_dir).entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot, QDir::NoSort);
		if (!info_list_dir.isEmpty())
			for (int i=0; i<info_list_dir.size(); i++) {
				if (info_list_dir.at(i).isDir())
					list_dir_temp+=scan(info_list_dir.at(i).absoluteFilePath().trimmed());
				else
					list_dir_temp+=info_list_dir.at(i).absoluteFilePath().trimmed();
			}
		return list_dir_temp;
	}

QStringList scan_url(const QUrl patch_dir){
	return scan(patch_dir.path());
}
QString open_dialog(const QString path,const int type){
#ifdef DEBUG
	qDebug()<<(QString(QObject::tr("open dialog path: %1")).arg(path));
#endif
	QFileDialog *file_dialog;
	QString _path;
	switch (type) {
		case DIR_OPEN_DIALOG_DIRS_ONLY:
			_path=file_dialog->getExistingDirectory(NULL,QObject::tr("Open"),path,QFileDialog::ShowDirsOnly);
		break;
		case DIR_OPEN_DIALOG_ALL_FILES:
			_path=file_dialog->getOpenFileName(NULL,QObject::tr("Open"),path);
		break;
		default: _path=""; break;
	}
	return _path;
}

QString open_save_dialog(const QString path){
#ifdef DEBUG
	qDebug()<<(QString(QObject::tr("open save dialog: %1")).arg(path));
#endif
	QFileDialog *file_dialog;
	return file_dialog->getSaveFileName(NULL,QObject::tr("Save"),path);
}
