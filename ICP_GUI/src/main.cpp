#include "icp_gui.h"
#include <QApplication>

#include "connection.h"
#include "node.h"
#include "port.h"

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
}
