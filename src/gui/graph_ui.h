#ifndef GRAPH_UI_H
#define GRAPH_UI_H

#include <QWidget>
#include "../core/graph.h"
#include "blockfactory_ui.h"

class GraphUI : public QWidget, public Graph
{
	Q_OBJECT
private:
	BlockFactoryUI bf;
	BlockFactory & GetBlockFactory() override;
public:
	GraphUI();
};

#endif // GRAPH_UI_H
