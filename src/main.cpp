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
	/*schema.addBlock(VECTOR_ADD);
	schema.addBlock(VECTOR_ADD);
	schema.addBlock(VECTOR_DOTPRODUCT);
	schema.addBlock(VECTOR_DOTPRODUCT);
	schema.addBlock(SCALAR_ADD);
	schema.addBlock(SCALAR_ADD);
	schema.addBlock(SCALAR_SUB);
	schema.addBlock(SCALAR_SUB);
	schema.addBlock(SCALAR_MUL);
	schema.addBlock(SCALAR_MUL);*/
	schema.addBlock(MAT_MUL);
	schema.addBlock(MAT_MUL);
	schema.addBlock(MAT_ADD);
	schema.addBlock(MAT_ADD);

    BlockUI<BlockBase> *a = static_cast<BlockUI<BlockBase>*>(schema.blocks.front());
    BlockUI<BlockBase> *b = static_cast<BlockUI<BlockBase>*>(schema.blocks.back());

    a->Move(100,100);
    b->Move(300,200);

	//a->Input(0).Value() = vec2(0, 1);
	//a->Input(1).Value() = vec2(1, 0);
	//a->Compute();

	//b->Input(1).Value() = scal(6);

	//b->Compute();

    //std::string out = b->Output(0).Value();

	return app.exec();
}
