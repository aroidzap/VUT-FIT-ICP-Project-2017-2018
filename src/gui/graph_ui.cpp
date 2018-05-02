#include "graph_ui.h"

BlockFactory &GraphUI::GetBlockFactory()
{
	return bf;
}

GraphUI::GraphUI() : bf(*this) {
	setMouseTracking(true);
}

void GraphUI::addConnection(OutPort &a, InPort &b)
{
	Graph::addConnection(a, b);
	// remove previous connection
	for(ConnectionUI *c : ui_connections){
		if((*c) == b){
			ui_connections.remove(c);
			delete c;
		}
	}
	// create new connection
	ui_connections.push_back(new ConnectionUI(static_cast<InPortUI*>(&b), static_cast<OutPortUI*>(&a), this));
}

void GraphUI::removeConnection(OutPort &a, InPort &b)
{
	Graph::removeConnection(a, b);

	for(ConnectionUI *c : ui_connections){
		if((*c) == a && (*c) == b){
			ui_connections.remove(c);
			delete c;
		}
	}
}

void GraphUI::removeConnection(InPort &p)
{
	Graph::removeConnection(p);

	for(ConnectionUI *c : ui_connections){
		if((*c) == p){
			ui_connections.remove(c);
			delete c;
		}
	}
}

void GraphUI::updateConnectionUI(Port &p)
{
	for(ConnectionUI *c : ui_connections){
		if((*c) == p){
			c->update();
		}
	}
}

GraphUI::~GraphUI()
{
	for(ConnectionUI *c : ui_connections){
		delete c;
	}
}

void GraphUI::hoverConnectionUI(QPoint mouse)
{
	for(ConnectionUI *c : ui_connections){
		c->mouseHover(mouse);
	}
}

void GraphUI::mouseMoveEvent(QMouseEvent *event)
{
	hoverConnectionUI(event->pos());
}

void GraphUI::hideHoverConnectionUI()
{
	for(ConnectionUI *c : ui_connections){
		c->mouseHover(false);
	}
}

void GraphUI::leaveEvent(QEvent *event)
{
	(event);
	hideHoverConnectionUI();
}
