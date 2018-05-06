/** ICP Project 2017/2018: BlockEditor
 * @file blockfactory_ui.h
 * @brief Abstract factory for blocks - GUI
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef BLOCKFACTORY_UI_H
#define BLOCKFACTORY_UI_H

#include <QWidget>
#include <list>
#include "../core/blockfactory.h"

class GraphUI;

/**
 * @brief Abstract factory for creating GUI blocks
 *
 * Blocks are created using abstract factory design patern.
 */
class BlockFactoryUI : public BlockFactory
{
private:
	//! Widged used as parent for constructed blocks
	QWidget *block_parent;
public:
	//! GUI Block constructor
	//! @param t Type of block to construct
	BlockBase* AllocBlock(BlockType t) override;

	//! Factory constructor
	//! @param g Parent scheme object
	BlockFactoryUI(GraphUI &g);
};

#endif // BLOCKFACTORY_UI_H
