/** ICP Project 2017/2018: BlockEditor
 * @file matmulvecblock.cpp
 * @brief Matrix and vector multiplication block's operation and ports definition
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#include "matmulvecblock.h"
#include "../types/types.h"
#include "../blocks.h"

MatMulVecBlock::MatMulVecBlock(Graph &g)
	: BlockBase(g, MAT_MUL_VEC, BLOCK_NAME.at(MAT_MUL_VEC),
	{
		InPort(*this, mat2(), "Mat"),
		InPort(*this, vec2(), "Vec")
	},
	{
		OutPort(*this, vec2(), "Out")
	}
	){}

void MatMulVecBlock::Compute()
{
	this->Output(0)["x"] = (this->Input(0)["m11"] * this->Input(1)["x"]) + (this->Input(0)["m12"] * this->Input(1)["y"]);
	this->Output(0)["y"] = (this->Input(0)["m21"] * this->Input(1)["x"]) + (this->Input(0)["m22"] * this->Input(1)["y"]);
}
