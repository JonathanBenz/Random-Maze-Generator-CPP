#include "../public/algorithmcontext.h"
#include "../../grid/public/grid.h"
#include "../public/imazealgorithms.h"
#include "../public/binarytreestrategy.h"
#include "../public/sidewinderstrategy.h"
#include "../public/aldous_broder.h"
#include "../public/wilsons.h"

void AlgorithmContext::SetStrategy(MazeAlgorithm algorithm)
{
	switch (algorithm)
	{
	case MazeAlgorithm::BinaryTree:
		m_Strategy = std::make_unique<BinaryTreeStrategy>();
		break;

	case MazeAlgorithm::Sidewinder:
		m_Strategy = std::make_unique<SidewinderStrategy>();
		break;

	case MazeAlgorithm::AldousBroder:
		m_Strategy = std::make_unique<AldousBroder>();
		break;

	case MazeAlgorithm::Wilsons:
		m_Strategy = std::make_unique<Wilsons>();
		break;
	}
}

void AlgorithmContext::ExecuteOn(Grid& grid)
{
	m_Strategy->GenerateMaze(grid);
}