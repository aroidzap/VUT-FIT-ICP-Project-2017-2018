#ifndef GRAPH_UI_H
#define GRAPH_UI_H

#include <QMouseEvent>
#include <QWidget>
#include "../core/graph.h"
#include "blockfactory_ui.h"
#include "connection_ui.h"
#include <list>

class ConnectionUI;

class GraphUI : public QWidget, public Graph
{
private:
	BlockFactoryUI bf;
	BlockFactory & GetBlockFactory() override;
public:
	std::list<ConnectionUI*> ui_connections;
	GraphUI();
	void addConnection(OutPort &a, InPort &b) override;
	void removeConnection(OutPort &a, InPort &b) override;
	void removeConnection(InPort &p) override;
	void updateConnectionUI(Port &p);
	void hoverConnectionUI(QPoint mouse);
	void hideHoverConnectionUI();
	~GraphUI();
protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;
};

#endif // GRAPH_UI_H
