#include "gui/blockeditor.h"
#include <QApplication>

#include "core/types/types.h"
#include "core/graph.h"
#include "core/blocks.h"
#include "core/blockfactory.h"

#include "gui/graph_ui.h"
#include "gui/block_ui.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	BLOCKEDITOR win;

	GraphUI schema;

	win.setCentralWidget(&schema);
	win.show();

	schema.SetName("schema");

	schema.addBlock(VECTOR_INPUT);
	schema.addBlock(VECTOR_OUTPUT);
	schema.addBlock(VECTOR_ADD);
	schema.addBlock(VECTOR_DOTPRODUCT);
	schema.addBlock(SCALAR_ADD);
	schema.addBlock(SCALAR_SUB);
	schema.addBlock(SCALAR_MUL);
	schema.addBlock(MAT_MUL);
	schema.addBlock(MAT_ADD);

	auto it = schema.blocks.begin();

	BlockUI<BlockBase> *a = static_cast<BlockUI<BlockBase>*>(*(it++));
	BlockUI<BlockBase> *b = static_cast<BlockUI<BlockBase>*>(*(it++));

	b->Move(300,300);
	a->Move(100,100);


	return app.exec();
}
