/** ICP Project 2017/2018: BlockEditor
 * @file matrixaddblock.cpp
 * @brief Matrix addition block's operation and ports definition
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#include "matrixaddblock.h"
#include "../types/types.h"
#include "../blocks.h"

MatrixAddBlock::MatrixAddBlock(Graph &g)
	: BlockBase(g, MAT_ADD, BLOCK_NAME.at(MAT_ADD),
    {
        InPort(*this, mat2(), "A"),
        InPort(*this, mat2(), "B")
    },
    {
        OutPort(*this, mat2(), "Out")
    }
    ){}

void MatrixAddBlock::Compute()
{
    this->Output(0)["m11"] = this->Input(0)["m11"] + this->Input(1)["m11"];
    this->Output(0)["m12"] = this->Input(0)["m12"] + this->Input(1)["m12"];
    this->Output(0)["m21"] = this->Input(0)["m21"] + this->Input(1)["m21"];
    this->Output(0)["m22"] = this->Input(0)["m22"] + this->Input(1)["m22"];
}
