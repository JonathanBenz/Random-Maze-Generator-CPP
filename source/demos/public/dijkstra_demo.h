#pragma once
#include <iostream>
#include "../../app.h"
#include "../../grid/public/cell.h"
#include "../../grid/public/grid.h"
#include "../../grid/public/distance_grid.h"
#include "../../grid/public/distances.h"
#include "../../algorithms/public/algorithmcontext.h"

enum class PathType 
{ 
	None,
	Shortest, 
	Longest, 
	Both
};

class DijkstraDemo
{
public:
	void SetGridSize(unsigned int rows, unsigned int columns);
	void SetMazeGenAlgorithm(MazeAlgorithm algo);
	void SetStartCell(int row, int column);
	void SetGoalCell(int row, int column);

	void RunNoPaths();
	void RunShortestPathDemo();
	void RunLongestPathDemo();
	void RunBothDemos();

	void UploadShortestPathVertices();
	void UploadLongestPathVertices();

private:
	void InitApp();
	void OnMazeGenerated();

private:
	DistanceGrid m_Grid;
	AlgorithmContext m_RandomMazeGenerator;
	App m_App;
	PathType pathType = PathType::Longest;
	Cell* m_StartingCell = nullptr;
	Cell* m_GoalCell = nullptr;
	bool bIsAppInitialized = false;
};