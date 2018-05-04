#ifndef BLOCKMENU_H
#define BLOCKMENU_H

#include <QMenu>
#include "../core/blocks.h"

class GraphUI;

class BlockMenuAction : public QAction
{
private:
	BlockType t;
public:
	BlockMenuAction(BlockType t);
	operator BlockType();
};

class BlockMenu
{
private:
	GraphUI &graph;
	QMenu menu;
public:
	BlockMenu(GraphUI &g);
	void ShowMenu();
};

#endif // BLOCKMENU_H
