/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: graph_ui.h
*/

#ifndef GRAPH_UI_H
#define GRAPH_UI_H

#include <QMouseEvent>
#include <QWidget>
#include "../core/graph.h"
#include "blockfactory_ui.h"
#include "connection_ui.h"
#include "blockmenu.h"
#include <list>


class ConnectionUI;

class GraphUI : public QWidget, public Graph
{
public:
	InPort *in_click;
	OutPort *out_click;
private:
	TempConnectionUI tc;
	BlockFactoryUI bf;
	BlockFactory & GetBlockFactory() override;
	bool drag = false;
	QPoint drag_p;
	bool block_click_remove = false;
	BlockMenu block_menu;
public:
	std::list<ConnectionUI*> ui_connections;
	GraphUI();
	void clearGraph() override;
	bool loadGraph(std::stringstream &graph, bool merge = false) override;
	std::stringstream saveGraph() override;
	void removeBlockOnClickEnable();
	void blockClicked(BlockBase *b);
	void removeBlock(BlockBase *b) override;
	bool addConnection(OutPort &a, InPort &b) override;
	void removeConnection(InPort &p) override;
	void removeConnection(OutPort &p) override;
	void updateConnectionUI(Port &p);
	void hoverConnectionUI(QPoint mouse);
	void hideHoverConnectionUI();
	bool allInputsConnected() override;
	void computeReset() override;
	bool computeStep() override;
	bool computeAll() override;
	~GraphUI();
protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;
};

#endif // GRAPH_UI_H
