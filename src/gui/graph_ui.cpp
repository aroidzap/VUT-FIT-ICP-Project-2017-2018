#include "graph_ui.h"
#include "style.h"

BlockFactory &GraphUI::GetBlockFactory()
{
	return bf;
}

GraphUI::GraphUI() : bf(*this), in_click(nullptr), out_click(nullptr),
	tc(&in_click, &out_click, this) {
	setMouseTracking(true);
}

bool GraphUI::addConnection(OutPort &a, InPort &b)
{
	if(Graph::addConnection(a, b)) {
		// remove previous connection
		for(ConnectionUI *c : ui_connections){
			if((*c) == b){
				ui_connections.remove(c);
				delete c;
			}
		}
		// create new connection
		ui_connections.push_back(new ConnectionUI(static_cast<InPortUI*>(&b), static_cast<OutPortUI*>(&a), this));

		this->in_click = nullptr;
		this->out_click = nullptr;
		return true;
	}
	else {
		// Unable to add connection - acyclic
		return false;
	}
}

void GraphUI::removeConnection(InPort &p)
{
	OutPort *conn_p = getConnectedOutPort(p);
	if(conn_p != nullptr){
		this->out_click = conn_p;

		Graph::removeConnection(p);

		for (auto it = ui_connections.cbegin(); it != ui_connections.cend();)
		{
			if (*(*it) == p)
			{
				delete (*it);
				ui_connections.erase(it++);
			}
			else
			{
				it++;
			}
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
	tc.update();
}

void GraphUI::mouseMoveEvent(QMouseEvent *event)
{
	hoverConnectionUI(event->pos());
	tc.update();
	if(drag){
		int x = pos().x() + event->pos().x() - drag_p.x();
		int y = pos().y() + event->pos().y() - drag_p.y();
		x = x > 0 ? 0 : x;
		y = y > Style::MenuHeight ? Style::MenuHeight : y;
		move(x, y);
		if(parentWidget() != nullptr){
			resize(parentWidget()->width() - x, parentWidget()->height() - y);
		}
		lower();
		update();
	}
}

void GraphUI::hideHoverConnectionUI()
{
	for(ConnectionUI *c : ui_connections){
		c->mouseHover(false);
	}
	tc.update();
}

void GraphUI::leaveEvent(QEvent *event)
{
	(event);
	hideHoverConnectionUI();
}

void GraphUI::mousePressEvent(QMouseEvent *event)
{
	(event);
	setFocus();
	in_click = nullptr;
	out_click = nullptr;
	tc.update();
	drag = true;
	drag_p = event->pos();
}

void GraphUI::mouseReleaseEvent(QMouseEvent *event)
{
	(event);
	drag = false;
}
