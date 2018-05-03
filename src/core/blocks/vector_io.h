#ifndef VECTORINPUT_H
#define VECTORINPUT_H

#include "../blockbase.h"
#include "../graph.h"

class VectorInput : public BlockBase
{
public:
	VectorInput(Graph &g);
	void Compute() override;
	virtual ~VectorInput() = default;
};

class VectorOutput : public BlockBase
{
public:
	VectorOutput(Graph &g);
	void Compute() override;
	virtual ~VectorOutput() = default;
};

#endif // VECTORADDBLOCK_H
