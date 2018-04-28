#include "tooltip.h"
#include "style.h"

#include <QPainter>
#include <QPainterPath>

Tooltip::Tooltip(QWidget *parent) : QWidget(parent) {
	setAttribute(Qt::WA_TransparentForMouseEvents);
}

void Tooltip::Move(int x, int y){
	move(x - width() / 2, y - height() / 2);
}

void Tooltip::Text(std::string text){
	this->text = text;
}

void Tooltip::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.setPen(Style::TooltipOutlineCol);
	painter.setBrush(Style::TooltipBackgroundCol);

	QPainterPath path;
	path.addRoundedRect(QRectF(.5, .5, width() - 1, height() - 1), Style::TooltipRoundSize, Style::TooltipRoundSize);

	painter.drawPath(path);

	painter.setPen(Style::TooltipTextCol);
	painter.drawText(16,16,text.c_str()); //TODO: style
}
