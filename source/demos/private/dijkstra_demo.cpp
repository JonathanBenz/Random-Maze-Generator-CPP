#include "../public/dijkstra_demo.h"
#include "../../graphics/public/graphics.h"

void DijkstraDemo::InitApp()
{
	m_App.InitApp(&m_Grid, &m_RandomMazeGenerator);
	glfwSetWindowUserPointer(Graphics::Window, &m_App);
	bIsAppInitialized = true;

	m_App.OnMazeGenerated.push_back(
		[this]()
		{
			OnMazeGenerated();
		});
}

void DijkstraDemo::OnMazeGenerated()
{
	if (Graphics::bShouldDrawShortestPath)
		UploadShortestPathVertices();

	if (Graphics::bShouldDrawLongestPath)
		UploadLongestPathVertices();
}

void DijkstraDemo::SetGridSize(unsigned int rows, unsigned int columns)
{
	m_Grid.InitGrid(rows, columns);
}

void DijkstraDemo::SetMazeGenAlgorithm(MazeAlgorithm algo)
{
	m_RandomMazeGenerator.SetStrategy(algo);
}

void DijkstraDemo::SetStartCell(int row, int column)
{
	m_StartingCell = m_Grid.GetCell(row, column);
}

void DijkstraDemo::SetGoalCell(int row, int column)
{
	m_GoalCell = m_Grid.GetCell(row, column);
}

void DijkstraDemo::RunShortestPathDemo()
{
	if (!m_StartingCell || !m_GoalCell) return;
	if (!bIsAppInitialized) InitApp();

	m_App.GenerateMaze();

	Distances distances = m_StartingCell->GetDistancesFromThisCell();
	m_Grid.SetDistances(distances.PathTo(m_GoalCell));
	std::cout << m_Grid << std::endl;
}

// TLDR: Get the furthest cell away from the furthest cell. 
void DijkstraDemo::RunLongestPathDemo()
{
	if (!m_StartingCell) return;
	if (!bIsAppInitialized) InitApp();

	m_App.GenerateMaze();

	Distances distances = m_StartingCell->GetDistancesFromThisCell();
	Cell* newStartCell = distances.GetMaxCell();

	Distances newDistances = newStartCell->GetDistancesFromThisCell();
	Cell* goalCell = newDistances.GetMaxCell();

	m_Grid.SetDistances(newDistances.PathTo(goalCell));
	std::cout << m_Grid << std::endl;
}

void DijkstraDemo::UploadShortestPathVertices()
{
	Graphics::ShortestPathVertices.clear();
	if (!m_StartingCell || !m_GoalCell) return;

	Distances distances = m_StartingCell->GetDistancesFromThisCell();
	Distances shortestPath = distances.PathTo(m_GoalCell);

	// These are already sorted for us in order from start cell to goal cell
	std::vector<Cell*> shortestPathCells = shortestPath.GetCells();
	size_t shortestPathSize = shortestPathCells.size();

	for (size_t i = 0; i + 1 < shortestPathSize; i++)
	{
		Cell* currentCell = shortestPathCells[i];
		Cell* nextCell = shortestPathCells[i + 1];

		// Calculate vertices (center of current cell, center of next cell)
		float x1 = static_cast<float>(currentCell->GetColumn()) + 0.5f;
		float y1 = static_cast<float>(currentCell->GetRow()) + 0.5f;

		float x2 = static_cast<float>(nextCell->GetColumn()) + 0.5f;
		float y2 = static_cast<float>(nextCell->GetRow()) + 0.5f;

		// Add Line
		Graphics::AddShortestPathLine(x1, y1, x2, y2);
	}
}

void DijkstraDemo::UploadLongestPathVertices()
{
	Graphics::LongestPathVertices.clear();
	if (!m_StartingCell) return;

	Distances distances = m_StartingCell->GetDistancesFromThisCell();
	Cell* newStartCell = distances.GetMaxCell();

	Distances newDistances = newStartCell->GetDistancesFromThisCell();
	Cell* goalCell = newDistances.GetMaxCell();

	Distances longestPath = newDistances.PathTo(goalCell);

	// These are already sorted for us in order from start cell to goal cell
	std::vector<Cell*> longestPathCells = longestPath.GetCells();
	size_t longestPathSize = longestPathCells.size();

	for (size_t i = 0; i + 1 < longestPathSize; i++)
	{
		Cell* currentCell = longestPathCells[i];
		Cell* nextCell = longestPathCells[i + 1];

		// Calculate vertices (center of current cell, center of next cell)
		float x1 = static_cast<float>(currentCell->GetColumn()) + 0.5f;
		float y1 = static_cast<float>(currentCell->GetRow()) + 0.5f;

		float x2 = static_cast<float>(nextCell->GetColumn()) + 0.5f;
		float y2 = static_cast<float>(nextCell->GetRow()) + 0.5f;

		// Add Line
		Graphics::AddLongestPathLine(x1, y1, x2, y2);
	}
}