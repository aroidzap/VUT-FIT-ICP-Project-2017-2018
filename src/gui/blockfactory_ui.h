#ifndef BLOCKFACTORY_UI_H
#define BLOCKFACTORY_UI_H

#include <QWidget>
#include <list>
#include "../core/blockfactory.h"
#include "block_ui.h"

class GraphUI;

class BlockFactoryUI : public BlockFactory
{
private:
	QWidget *block_parent;
	std::list<BlockUI*> blocks;
public:
	BlockBase* AllocBlock(BlockType t) override;
	void FreeBlock(BlockBase *b) override;
	BlockFactoryUI(GraphUI &g);
	~BlockFactoryUI();
};

#endif // BLOCKFACTORY_UI_H
