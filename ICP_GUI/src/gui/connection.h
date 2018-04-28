#ifndef CONNECTION_H
#define CONNECTION_H

#include <QWidget>
#include <QPoint>
#include <QPaintEvent>
#include <QMouseEvent>

#include "tooltip.h"

class Connection : public QWidget
{
	Q_OBJECT
private:
	Tooltip t;
	QPoint a, b;
	QPainterPath computePath();
	bool hover = false;
	double getValue();
	void showValue();
	void hideValue();
public:
	explicit Connection(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;
};

#endif // CONNECTION_H
