#include "scalaraddblock.h"
#include "../types/types.h"

ScalarAddBlock::ScalarAddBlock(Graph &g)
    : BlockBase(g, SCALAR_ADD, "Scalar Addition",
    {
        InPort(*this, scal(), "A"),
        InPort(*this, scal(), "B")
    },
    {
        OutPort(*this, scal(), "Out")
    }
    ){}

void ScalarAddBlock::Compute()
{
    this->Output(0)["val"] = this->Input(0)["val"] + this->Input(1)["val"];
}
