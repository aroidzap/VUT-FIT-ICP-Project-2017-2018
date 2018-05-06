/** ICP Project 2017/2018: BlockEditor
 * @file blockmenu.h
 * @brief Menu dropdown showed after right-clicking blocks
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef BLOCKMENU_H
#define BLOCKMENU_H

#include <QAction>
#include <QMenu>
#include "../core/blocks.h"
#include "../core/blockbase.h"

class GraphUI;

//! BlockType decorator for QAction
class BlockMenuAction : public QAction
{
private:
	//! Type of the generated block
	BlockType t;
public:
	//! Action constructor
	BlockMenuAction(BlockType t, const QIcon &icon);
	operator BlockType();
};

//! Class that defines the dropdown menu for selecting a block to generate
class BlockMenu
{
private:
	//! Parent GraphUI
	GraphUI &graph;
	//! Dropdown menu object
	QMenu menu;
public:
	//! Menu constructor
	BlockMenu(GraphUI &g);
	//! Function for showing the menu after a right click if free space
	void ShowMenu();
};

//! Menu shown after right-clicking a block (contains only a delete option)
class BlockDelete
{
private:
	//! Parent widget
	GraphUI &graph;
	//! Dropdown menu object
	QMenu menu;
public:
	//! Menu constructor
	BlockDelete(GraphUI &g);
	//! Function for showing the menu after right-clicking a block
	void ShowMenu(BlockBase *block);
};

#endif // BLOCKMENU_H
