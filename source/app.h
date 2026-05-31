#pragma once
#include "grid/public/grid.h"
#include "algorithms/public/algorithmcontext.h"
#include <iostream>
#include <functional>

class App
{
public:
    App() = default;
    App(Grid* grid, AlgorithmContext* algo) : m_Grid(grid), m_Algo(algo) {}

    void InitApp(Grid* grid, AlgorithmContext* algo)
    {
        m_Grid = grid;
        m_Algo = algo;
    }

    void GenerateMaze()
    {
        m_Algo->ExecuteOn(*m_Grid);
        m_Grid->UploadGridVertices();
        //std::cout << *m_Grid << std::endl;

        for (auto& callback : OnMazeGenerated) callback();
    }

public:
    // Listener (vector allows multiple functions to subscribe)
    std::vector<std::function<void()>> OnMazeGenerated;

private:
    Grid* m_Grid;
    AlgorithmContext* m_Algo;
};