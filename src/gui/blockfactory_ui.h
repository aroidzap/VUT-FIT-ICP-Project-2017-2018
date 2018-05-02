#ifndef BLOCKFACTORY_UI_H
#define BLOCKFACTORY_UI_H

#include <QWidget>
#include <list>
#include "../core/blockfactory.h"

class GraphUI;

class BlockFactoryUI : public BlockFactory
{
private:
	QWidget *block_parent;
public:
	BlockBase* AllocBlock(BlockType t) override;
	BlockFactoryUI(GraphUI &g);
};

#endif // BLOCKFACTORY_UI_H