#include<QObject>
#include<QMessageBox>
#include "player2_help.h"

void show(void){
	QMessageBox *messageBox=new QMessageBox();
	messageBox->setText(QObject::tr(
								"<center><h1>Mouse</h1></center>"
								"<p style='font-size: 20px;'><center>Middle click - close player</center></p>"
								"<p style='font-size: 20px;'><center>Right click - show menu</center></p>"
								"<p style='font-size: 20px;'><center>Left click - show/hide player</center></p>"
								"<p><center><h1>Menu</h1></center></p>"
								"<p style='font-size: 20px;'><center>Show - show player</center></p>"
								"<p style='font-size: 20px;'><center>Hide - hide player</center></p>"
								"<p style='font-size: 20px;'><center>Quit - exit player</center></p>"
								"<p><center><h1>Player</h1></center></p>"
								"<p style='font-size: 20px;'><center>Q - exit player</center></p>"
								"<p style='font-size: 20px;'><center>P - play/pause</center></p>"
								"<p style='font-size: 20px;'><center>O - open file</center></p>"
								"<p style='font-size: 20px;'><center>Esc - hide player</center></p>"
								"<p style='font-size: 20px;'><center>H - help</center></p>"));
	messageBox->showNormal();
}
