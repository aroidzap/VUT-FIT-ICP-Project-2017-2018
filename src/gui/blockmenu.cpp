#include "blockmenu.h"
#include <QCursor>
#include "../core/blocks.h"
#include "block_ui.h"

BlockMenu::BlockMenu(GraphUI &g) : graph(g)
{
	for (auto el : BLOCK_NAME) {
		menu.addAction(new BlockMenuAction(el.first));
	}
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

BlockMenuAction::BlockMenuAction(BlockType t)
	: QAction(QString(BLOCK_NAME.at(t).c_str())), t(t) { }

BlockMenuAction::operator BlockType()
{
	return t;
}
