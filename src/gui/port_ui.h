/** ICP Project 2017/2018: BlockEditor
 * @file port_ui.h
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
 * @brief The base abstract class of port GUI representation
 */
class PortBaseUI : public QWidget
{
protected:
	//! Parent widget
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
	//! Move to coordinates
	virtual void Move(int x, int y) = 0;
	//! Get width of Port GUI widget
	int getWidth() const;
};

/**
 * @brief Input ports GUI representation
 */
class InPortUI : public PortBaseUI, public InPort
{
public:
	//! Copy constructor
	InPortUI(const InPortUI &other);
	//! Input port constructor (decorator pattern)
	explicit InPortUI(const InPort &p, QWidget *parent = nullptr);
	//! Move to coordinates
	void Move(int x, int y) override;
protected:
	//! Event that invokes actions triggered by mouse movement
	void mouseMoveEvent(QMouseEvent *event) override;
	//! Event that invokes actions triggered by mouse clicks
	void mousePressEvent(QMouseEvent *) override;
};

/**
 * @brief Output ports GUI representation
 */
class OutPortUI : public PortBaseUI, public OutPort
{
public:
	//! Copy constructor
	OutPortUI(const OutPortUI &other);
	//! Output port constructor (decorator pattern)
	explicit OutPortUI(const OutPort &p, QWidget *parent = nullptr);
	//! Move to coordinates
	void Move(int x, int y) override;
protected:
	//! Event that invokes actions triggered by mouse movement
	void mouseMoveEvent(QMouseEvent *event) override;
	//! Event that invokes actions triggered by mouse clicks
	void mousePressEvent(QMouseEvent *) override;
};

#endif // PORT_UI_H
