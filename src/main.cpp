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
#include "core/blocks.h"
#include "core/blockfactory.h"

#include "gui/graph_ui.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	BLOCKEDITOR win;

	GraphUI schema;

	win.setCentralWidget(&schema);
	win.show();

	schema.SetName("schema");
	schema.addBlock(VECTOR_ADD);
	schema.addBlock(VECTOR_ADD);

	BlockBase *a = schema.blocks.front();
	BlockBase *b = schema.blocks.back();

	a->inputs[0].Value() = vec2(0, 1);
	a->inputs[1].Value() = vec2(1, 0);
	a->Compute();

	b->inputs[1].Value() = vec2(1, 1);

	schema.addConnection(a->outputs[0], b->inputs[0]);

	b->Compute();

	std::string out = b->outputs[0].Value();

	return app.exec();
}
