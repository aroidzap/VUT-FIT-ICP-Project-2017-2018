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
public:
	InPort *in_click;
	OutPort *out_click;
private:
	TempConnectionUI tc;
	BlockFactoryUI bf;
	BlockFactory & GetBlockFactory() override;
	bool drag = false;
	QPoint drag_p;
public:
	std::list<ConnectionUI*> ui_connections;
	GraphUI();
	bool addConnection(OutPort &a, InPort &b) override;
	void removeConnection(InPort &p) override;
	void updateConnectionUI(Port &p);
	void hoverConnectionUI(QPoint mouse);
	void hideHoverConnectionUI();
	~GraphUI();
protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;
};

#endif // GRAPH_UI_H
