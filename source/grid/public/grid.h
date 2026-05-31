#pragma once
#include <vector>
#include <ostream>
#include <string>

class Cell;

class Grid
{
public:
	Grid() = default;
	Grid(unsigned int rows, unsigned int columns);
	virtual ~Grid();

	void InitGrid(unsigned int rows, unsigned int columns);
	void CleanupGrid();

	friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
	void UploadGridVertices();

	template <typename Func>
	void EachRow(Func&& fn)
	{
		for (unsigned int row = 0; row < m_Rows; row++)
		{
			fn(*this, GetCell(row, 0));
		}
	}

	// Returns the row array of Cells within a specific row. 
	std::vector<Cell*> GetCellRow(unsigned int row);

	template <typename Func>
	void EachCell(Func&& fn)
	{
		for (Cell* cell : m_Grid)
		{
			fn(*this, cell);
		}
	}

public: // GETTERS & SETTERS
	unsigned int GetTotalRows() const { return m_Rows; }
	unsigned int GetTotalColumns() const { return m_Columns; }
	unsigned int GetSize() const { return m_Rows * m_Columns; }

	virtual Cell* GetCell(int row, int column);
	virtual const Cell* GetCell(int row, int column) const;

	Cell* GetRandomCell();
	const Cell* GetRandomCell() const;

protected:
	virtual void PrepareGrid();
	virtual void ConfigureCells();
	
	virtual std::string GetContentsOf(const Cell* cell) const;

private:
	unsigned int m_Rows{};
	unsigned int m_Columns{};

	// Flattened 2D Dynamic Array
	std::vector<Cell*> m_Grid;
};