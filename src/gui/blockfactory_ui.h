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

//! Class defining relationships for all blocks with a parent widget
class BlockFactoryUI : public BlockFactory
{
private:
	//! Widget containing the whole scheme
	QWidget *block_parent;
public:
	//! GUI Block factory
	BlockBase* AllocBlock(BlockType t) override;
	//! GUI Block constructor
	BlockFactoryUI(GraphUI &g);
};

#endif // BLOCKFACTORY_UI_H
