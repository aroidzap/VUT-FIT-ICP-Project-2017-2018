/** ICP Project 2017/2018: BlockEditor
 * @file connection_ui.h
 * @brief Connection graphical representation
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef CONNECTION_UI_H
#define CONNECTION_UI_H

#include <QPoint>
#include <QWidget>
#include <QPaintEvent>

#include "tooltip.h"
#include "port_ui.h"

//! Widget for connection graphical representation
class ConnectionUI : public QWidget
{
protected:
	//! Parent widget
	QWidget *p;
	//! Tooltip shown after hovering a connection
	Tooltip t;
	//! Connection terminates here
	InPortUI *in;
	//! Connection starts here
	OutPortUI *out;
	//! Adjusts the line shape and position
	QPainterPath computePath();
	//! Mouse hover state
	bool hover = false;
	//! Showing the tooltip
	void showValue();
	//! Hiding the tooltip
	void hideValue();
	//! Provides start point for path compution
	virtual QPoint getLeft();
	//! Provides end point for path compution
	virtual QPoint getRight();
public:
	/**
	 * @brief Connection constructor
	 * @param in Input port
	 * @param out Output port
	 * @param parent Parent widget containing the scheme
	 */
	explicit ConnectionUI(InPortUI *in, OutPortUI *out, QWidget *parent = nullptr);
	//! Connection constructor
	ConnectionUI(const ConnectionUI &other);
	//! Redraw connection above other elements
	void Redraw();
	//! Overloading operator == for input port comparison
	bool operator==(const InPort &p);
	//! Overloading operator == for output port comparison
	bool operator==(const OutPort &p);
	//! Overloading operator == for any port comparison
	bool operator==(const Port &p);
	//! Overloading operator == for connection comparison (based on input ports)
	friend bool operator==(const ConnectionUI &a, const ConnectionUI &b);
	//! Activating hover state by mouse
	bool mouseHover(QPoint mouse);
	//! Activating hover state by function call
	bool mouseHover(bool hover);
protected:
	void paintEvent(QPaintEvent *event) override;
};

//! Temporary connection for visualising unfinished connection
class TempConnectionUI : public ConnectionUI
{
private:
	//! Input port
	InPort **in_c;
	//! Output port
	OutPort **out_c;
protected:
	//! Get starting coordinates
	QPoint getLeft() override;
	//! Get end coordinates
	QPoint getRight() override;
	//! Actual rendering of the connection
	void paintEvent(QPaintEvent *) override;
public:
	/**
	 * @brief Temp connection constructor
	 * @param in Input port
	 * @param out Output port
	 * @param parent Parent widget where the whole scheme is stored
	 */
	TempConnectionUI(InPort **in, OutPort **out, QWidget *parent = nullptr);
};

#endif // CONNECTION_UI_H
