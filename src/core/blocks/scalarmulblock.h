#ifndef SCALARMULBLOCK_H
#define SCALARMULBLOCK_H

#include "../blockbase.h"
#include "../graph.h"

class ScalarMulBlock : public BlockBase
{
public:
    ScalarMulBlock(Graph &g);
    void Compute() override;
    virtual ~ScalarMulBlock() = default;
};

#endif // SCALARMULBLOCK_H

