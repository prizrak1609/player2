#include<QFile>
#include<QIODevice>
#include<QObject>
#include "player2_readme.h"
#include"defines.h"
#ifdef DEBUG
#include<QDebug>
void debug_(QString text){
	qDebug()<<text;
}
#endif

void create(const QString path){
#ifdef DEBUG
	qDebug()<<(QString(QObject::tr("create readme file: %1/readme_player2.txt")).arg(path));
#endif
		QFile *readme_file=new QFile(QString(path+"/"+"readme_player2.txt"));
		readme_file->open(QIODevice::WriteOnly);
		QString text_readme=QObject::tr(
				"Mouse\n"
				"Middle click - close player\n"
				"Right click - show menu\n"
				"Left click - show/hide player\n\n"
				"Menu\n"
				"Show - show player\n"
				"Hide - hide player\n"
				"Quit - exit player\n\n"
				"Player\n"
				"Q - exit player\n"
				"P - play/pause\n"
				"O - open file\n"
				"Esc - hide player\n"
				"H - help\n"
				"N - next file\n"
				"Ctrl+O - open network music\n"
				"Ctrl+P - previus file\n\n"
				"Global key\n"
				"Ctrl+Shift+P - play/pause\n"
				"Ctrl+Shift+S - show widget\n"
				"Ctrl+Shift+Q - quit\n"
				"Ctrl+Shift+O - open file\n"
				"Ctrl+Shift+N - next file\n"
				"Ctrl+Shift+F - previus file\n");
		readme_file->write(text_readme.toLatin1());
		readme_file->close();
}
