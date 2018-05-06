/** ICP Project 2017/2018: BlockEditor
 * @file graph_ui.h
 * @brief Port GUI representation
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
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

/**
 * @brief The plain port (no data type) GUI representation
 */
class PortBaseUI : public QWidget
{
protected:
	//! Port widget
	QWidget *p;
	//! Port hover state
	bool hover = false;
	//! Port label
	QLabel label;
	/**
	 * @brief Plain ort constructor
	 * @param name
	 * @param parent Parent block's widget
	 */
	PortBaseUI(const std::string name, QWidget *parent = nullptr);

	//! Rendering event
	void paintEvent(QPaintEvent *) override;
	//! Event that invokes actions triggered by mouse movement
	void mouseMoveEvent(QMouseEvent *event) override;
	//! Event that invokes actions triggered by mouse leaving the port
	void leaveEvent(QEvent *) override;
public:
	//! Block's position - coordinates
	QPoint Pos();
	//! Function moves the block inside the parent widget
	virtual void Move(int x, int y) = 0;
	//! Get width required by block's content
	int getWidth() const;
};

/**
 * @brief Input ports GUI representation
 */
class InPortUI : public PortBaseUI, public InPort
{
public:
	//! Constructor
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
