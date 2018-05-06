/** ICP Project 2017/2018: BlockEditor
 * @file graph_ui.h
 * @brief Scheme GUI representation
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef GRAPH_UI_H
#define GRAPH_UI_H

#include <QMouseEvent>
#include <QPaintEvent>
#include <QWidget>
#include "../core/graph.h"
#include "blockfactory_ui.h"
#include "connection_ui.h"
#include "blockmenu.h"
#include <list>


class ConnectionUI;

/**
 * @brief Parent QWidget to all other widgets used in scheme
 */
class GraphUI : public QWidget, public Graph
{
public:
	InPort *in_click;
	OutPort *out_click;
private:
	TempConnectionUI tc;
	//! GUI Block factory
	BlockFactoryUI bf;
	BlockFactory & GetBlockFactory() override;
	//! Dragging state
	bool drag = false;
	//!
	QPoint drag_p;
	//! Rightclick dropdown menu for choosing a new block to add to the scheme
	BlockMenu block_menu;
	//! Right click dropdown menu for block options
	BlockDelete block_context_menu;
public:
	//! Offset to apply to new block's position
	QPoint pos_offset;
	//! List of graphical connections in GUI
	std::list<ConnectionUI*> ui_connections;
	GraphUI();
	//! Get block's position offset
	QPoint getOffset() const;
	//! Delete the current scheme, get ready for new scheme
	void clearGraph() override;
	/**
	 * @brief Load scheme from a file
	 * @param graph Scheme's parent widget
	 * @param merge Merge flag - file will merge into existing scheme if true
	 * @return True when file was loaded successfully, else false
	 */
	bool loadGraph(std::stringstream &graph, bool merge = false) override;
	/**
	 * @brief Prepare scheme for saving - generate stringstream GPH represaentation
	 * @return GPH stringstream representation
	 */
	std::stringstream saveGraph() override;
	//! Block's context menu
	void blockContextMenu(BlockBase *b);
	
	BlockBase *addBlock(BlockType t) override;
	//! Removes a block from the scheme
	void removeBlock(BlockBase *b) override;
	/**
	 * @brief Adds a connection to the scheme if all conditions are met
	 * @param a Output port where the connection starts
	 * @param b Input port where the connection ends
	 * @return True if connection was added, else false
	 */
	bool addConnection(OutPort &a, InPort &b) override;
	/**
	 * @brief Remove connection from the scheme
	 *
	 * @param p Input port
	 */
	void removeConnection(InPort &p) override;
	/**
	 * @brief Remove connection from the scheme
	 *
	 * @param p Output port
	 */
	void removeConnection(OutPort &p) override;
	/**
	 * @brief Replace detached side of the connection
	 * @param p Port, where the connection was detached
	 */
	void updateConnectionUI(Port &p);
	/**
	 * @brief Show tooltip when connection is hovered
	 * @param mouse QPoint coordinates
	 */
	void hoverConnectionUI(QPoint mouse);
	//!
	void hideHoverConnectionUI();
	bool allInputsConnected() override;
	void computeReset() override;
	bool computeStep() override;
	bool computeAll() override;
	~GraphUI();
protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *) override;
	void leaveEvent(QEvent *) override;
};

#endif // GRAPH_UI_H
