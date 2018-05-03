#ifndef SCALAR_IO_H
#define SCALAR_IO_H

#include "../blockbase.h"
#include "../graph.h"

class ScalarInput : public BlockBase
{
public:
	ScalarInput(Graph &g);
	void Compute() override;
	virtual ~ScalarInput() = default;
};

class ScalarOutput : public BlockBase
{
public:
	ScalarOutput(Graph &g);
	void Compute() override;
	virtual ~ScalarOutput() = default;
};

#endif // SCALAR_IO_H
