/** ICP Project 2017/2018: BlockEditor
 * @file matrixmulblock.cpp
 * @brief Matrix multiplication block's operation and ports definition
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#include "matrixmulblock.h"
#include "../types/types.h"
#include "../blocks.h"

MatrixMulBlock::MatrixMulBlock(Graph &g)
	: BlockBase(g, MAT_MUL, BLOCK_NAME.at(MAT_MUL),
    {
        InPort(*this, mat2(), "A"),
        InPort(*this, mat2(), "B")
    },
    {
        OutPort(*this, mat2(), "Out")
    }
    ){}

void MatrixMulBlock::Compute()
{
	this->Output(0)["m11"] = (this->Input(0)["m11"] * this->Input(1)["m11"]) + (this->Input(0)["m12"] * this->Input(1)["m21"]);
	this->Output(0)["m12"] = (this->Input(0)["m11"] * this->Input(1)["m12"]) + (this->Input(0)["m12"] * this->Input(1)["m22"]);
	this->Output(0)["m21"] = (this->Input(0)["m21"] * this->Input(1)["m11"]) + (this->Input(0)["m22"] * this->Input(1)["m21"]);
	this->Output(0)["m22"] = (this->Input(0)["m21"] * this->Input(1)["m12"]) + (this->Input(0)["m22"] * this->Input(1)["m22"]);
}
