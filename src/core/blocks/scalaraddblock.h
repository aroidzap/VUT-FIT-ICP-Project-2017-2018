#ifndef SCALARADDBLOCK
#define SCALARADDBLOCK

#include "../blockbase.h"
#include "../graph.h"

class ScalarAddBlock : public BlockBase
{
public:
    ScalarAddBlock(Graph &g);
    void Compute() override;
    virtual ~ScalarAddBlock() = default;
};

#endif // SCALARADDBLOCK

