#include "gui/icp_gui.h"
#include <QApplication>

#include "gui/connection.h"
#include "gui/node.h"
#include "gui/port.h"

#include "core/type.h"

int main(int argc, char *argv[])
{
	/*QApplication a(argc, argv);

	ICP_GUI w;

	QWidget scheme;
	w.setCentralWidget(&scheme);
	w.show();

	Connection c(&scheme);

	Node n("blok", QPoint(150, 100), &scheme);

	return a.exec();*/

	Type t{"x", "y", "zz"};
	Type b{"z", "y", "x"};
	bool x = t == b;
	return 0;
}
