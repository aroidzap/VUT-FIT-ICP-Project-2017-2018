#ifndef BLOCK_UI_H
#define BLOCK_UI_H

#include <QApplication>
#include <QPaintEvent>
#include <QWidget>
#include <list>

#include <QPainter>
#include <QPainterPath>

#include <algorithm>

#include "block_ui.h"
#include "style.h"
#include "port_ui.h"
#include "graph_ui.h"

#include "../core/blockbase.h"

template <typename BlockBaseT>
class BlockUI : public QWidget, public BlockBaseT
{
private:
	std::vector<InPortUI> inputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
	std::vector<OutPortUI> outputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
	QLabel label;
	bool drag = false;
	bool highlight = false;
	QPoint drag_p;
	int height;
	int width;
public:
	explicit BlockUI(const BlockBaseT &b, QWidget *parent = nullptr)
		: BlockBaseT(b), QWidget(parent), label(b.name.c_str(), this)
	{
		for(size_t i = 0; i < BlockBaseT::InputCount(); i++) {
			inputs.push_back(InPortUI(InPort(BlockBaseT::Input(i), *this), parent));
		}
		for(size_t i = 0; i < BlockBaseT::OutputCount(); i++) {
			outputs.push_back(OutPortUI(OutPort(BlockBaseT::Output(i), *this), parent));
		}

		int input_w = (*std::max_element(inputs.begin(), inputs.end(),
			[] (const InPortUI &a, const InPortUI &b) { return a.getWidth() < b.getWidth(); }
		)).getWidth();
		int output_w = (*std::max_element(outputs.begin(), outputs.end(),
			[] (const OutPortUI &a, const OutPortUI &b) { return a.getWidth() < b.getWidth(); }
		)).getWidth();

		height = (static_cast<int>(std::max(inputs.size(), outputs.size()))) * Style::PortMarginV +
				 std::max(Style::PortMarginV, Style::NodeNameHeight);
		width = std::max(input_w + output_w, Style::NodeMinWidth);
		width = std::max(width, Style::NodeNamePadding * 2 + QApplication::fontMetrics().width(label.text()));

		resize(width + 1, height + 1);

		Move(0, 0);

		show();
		this->label.show();
	}

	InPort & Input(std::size_t id) override
	{
		return inputs[id];
	}

	std::size_t InputCount() override
	{
		return inputs.size();
	}

	OutPort & Output(std::size_t id) override
	{
		return outputs[id];
	}

	std::size_t OutputCount() override
	{
		return outputs.size();
	}

	void Move(int x, int y)
	{
		move(x, y);

		label.move(0, Style::NodeNamePadding);
		label.setFixedWidth(width);
		label.setAlignment(Qt::AlignCenter);

		int offset = std::max(Style::PortMarginV, Style::NodeNameHeight);
		for(auto &in : inputs) {
			in.Move(x, y + offset);
			offset += Style::PortMarginV;
		}
		offset = std::max(Style::PortMarginV, Style::NodeNameHeight);
		for(auto &out : outputs) {
			out.Move(x + width, y + offset);
			offset += Style::PortMarginV;
		}
	}
	void Highlight(bool enable)
	{
		this->highlight = enable;
		update();
	}

protected:
	void paintEvent(QPaintEvent *event) override
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
	void mouseMoveEvent(QMouseEvent *event) override
	{
		if (!drag) {
			drag = true;
			drag_p = event->pos();
		}
		QPoint tmp = pos() + event->pos() - drag_p;
		Move(tmp.x(), tmp.y());
	}
	void mouseReleaseEvent(QMouseEvent *event) override
	{
		(event);
		drag = false;
	}
	void enterEvent(QEvent *event) override
	{
		(event);
		static_cast<GraphUI&>(this->graph).hideHoverConnectionUI();
	}
};

#endif // BLOCK_UI_H
