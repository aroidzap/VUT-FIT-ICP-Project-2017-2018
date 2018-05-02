#ifndef CONNECTION_UI_H
#define CONNECTION_UI_H

#include <QWidget>
#include <QPaintEvent>

#include "tooltip.h"
#include "port_ui.h"

class ConnectionUI : public QWidget
{
private:
	QWidget *p;
	Tooltip t;
	InPortUI *in;
	OutPortUI *out;
	QPainterPath computePath();
	bool hover = false;
	void showValue();
	void hideValue();
public:
	explicit ConnectionUI(InPortUI *in, OutPortUI *out, QWidget *parent = nullptr);
	ConnectionUI(const ConnectionUI &other);
	bool operator==(const InPort &p);
	bool operator==(const OutPort &p);
	bool operator==(const Port &p);
	friend bool operator==(const ConnectionUI &a, const ConnectionUI &b);
	bool mouseHover(QPoint mouse);
	bool mouseHover(bool hover);
protected:
	void paintEvent(QPaintEvent *event) override;
};

#endif // CONNECTION_UI_H
