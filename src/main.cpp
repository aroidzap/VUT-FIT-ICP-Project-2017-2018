#include "gui/blockeditor.h"
#include <QApplication>

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

	a->Input(0).Value() = vec2(0, 1);
	a->Input(1).Value() = vec2(1, 0);
	a->Compute();

	b->Input(1).Value() = vec2(1, 1);

	schema.addConnection(a->Output(0), b->Input(0));

	b->Compute();

	std::string out = b->Output(0).Value();

	return app.exec();
}
