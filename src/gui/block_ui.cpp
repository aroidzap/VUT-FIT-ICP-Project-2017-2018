#include "block_ui.h"
#include "style.h"
#include "port_ui.h"

#include <QPainter>
#include <QPainterPath>

#include <algorithm>

BlockUI::BlockUI(const BlockBase &b, QWidget *parent)
	: BlockBase(b), QWidget(parent), label(b.name.c_str(), this)
{
	int input_w = static_cast<const InPortUI*>(&(*std::max_element(inputs.begin(), inputs.end(),
		[] (const InPort &a, const InPort &b) {
		// dynamic_cast ??
		return static_cast<const InPortUI*>(&a)->getWidth() < static_cast<const InPortUI*>(&b)->getWidth();
	})))->getWidth();
	int output_w = static_cast<const OutPortUI*>(&(*std::max_element(outputs.begin(), outputs.end(),
		[] (const OutPort &a, const OutPort &b) {
		// dynamic_cast ??
		return static_cast<const OutPortUI*>(&a)->getWidth() < static_cast<const OutPortUI*>(&b)->getWidth();
	})))->getWidth();

	height = (static_cast<int>(std::max(inputs.size(), outputs.size()))) * Style::PortMarginV +
			 std::max(Style::PortMarginV, Style::NodeNameHeight);
	width = std::max(input_w + output_w, Style::NodeMinWidth);
	resize(width + 1, height + 1);

	Move(0, 0);

	show();
	this->label.show();
}

void BlockUI::Move(int x, int y){
	move(x, y);

	label.move(0, Style::NodeNamePadding);
	label.setFixedWidth(width);
	label.setAlignment(Qt::AlignCenter);

	int offset = std::max(Style::PortMarginV, Style::NodeNameHeight);
	for(auto &in : inputs) {
		// dynamic_cast ??
		static_cast<InPortUI*>(&in)->Move(x, y + offset);
		offset += Style::PortMarginV;
	}
	offset = std::max(Style::PortMarginV, Style::NodeNameHeight);
	for(auto &out : outputs) {
		// dynamic_cast ??
		static_cast<OutPortUI*>(&out)->Move(x + width, y + offset);
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
