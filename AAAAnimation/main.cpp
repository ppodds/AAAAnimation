#include "aaaanimation.h"
#include <QtWidgets/QApplication>
#include "main.h"
#include "console/console_controller.h"
#include "player/ascii_player_thread.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AAAAnimation w;
	w.show();
	AsciiPlayerThread ascii_player_thread;
	ascii_player_thread.start();
	return a.exec();
}
