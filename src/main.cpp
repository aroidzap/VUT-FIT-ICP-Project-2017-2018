/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: main.cpp
*/

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
	schema.addBlock(VECTOR_ADD);
	schema.addBlock(SCAL_INPUT);
	schema.addBlock(SCAL_OUTPUT);
	schema.addBlock(VECTOR_OUTPUT);
	schema.addBlock(MAT2_INPUT);
	schema.addBlock(MAT2_OUTPUT);
	/*schema.addBlock(VECTOR_ADD);
	schema.addBlock(VECTOR_DOTPRODUCT);
	schema.addBlock(SCALAR_ADD);
	schema.addBlock(SCALAR_SUB);
	schema.addBlock(SCALAR_MUL);
	schema.addBlock(MAT_MUL);
	schema.addBlock(MAT_ADD);*/

	auto it = schema.blocks.begin();

	BlockUI<BlockBase> *a = static_cast<BlockUI<BlockBase>*>(*(it++));
	BlockUI<BlockBase> *b = static_cast<BlockUI<BlockBase>*>(*(it++));

	schema.addConnection(a->Output(0), b->Input(0));
	schema.addConnection(a->Output(0), b->Input(1));

	b->Move(300,300);
	a->Move(100,100);

	schema.computeStep();

	auto ss = schema.saveGraph();
	schema.loadGraph(ss);

	return app.exec();
}
