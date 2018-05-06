/** ICP Project 2017/2018: BlockEditor
 * @file graph_ui.h
 * @brief Scheme GUI representation
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef GRAPH_UI_H
#define GRAPH_UI_H

#include <QMouseEvent>
#include <QPaintEvent>
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
	BlockMenu block_menu;
	BlockDelete block_context_menu;
public:
	QPoint pos_offset;
	std::list<ConnectionUI*> ui_connections;
	GraphUI();
	QPoint getOffset() const;
	void clearGraph() override;
	bool loadGraph(std::stringstream &graph, bool merge = false) override;
	std::stringstream saveGraph() override;
	void blockContextMenu(BlockBase *b);
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
	void mouseReleaseEvent(QMouseEvent *) override;
	void leaveEvent(QEvent *) override;
};

#endif // GRAPH_UI_H
