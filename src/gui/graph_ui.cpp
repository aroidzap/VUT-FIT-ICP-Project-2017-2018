/** ICP Project 2017/2018: BlockEditor
 * @file graph_ui.cpp
 * @brief Actions performed on the whole scheme
 * @details GraphUI is a central widget, all new blocks and connections are created here
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#include "graph_ui.h"
#include "block_ui.h"
#include "style.h"
#include "alert.h"

BlockFactory &GraphUI::GetBlockFactory()
{
	return bf;
}

GraphUI::GraphUI() : in_click(nullptr), out_click(nullptr),
	tc(&in_click, &out_click, this), bf(*this), block_menu(*this), block_context_menu(*this) {
	setMouseTracking(true);
}

QPoint GraphUI::getOffset() const
{
	return pos_offset;
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
	// block id offset
	int b_id_off = static_cast<int>(blocks.size());

	int x_off = 0, y_off = 0;
	bool first_ = true;
	if (merge) {
		for (BlockBase *b : blocks) {
			auto block = static_cast<BlockUI<BlockBase>*>(b);
			if(first_){
				x_off = block->Pos().x();
				y_off = block->Pos().y() + block->height();
				first_ = false;
			}
			x_off = std::min(x_off, block->Pos().x());
			y_off = std::max(y_off, block->Pos().y() + block->height());
		}
		y_off += Style::GraphLoadPadding;
	} else {
		pos_offset = QPoint(0, 0); // reset drag offset
		x_off = Style::GraphLoadPadding;
		y_off = Style::GraphLoadPadding;
	}

	if (!Graph::loadGraph(graph, merge)){
		return false;
	}

	std::string tmp;
	try {
		// Block Positions
		graph >> std::ws; // skip whitespaces
		std::getline(graph, tmp,'[');
		if (tmp != "pos") {
			return false;
		}
		std::getline(graph, tmp, ']');
		std::stringstream pos_stream(tmp);

		auto it = blocks.begin();
		if (merge) {
			std::advance(it, b_id_off);
		}

		while(std::getline(pos_stream, tmp, ',')){
			std::stringstream xy(tmp);
			std::string xs, ys;
			std::getline(xy, xs, ':');
			std::getline(xy, ys, ':');
			int x = std::stoi(xs) + x_off;
			int y = std::stoi(ys) + y_off;
			static_cast<BlockUI<BlockBase>*>(*it)->Move(x, y);
			it++;
		}
	}
	catch (const std::invalid_argument &) {
		return false;
	}
	return true;
}

std::stringstream GraphUI::saveGraph()
{
	std::stringstream ss = Graph::saveGraph();

	// get offset
	int x_off = 0, y_off = 0;
	bool first_ = true;
	for (BlockBase *b : blocks) {
		auto p = static_cast<BlockUI<BlockBase>*>(b)->Pos();
		if (first_) {
			x_off = p.x(); y_off = p.y();
			first_ = false;
		} else {
			x_off = std::min(x_off, p.x());
			y_off = std::min(y_off, p.y());
		}
	}

	// Block Positions
	ss << '\n';
	ss << "pos[";
	bool first = true;
	for (BlockBase *b : blocks) {
		if(first) {
			first = false;
		} else {
			ss << ",";
		}
		BlockUI<BlockBase> *b_ui = static_cast<BlockUI<BlockBase>*>(b);
		ss << b_ui->Pos().x() - x_off << ":" << b_ui->Pos().y() - y_off;
	}
	ss << "]";

	return std::move(ss);
}

void GraphUI::blockContextMenu(BlockBase *b)
{
	block_context_menu.ShowMenu(b);
}

BlockBase *GraphUI::addBlock(BlockType t)
{
	BlockBase *b = Graph::addBlock(t);
	static_cast<BlockUI<BlockBase>*>(b)->updateOffset(pos_offset);
	return b;
}

void GraphUI::removeBlock(BlockBase *b)
{
	Graph::removeBlock(b);
	this->in_click = nullptr;
	this->out_click = nullptr;
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
			c->Redraw();
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
	tc.Redraw();
}

void GraphUI::mouseMoveEvent(QMouseEvent *event)
{
	hoverConnectionUI(event->pos());
	tc.Redraw();
	if(drag){
		pos_offset += event->pos() - drag_p;
		drag_p = event->pos();
		for (auto b : blocks) {
			static_cast<BlockUI<BlockBase>*>(b)->updateOffset(pos_offset);
		}
	}
}

void GraphUI::hideHoverConnectionUI()
{
	for(ConnectionUI *c : ui_connections){
		c->mouseHover(false);
	}
	tc.Redraw();
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
	if (Graph::computeAll()) {
		return computeStep();
	} else {
		return false;
	}
}

void GraphUI::leaveEvent(QEvent *)
{
	hideHoverConnectionUI();
}

void GraphUI::mousePressEvent(QMouseEvent *event)
{
	setFocus();
	in_click = nullptr;
	out_click = nullptr;
	tc.Redraw();

	if(event->button() != Qt::RightButton) {
		drag = true;
		drag_p = event->pos();
	}
	else {
		block_menu.ShowMenu();
	}
}

void GraphUI::mouseReleaseEvent(QMouseEvent *)
{
	drag = false;
}
