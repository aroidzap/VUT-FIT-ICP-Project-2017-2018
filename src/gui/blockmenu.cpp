#include "blockmenu.h"
#include <QCursor>
#include "../core/blocks.h"
#include "block_ui.h"

BlockMenu::BlockMenu(GraphUI &g) : graph(g)
{
	auto scalar = menu.addMenu("Scalar");
	auto vector = menu.addMenu("Vector");
	auto matrix = menu.addMenu("Matrix");

	scalar->addAction(new BlockMenuAction(SCAL_INPUT, QIcon()));
	scalar->addAction(new BlockMenuAction(SCAL_OUTPUT, QIcon()));
	scalar->addAction(new BlockMenuAction(SCALAR_ADD, QIcon()));
	scalar->addAction(new BlockMenuAction(SCALAR_SUB, QIcon()));
	scalar->addAction(new BlockMenuAction(SCALAR_MUL, QIcon()));

	vector->addAction(new BlockMenuAction(VECTOR_INPUT, QIcon()));
	vector->addAction(new BlockMenuAction(VECTOR_OUTPUT, QIcon()));
	vector->addAction(new BlockMenuAction(VECTOR_ADD, QIcon()));
	vector->addAction(new BlockMenuAction(VECTOR_DOTPRODUCT, QIcon()));

	matrix->addAction(new BlockMenuAction(MAT2_INPUT, QIcon()));
	matrix->addAction(new BlockMenuAction(MAT2_OUTPUT, QIcon()));
	matrix->addAction(new BlockMenuAction(MAT_ADD, QIcon()));
	matrix->addAction(new BlockMenuAction(MAT_MUL, QIcon()));
	matrix->addAction(new BlockMenuAction(MAT_MUL_VEC, QIcon()));
}

void BlockMenu::ShowMenu()
{
	auto point = QCursor::pos();
	menu.move(point);
	auto selected = menu.exec();
	if (selected != nullptr) {
		graph.addBlock(static_cast<BlockMenuAction&>(*selected));
		auto block = static_cast<BlockUI<BlockBase>*>(&(*graph.blocks.back()));
		if(block != nullptr){
			auto p = graph.mapFromGlobal(point);
			block->Move(p.x(), p.y());
		}
	}
}

BlockMenuAction::BlockMenuAction(BlockType t, const QIcon &icon)
	: QAction(icon, QString(BLOCK_NAME.at(t).c_str()), nullptr), t(t) { }

BlockMenuAction::operator BlockType()
{
	return t;
}

BlockDelete::BlockDelete(GraphUI &g) : graph(g)
{
	menu.addAction(QIcon(":/icons/delete.png"), "Delete");
}

void BlockDelete::ShowMenu(BlockBase *block)
{
	menu.move(QCursor::pos());
	if (menu.exec() != nullptr) {
		graph.removeBlock(block);
	}
}
