#include "connection_ui.h"
#include "style.h"

#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <algorithm>

ConnectionUI::ConnectionUI(InPortUI *in, OutPortUI *out, QWidget *parent)
	: QWidget(parent), t(parent), in(in), out(out)
{
	resize(parent->size());
	show();
	setMouseTracking(true);
}

QPainterPath ConnectionUI::computePath()
{
	QPoint left = this->in->pos();
	QPoint right = this->out->pos();

	QPainterPath path;
	path.moveTo(left);
	int cp = std::max(abs(left.y() - right.y())/3, abs(left.x() - right.x())/2); //control point
	path.cubicTo(left + QPoint(cp, 0), right + QPoint(-cp, 0), right);

	return path;
}

void ConnectionUI::showValue(){
	t.move(mapFromGlobal(QCursor::pos()));
	t.Text(out->Value());
	t.show();
	t.raise();
}
void ConnectionUI::hideValue(){
	t.hide();
}

void ConnectionUI::paintEvent(QPaintEvent *event)
{
	(event);
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

void ConnectionUI::mouseMoveEvent(QMouseEvent *event)
{
	QPoint off = QPoint(Style::ConnectionHoverSize / 2, Style::ConnectionHoverSize / 2);
	hover = computePath().intersects(QRectF(event->pos() - off, event->pos() + off));
	update();
}

void ConnectionUI::leaveEvent(QEvent *event)
{
	(event);
	hover = false;
	update();
}
