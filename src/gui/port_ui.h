#ifndef PORT_UI_H
#define PORT_UI_H

#include <QPaintEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QLabel>
#include <string>
#include "../core/port.h"

class PortBaseUI : public QWidget
{
	Q_OBJECT
protected:
	bool hover = false;
	QLabel label;
	PortBaseUI(const std::string name, QWidget *parent = nullptr);

	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;
public:
	virtual void Move(int x, int y) = 0;
	int getWidth() const;
};

class InPortUI : public PortBaseUI, public InPort
{
public:
	explicit InPortUI(const InPort &p, QWidget *parent = nullptr);
	void Move(int x, int y) override;
};

class OutPortUI : public PortBaseUI, public OutPort
{
public:
	explicit OutPortUI(const OutPort &p, QWidget *parent = nullptr);
	void Move(int x, int y) override;
};

#endif // PORT_UI_H
