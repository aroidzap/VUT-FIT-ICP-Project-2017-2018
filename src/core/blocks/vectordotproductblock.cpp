#include "vectordotproductblock.h"
#include "../types/types.h"

VectorDotProductBlock::VectorDotProductBlock(Graph &g)
    : BlockBase(g, VECTOR_DOTPRODUCT, "2D Vector Dot Product",
    {
        InPort(*this, vec2(), "A"),
        InPort(*this, vec2(), "B")
    },
    {
        OutPort(*this, vec2(), "Out")
    }
    ){}

void VectorDotProductBlock::Compute()
{
    this->Output(0)["x"] = this->Input(0)["x"] * this->Input(1)["x"];
    this->Output(0)["y"] = this->Input(0)["y"] * this->Input(1)["y"];
}
