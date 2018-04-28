#include "block_ui.h"
#include "style.h"
#include "port_ui.h"

#include <QPainter>
#include <QPainterPath>

#include <algorithm>

BlockUI::BlockUI(std::string name, QPoint position, QWidget *parent) : QWidget(parent), name(name.c_str(), this)
{
	//input
	inputs.push_back(new PortUI("vstup A", true, parent));
	inputs.push_back(new PortUI("vstup B", true, parent));
	inputs.push_back(new PortUI("vstup C", true, parent));
	//outputs
	outputs.push_back(new PortUI("vystup A", false, parent));
	outputs.push_back(new PortUI("vystup B", false, parent));

	int input_w = (*std::max_element(inputs.begin(), inputs.end(),
		[] (const PortUI *a, const PortUI *b) { return a->getWidth() < b->getWidth(); }))->getWidth();
	int output_w = (*std::max_element(inputs.begin(), inputs.end(),
		[] (const PortUI *a, const PortUI *b) { return a->getWidth() < b->getWidth(); }))->getWidth();

	height = (static_cast<int>(std::max(inputs.size(), outputs.size()))) * Style::PortMarginV +
			 std::max(Style::PortMarginV, Style::NodeNameHeight);
	width = std::max(input_w + output_w, Style::NodeMinWidth);
	resize(width + 1, height + 1);

	Move(position.x(), position.y());

	show();
	this->name.show();
}

BlockUI::~BlockUI()
{
	for(auto const &in : inputs) {
		delete in;
	}
	for(auto const &out : outputs) {
		delete out;
	}
}

void BlockUI::Move(int x, int y){
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

void BlockUI::Highlight(bool enable)
{
	this->highlight = enable;
	update();
}

void BlockUI::paintEvent(QPaintEvent *event)
{
	(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);


	QPainterPath path;
	path.addRoundedRect(QRectF(.5, .5, width, height), Style::NodeRoundSize, Style::NodeRoundSize);

	painter.fillPath(path, QBrush(Style::NodeBackgroundCol));

	if (highlight) {
		QPainterPath h;
		h.addRoundedRect(QRectF(2.5, 2.5, width - 4, height - 4), Style::NodeRoundSize, Style::NodeRoundSize);

		QPen p(Style::NodeOutlineHighlightCol);
		p.setWidth(5);

		painter.strokePath(h, p);
	}

	painter.strokePath(path, QPen(Style::NodeOutlineCol));
}

void BlockUI::mouseMoveEvent(QMouseEvent *event)
{
	if (!drag) {
		drag = true;
		drag_p = event->pos();
	}
	QPoint tmp = pos() + event->pos() - drag_p;
	Move(tmp.x(), tmp.y());
}

void BlockUI::mouseReleaseEvent(QMouseEvent *event)
{
	(event);
	drag = false;
}
