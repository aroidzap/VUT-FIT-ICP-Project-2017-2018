/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: port_ui.h
*/

#ifndef PORT_UI_H
#define PORT_UI_H

#include <QPaintEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <string>
#include "../core/port.h"

class PortBaseUI : public QWidget
{
protected:
	QWidget *p;
	bool hover = false;
	QLabel label;
	PortBaseUI(const std::string name, QWidget *parent = nullptr);

	void paintEvent(QPaintEvent *) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *) override;
public:
	QPoint Pos();
	virtual void Move(int x, int y) = 0;
	int getWidth() const;
};

class InPortUI : public PortBaseUI, public InPort
{
public:
	InPortUI(const InPortUI &other);
	explicit InPortUI(const InPort &p, QWidget *parent = nullptr);
	void Move(int x, int y) override;
protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *) override;
};

class OutPortUI : public PortBaseUI, public OutPort
{
public:
	OutPortUI(const OutPortUI &other);
	explicit OutPortUI(const OutPort &p, QWidget *parent = nullptr);
	void Move(int x, int y) override;
protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *) override;
};

#endif // PORT_UI_H
