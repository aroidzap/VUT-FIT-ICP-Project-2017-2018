#include "port_ui.h"
#include "style.h"
#include <QPainter>
#include <QPainterPath>

PortUI::PortUI(std::string name, bool input, QWidget *parent) : QWidget(parent), label(name.c_str(), parent), input(input)
{
	resize(Style::PortSize + 2, Style::PortSize + 2);
	Move(0, 0);

	show();
	label.show();

	setMouseTracking(true);
}

int PortUI::getWidth() const{
	return Style::PortNamePadding * 2 + label.width();
}

void PortUI::Move(int x, int y)
{
	move(x - Style::PortSize/2 - 1, y - Style::PortSize/2 - 1);
	if(input) {
		label.move(x + Style::PortNamePadding, y - label.height() / 2);
	} else {
		label.move(x - Style::PortNamePadding - label.width(), y - label.height() / 2);
	}
}

void PortUI::paintEvent(QPaintEvent *event)
{
	(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.setPen(Style::PortOutlineCol);
	if(hover){
		painter.setBrush(Style::PortHoverCol); //hover
	} else {
		painter.setBrush(Style::PortFreeCol); //free
	}
	painter.drawEllipse(QPoint((Style::PortSize/2 + 1), (Style::PortSize/2 + 1)),
						Style::PortDrawSize/2, Style::PortDrawSize/2);
}

void PortUI::mouseMoveEvent(QMouseEvent *event)
{
	QPoint diff = (event->pos() - QPoint(Style::PortSize/2, Style::PortSize/2));
	int dist = sqrt(diff.x()*diff.x() + diff.y()*diff.y());
	hover = (dist <= Style::PortSize/2);
	update();
}

void PortUI::leaveEvent(QEvent *event)
{
	(event);
	hover = false;
	update();
}

void PortUI::mouseReleaseEvent(QMouseEvent *event)
{
	(event);
}
