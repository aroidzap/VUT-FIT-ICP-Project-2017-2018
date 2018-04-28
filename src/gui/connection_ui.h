#ifndef CONNECTION_UI_H
#define CONNECTION_UI_H

#include <QWidget>
#include <QPoint>
#include <QPaintEvent>
#include <QMouseEvent>

#include "tooltip.h"

class ConnectionUI : public QWidget
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
	explicit ConnectionUI(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;
};

#endif // CONNECTION_UI_H
