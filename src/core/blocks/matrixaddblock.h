#ifndef MATRIXADDBLOCK
#define MATRIXADDBLOCK

#include "../blockbase.h"
#include "../graph.h"

class MatrixAddBlock : public BlockBase
{
public:
    MatrixAddBlock(Graph &g);
    void Compute() override;
    virtual ~MatrixAddBlock() = default;
};

#endif // MATRIXADDBLOCK

