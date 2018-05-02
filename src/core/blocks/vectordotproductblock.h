#ifndef VECTORDOTPRODBLOCK_H
#define VECTORDOTPRODBLOCK_H

#include "../blockbase.h"
#include "../graph.h"

class VectorDotProductBlock : public BlockBase
{
public:
    VectorDotProductBlock(Graph &g);
    void Compute() override;
    virtual ~VectorDotProductBlock() = default;
};

#endif // VECTORDOTPRODBLOCK_H
