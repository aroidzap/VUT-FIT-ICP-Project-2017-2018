#ifndef CONNECTION_UI_H
#define CONNECTION_UI_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>

#include "tooltip.h"
#include "port_ui.h"

class ConnectionUI : public QWidget
{
private:
	Tooltip t;
	InPortUI *in;
	OutPortUI *out;
	QPainterPath computePath();
	bool hover = false;
	void showValue();
	void hideValue();
public:
	explicit ConnectionUI(InPortUI *in, OutPortUI *out, QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;
};

#endif // CONNECTION_UI_H
