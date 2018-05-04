#ifndef BLOCKMENU_H
#define BLOCKMENU_H

#include <QAction>
#include <QMenu>
#include "../core/blocks.h"
#include "../core/blockbase.h"

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

class BlockDelete
{
private:
	GraphUI &graph;
	QMenu menu;
public:
	BlockDelete(GraphUI &g);
	void ShowMenu(BlockBase *block);
};

#endif // BLOCKMENU_H
