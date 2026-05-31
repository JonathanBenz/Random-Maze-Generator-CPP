#include <iostream>
#include "app.h"
#include "grid/public/cell.h"
#include "grid/public/grid.h"
#include "grid/public/distance_grid.h"
#include "grid/public/distances.h"
#include "graphics/public/graphics.h"
#include "algorithms/public/algorithmcontext.h"
#include "demos/public/dijkstra_demo.h"

/* Prototype Functions */
void RunDijkstraDemo(PathType pathType);
/* ******************* */

int main()
{
	if (Graphics::InitOpenGL() == -1) return -1;

	/*Grid grid(8, 8);
	AlgorithmContext randomMazeGenerator;
	App app(&grid, &randomMazeGenerator);
	glfwSetWindowUserPointer(Graphics::Window, &app);
	randomMazeGenerator.SetStrategy(MazeAlgorithm::Sidewinder);
	app.GenerateMaze();
	std::cout << grid << std::endl;*/

	RunDijkstraDemo(PathType::Shortest);

	Graphics::InitShaders();
	Graphics::UpdateLoop();
    Graphics::CleanUp();
}

void RunDijkstraDemo(PathType pathType)
{
	DijkstraDemo dijkstra;
	unsigned int rows = 64;
	unsigned int columns = 64;
	dijkstra.SetGridSize(rows, columns);
	dijkstra.SetMazeGenAlgorithm(MazeAlgorithm::Sidewinder);
	dijkstra.SetStartCell(rows - 1, 0);
	dijkstra.SetGoalCell(rows - 1, columns - 1);

	Graphics::bShouldDrawShortestPath = false;
	Graphics::bShouldDrawLongestPath = true;

	switch (pathType)
	{
	case PathType::Shortest:
		dijkstra.RunShortestPathDemo();
		break;

	case PathType::Longest:
		dijkstra.RunLongestPathDemo();
		break;
	}
}