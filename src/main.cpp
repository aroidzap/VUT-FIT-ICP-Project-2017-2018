#include "gui/blockeditor.h"
#include <QApplication>

#include "gui/connection_ui.h"
#include "gui/block_ui.h"
#include "gui/port_ui.h"
/*
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	BLOCKEDITOR w;

	QWidget scheme;
	w.setCentralWidget(&scheme);
	w.show();

	ConnectionUI c(&scheme);

	BlockUI n("blok", QPoint(150, 100), &scheme);

	return a.exec();

	return 0;
}
*/

#include "core/types/types.h"
#include "core/graph.h"
#include "core/blocks/vectoraddblock.h"

int main() {

	VectorAddBlock a;
	VectorAddBlock b;

	a.inputs[0].Value() = vec2(0, 1);
	a.inputs[1].Value() = vec2(1, 0);
	a.Compute();

	b.inputs[1].Value() = vec2(1, 1);

	Graph schema("schema", {&a, &b});
	schema.addConnection(a.outputs[0], b.inputs[1]);

	b.Compute();

	Type out = b.outputs[0].Value();

	return 0;
}
