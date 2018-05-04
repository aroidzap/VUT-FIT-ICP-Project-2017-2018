#include "graph_ui.h"
#include "block_ui.h"
#include "style.h"
#include "alert.h"

BlockFactory &GraphUI::GetBlockFactory()
{
	return bf;
}

GraphUI::GraphUI() : bf(*this), in_click(nullptr), out_click(nullptr),
	tc(&in_click, &out_click, this) {
	setMouseTracking(true);
}

void GraphUI::clearGraph()
{
	Graph::clearGraph();
	for(ConnectionUI *c : ui_connections){
		delete c;
	}
	ui_connections.clear();
	in_click = nullptr;
	out_click = nullptr;
	last_computed = nullptr;
}

bool GraphUI::loadGraph(std::stringstream &graph, bool merge)
{
	if (!Graph::loadGraph(graph, merge)){
		return false;
	}

	std::string tmp;
	try {
		// Block Positions
		std::getline(graph, tmp,'[');
		if (tmp != "pos") {
			return false;
		}
		std::getline(graph, tmp, ']');
		std::stringstream pos_stream(tmp);

		auto it = blocks.begin();

		while(std::getline(pos_stream, tmp, ',')){
			std::stringstream xy(tmp);
			std::string xs, ys;
			std::getline(xy, xs, ':');
			std::getline(xy, ys, ':');
			int x = std::stoi(xs);
			int y = std::stoi(ys);
			static_cast<BlockUI<BlockBase>*>(*it)->Move(x, y);
			it++;
		}
	}
	catch (const std::invalid_argument &e) {
		(e);
		return false;
	}
	return true;
}

std::stringstream GraphUI::saveGraph()
{
	std::stringstream ss = Graph::saveGraph();

	// Block Positions
	ss << "pos[";
	bool first = true;
	for (BlockBase *b : blocks) {
		if(first) {
			first = false;
		} else {
			ss << ",";
		}
		BlockUI<BlockBase> *b_ui = static_cast<BlockUI<BlockBase>*>(b);
		ss << b_ui->Pos().x() << ":" << b_ui->Pos().y();
	}
	ss << "]";

	return std::move(ss);
}

void GraphUI::blockClicked(BlockBase *b)
{
	if(block_click_remove){
		removeBlock(b);
	}
}

void GraphUI::removeBlockOnClickEnable()
{
	block_click_remove = true;
}

void GraphUI::removeBlock(BlockBase *b)
{
	Graph::removeBlock(b);
	block_click_remove = false;
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
		if(!a.Value().type_of(b.Value())){
			ErrorAlert("These port types are incompatible!");
		}
		else {
			ErrorAlert("This connection would form cycle!");
		}

		this->in_click = nullptr;
		this->out_click = nullptr;
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
				it = ui_connections.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}

void GraphUI::removeConnection(OutPort &p)
{
	Graph::removeConnection(p);

	for (auto it = ui_connections.cbegin(); it != ui_connections.cend();)
	{
		if (*(*it) == p)
		{
			delete (*it);
			it = ui_connections.erase(it);
		}
		else
		{
			it++;
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

bool GraphUI::allInputsConnected()
{
	if(!Graph::allInputsConnected()){
		ErrorAlert("Some input ports are not connected!");
		return false;
	}
	return true;
}

void GraphUI::computeReset()
{
	if(last_computed != nullptr){
		static_cast<BlockUI<BlockBase>*>(last_computed)->Highlight(false);
	}
	Graph::computeReset();
}

bool GraphUI::computeStep()
{
	if(last_computed != nullptr){
		static_cast<BlockUI<BlockBase>*>(last_computed)->Highlight(false);
	}
	bool ret = Graph::computeStep();
	if(last_computed != nullptr){
		static_cast<BlockUI<BlockBase>*>(last_computed)->Highlight(true);
	}
	return ret;
}

bool GraphUI::computeAll()
{
	bool ret = Graph::computeAll();
	return computeStep() && ret;
}

void GraphUI::leaveEvent(QEvent *event)
{
	(event);
	hideHoverConnectionUI();
}

void GraphUI::mousePressEvent(QMouseEvent *event)
{
	if(event->button() != Qt::RightButton) {
		setFocus();
		in_click = nullptr;
		out_click = nullptr;
		tc.update();
		drag = true;
		drag_p = event->pos();
	}
	else {

	}
}

void GraphUI::mouseReleaseEvent(QMouseEvent *event)
{
	(event);
	drag = false;
}
