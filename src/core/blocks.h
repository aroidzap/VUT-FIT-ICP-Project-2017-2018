#ifndef BLOCKS_H
#define BLOCKS_H

enum BlockType {
	// Input
	SCAL_INPUT = 0,
	VECTOR_INPUT = 1,
	MAT2_INPUT = 2,
	// Output
	SCAL_OUTPUT = 3,
	VECTOR_OUTPUT = 4,
	MAT2_OUTPUT = 5,
	
	// Vector
	VECTOR_ADD = 10,
	VECTOR_SUB = 11,
    VECTOR_DOTPRODUCT = 12,
	// Scalar
    SCALAR_ADD = 13,
    SCALAR_SUB = 14,
    SCALAR_MUL = 15,
	// Matrix
	MAT_ADD = 16,
    MAT_MUL = 17
};

#endif // BLOCKS_H
