#ifndef CONNECTION_UI_H
#define CONNECTION_UI_H

#include <QPoint>
#include <QWidget>
#include <QPaintEvent>

#include "tooltip.h"
#include "port_ui.h"

class ConnectionUI : public QWidget
{
protected:
	QWidget *p;
	Tooltip t;
	InPortUI *in;
	OutPortUI *out;
	QPainterPath computePath();
	bool hover = false;
	void showValue();
	void hideValue();
	virtual QPoint getLeft();
	virtual QPoint getRight();
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

class TempConnectionUI : public ConnectionUI
{
private:
	InPort **in_c;
	OutPort **out_c;
protected:
	QPoint getLeft() override;
	QPoint getRight() override;
	void paintEvent(QPaintEvent *event) override;
public:
	TempConnectionUI(InPort **in, OutPort **out, QWidget *parent = nullptr);
};

#endif // CONNECTION_UI_H
