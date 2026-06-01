#pragma once
#include "imazealgorithms.h"
#include <memory>

class IMazeAlgorithm;
class Grid;

enum class MazeAlgorithm
{
	BinaryTree,
	Sidewinder,
	AldousBroder,
	Wilsons
};

class AlgorithmContext
{
public:
	void SetStrategy(MazeAlgorithm algorithm);
	void ExecuteOn(Grid& grid);

private:
	std::unique_ptr<IMazeAlgorithm> m_Strategy;
};