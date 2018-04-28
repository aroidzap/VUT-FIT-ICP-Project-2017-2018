#include "connection.h"
#include "style.h"

#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <algorithm>

Connection::Connection(QWidget *parent) : QWidget(parent), t(parent)
{
	this->a = QPoint(0,0);
	this->b = QPoint(100,100);
	resize(parent->size());
	show();
	setMouseTracking(true);
}

QPainterPath Connection::computePath()
{
	QPoint left = this->a;
	QPoint right = this->b;

	QPainterPath path;
	path.moveTo(left);
	int cp = std::max(abs(left.y() - right.y())/3, abs(left.x() - right.x())/2); //control point
	path.cubicTo(left + QPoint(cp, 0), right + QPoint(-cp, 0), right);

	return path;
}

double Connection::getValue(){
	return 0.0;
}
void Connection::showValue(){
	t.move(mapFromGlobal(QCursor::pos()));
	t.Text("value = " + std::to_string(getValue()));
	t.show();
	t.raise();
}
void Connection::hideValue(){
	t.hide();
}
void Connection::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen p(Style::ConnectionCol);
	if(hover){
		p.setWidth(2);
		showValue();
	} else {
		hideValue();
	}
	painter.setPen(p);
	painter.drawPath(computePath());
}

void Connection::mouseMoveEvent(QMouseEvent *event)
{
	QPoint off = QPoint(Style::ConnectionHoverSize / 2, Style::ConnectionHoverSize / 2);
	hover = computePath().intersects(QRectF(event->pos() - off, event->pos() + off));
	update();
}

void Connection::leaveEvent(QEvent *event)
{
	hover = false;
	update();
}
