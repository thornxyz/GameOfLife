#pragma once
#include <vector>

#include "globals.hpp"
#include "raylib.h"
using std::vector;

class Grid {
   public:
    Grid(int width, int height, int cellSize)
        : rows(height / cellSize),
          columns(width / cellSize),
          cellSize(cellSize),
          cells(rows, vector<Color>(columns, deadColor)) {};

    void Draw(int xOffset);
    void SetValue(int row, int column, Color value);
    Color GetValue(int row, int column);
    bool IsWithinBounds(int row, int column);
    int GetRows() { return rows; }
    int GetColumns() { return columns; }
    void FillRandom();
    void Clear();
    void ToggleCell(int row, int column);
    Color GetAverageColorOfNeighbors(int row, int column);

   private:
    int rows;
    int columns;
    int cellSize;
    vector<vector<Color>> cells;
};