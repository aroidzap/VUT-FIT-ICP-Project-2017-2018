#include "node.h"
#include "style.h"
#include "port.h"

#include <QPainter>
#include <QPainterPath>

#include <algorithm>

Node::Node(std::string name, QPoint position, QWidget *parent) : QWidget(parent), name(name.c_str(), this)
{
	//input
	inputs.push_back(new Port("vstup A", true, parent));
	inputs.push_back(new Port("vstup B", true, parent));
	inputs.push_back(new Port("vstup C", true, parent));
	//outputs
	outputs.push_back(new Port("vystup A", false, parent));
	outputs.push_back(new Port("vystup B", false, parent));

	int input_w = (*std::max_element(inputs.begin(), inputs.end(),
		[] (const Port *a, const Port *b) { return a->getWidth() < b->getWidth(); }))->getWidth();
	int output_w = (*std::max_element(inputs.begin(), inputs.end(),
		[] (const Port *a, const Port *b) { return a->getWidth() < b->getWidth(); }))->getWidth();

	height = (std::max(inputs.size(), outputs.size())) * Style::PortMarginV +
			 std::max(Style::PortMarginV, Style::NodeNameHeight);
	width = std::max(input_w + output_w, Style::NodeMinWidth);
	resize(width + 1, height + 1);

	Move(position.x(), position.y());

	show();
	this->name.show();
}

Node::~Node()
{
	for(auto const &in : inputs) {
		delete in;
	}
	for(auto const &out : outputs) {
		delete out;
	}
}

void Node::Move(int x, int y){
	move(x, y);

	name.move(0, Style::NodeNamePadding);
	name.setFixedWidth(width);
	name.setAlignment(Qt::AlignCenter);

	int offset = std::max(Style::PortMarginV, Style::NodeNameHeight);
	for(auto const &in : inputs) {
		in->Move(x, y + offset);
		offset += Style::PortMarginV;
	}
	offset = std::max(Style::PortMarginV, Style::NodeNameHeight);
	for(auto const &out : outputs) {
		out->Move(x + width, y + offset);
		offset += Style::PortMarginV;
	}
}

void Node::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QPainterPath path;
	path.addRoundedRect(QRectF(.5, .5, width, height), Style::NodeRoundSize, Style::NodeRoundSize);

	painter.setPen(Style::NodeOutlineCol);
	painter.setBrush(Style::NodeBackgroundCol);

	painter.drawPath(path);

}

void Node::mouseMoveEvent(QMouseEvent *event)
{
	if (!drag) {
		drag = true;
		drag_p = event->pos();
	}
	QPoint tmp = pos() + event->pos() - drag_p;
	Move(tmp.x(), tmp.y());
}

void Node::mouseReleaseEvent(QMouseEvent *event)
{
	drag = false;
}
