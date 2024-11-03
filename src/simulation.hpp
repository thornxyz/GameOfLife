#pragma once
#include "grid.hpp"
#include "raylib.h"

class Simulation {
   public:
    Simulation(int width, int height, int cellSize)
        : grid(width, height, cellSize),
          tempGrid(width, height, cellSize),
          run(false) {};

    void Draw(int xOffset);
    void SetCellValue(int row, int column, Color color);
    int CountLiveNeighbors(int row, int column);
    void UpdateConway();
    void UpdateWalledCities();
    void UpdateGnarl();
    void UpdateLife34();
    bool IsRunning() { return run; }
    void Start() { run = true; }
    void Stop() { run = false; }
    void ClearGrid();
    void CreateRandomState();
    void ToggleCell(int row, int column);

   private:
    Grid grid;
    Grid tempGrid;
    bool run;
};