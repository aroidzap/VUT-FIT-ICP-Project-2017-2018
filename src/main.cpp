#include "gui/icp_gui.h"
#include <QApplication>

#include "gui/connection_ui.h"
#include "gui/block_ui.h"
#include "gui/port_ui.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ICP_GUI w;

	QWidget scheme;
	w.setCentralWidget(&scheme);
	w.show();

	Connection c(&scheme);

	Node n("blok", QPoint(150, 100), &scheme);

	return a.exec();

	return 0;
}
