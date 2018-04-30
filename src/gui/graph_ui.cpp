#include "graph_ui.h"

BlockFactory &GraphUI::GetBlockFactory()
{
	return bf;
}

GraphUI::GraphUI() : bf(*this) { }
