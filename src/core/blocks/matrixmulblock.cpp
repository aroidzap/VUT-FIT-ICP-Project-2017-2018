/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: matrixmulblock.cpp
*/

#include "matrixmulblock.h"
#include "../types/types.h"

MatrixMulBlock::MatrixMulBlock(Graph &g)
	: BlockBase(g, MAT_MUL, "2D Matrix Multiplication",
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
