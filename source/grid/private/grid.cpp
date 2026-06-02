#include "../public/grid.h"
#include "../public/cell.h"
#include "../../utils.h"
#include "../../graphics/public/graphics.h"

Grid::Grid(unsigned int rows, unsigned int columns)
{
	InitGrid(rows, columns);
}

void Grid::InitGrid(unsigned int rows, unsigned int columns)
{
	CleanupGrid();

	m_Rows = rows;
	m_Columns = columns;
	Graphics::Rows = static_cast<float>(rows);
	Graphics::Columns = static_cast<float>(columns);

	PrepareGrid();
	ConfigureCells();
}

Grid::~Grid()
{
	CleanupGrid();
}

void Grid::CleanupGrid()
{
	for (Cell* cell : m_Grid) delete cell;
	m_Grid.clear();
}

Cell* Grid::GetCell(int row, int column)
{
	if (row < 0 || row > static_cast<int>(m_Rows) - 1) return nullptr;
	if (column < 0 || column > static_cast<int>(m_Columns) - 1) return nullptr;

	return m_Grid.at(row * m_Columns + column);
}

const Cell* Grid::GetCell(int row, int column) const
{
	if (row < 0 || row > static_cast<int>(m_Rows) - 1) return nullptr;
	if (column < 0 || column > static_cast<int>(m_Columns) - 1) return nullptr;

	return m_Grid.at(row * m_Columns + column);
}

std::string Grid::GetContentsOf(const Cell* cell) const
{
	return " ";
}

std::vector<Cell*> Grid::GetCellRow(unsigned int row)
{
	std::vector<Cell*> cellRow;
	if (static_cast<int>(row) < 0 || row > m_Rows - 1) return cellRow;

	cellRow.reserve(static_cast<size_t>(m_Columns));
	for (unsigned int column = 0; column < m_Columns; column++)
		cellRow.push_back(GetCell(row, column));
	
	return cellRow;
}

Cell* Grid::GetRandomCell()
{
	unsigned int randRow = Utils::BoundedRand(m_Rows);
	unsigned int randColumn = Utils::BoundedRand(m_Columns);
	return GetCell(randRow, randColumn);
}

const Cell* Grid::GetRandomCell() const
{
	unsigned int randRow = Utils::BoundedRand(m_Rows);
	unsigned int randColumn = Utils::BoundedRand(m_Columns);
	return GetCell(randRow, randColumn);
}

std::vector<Cell*> Grid::GetDeadEnds()
{
	std::vector<Cell*> list;
	for (Cell* cell : m_Grid)
	{
		if (cell->GetLinks().size() == 1)
			list.push_back(cell);
	}

	return list;
}

void Grid::PrepareGrid()
{
	m_Grid.reserve(static_cast<size_t>(m_Rows * m_Columns));

	for (unsigned int row = 0; row < m_Rows; row++)
	{
		for (unsigned int column = 0; column < m_Columns; column++)
		{
			m_Grid.emplace_back(new Cell(row, column));
		}
	}
}

void Grid::ConfigureCells()
{
	for (Cell* cell : m_Grid)
	{
		unsigned int row = cell->GetRow();
		unsigned int column = cell->GetColumn();

		cell->SetNorthNeighbor(GetCell(row - 1, column));
		cell->SetSouthNeighbor(GetCell(row + 1, column));
		cell->SetEastNeighbor(GetCell(row, column + 1));
		cell->SetWestNeighbor(GetCell(row, column - 1));
	}
}

std::ostream& operator<<(std::ostream& os, const Grid& grid)
{
	std::string ASCII("\n   +");
	for (unsigned int i = 0; i < grid.m_Columns; i++) ASCII += "---+";
	ASCII += "\n";

	for (unsigned int row = 0; row < grid.m_Rows; row++)
	{
		std::string top("   |");
		std::string bottom("   +");
		for (unsigned int column = 0; column < grid.m_Columns; column++)
		{
			std::string body("   ");
			std::string eastBoundary;
			std::string southBoundary;
			std::string corner("+");

			if (const Cell* cell = grid.GetCell(row, column))
			{
				body = " " + grid.GetContentsOf(cell) + " ";
				eastBoundary = cell->IsLinked(cell->GetEastNeighbor()) ? " " : "|";
				southBoundary = cell->IsLinked(cell->GetSouthNeighbor()) ? "   " : "---";
			}

			else
			{
				eastBoundary = "|";
				southBoundary = "---";
			}

			top += body;
			top += eastBoundary;
			bottom += southBoundary;
			bottom += corner;
		}

		ASCII += top;
		ASCII += "\n";
		ASCII += bottom;
		ASCII += "\n";
	}

	os << ASCII;
	return os;
}

void Grid::UploadGridVertices()
{
	Graphics::GridVertices.clear();

	for (Cell* cell : m_Grid)
	{
		// Calculate vertices
		float x1 = static_cast<float>(cell->GetColumn());
		float y1 = static_cast<float>(cell->GetRow());
		float x2 = static_cast<float>(cell->GetColumn() + 1);
		float y2 = static_cast<float>(cell->GetRow() + 1);

		// Add Lines
		if (!cell->GetNorthNeighbor()) Graphics::AddGridLine(x1, y1, x2, y1);
		if (!cell->GetWestNeighbor()) Graphics::AddGridLine(x1, y1, x1, y2);

		if (!cell->IsLinked(cell->GetEastNeighbor())) Graphics::AddGridLine(x2, y1, x2, y2);
		if (!cell->IsLinked(cell->GetSouthNeighbor())) Graphics::AddGridLine(x1, y2, x2, y2);
	}
}