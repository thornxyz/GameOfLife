#include "simulation.hpp"

#include <utility>
#include <vector>

#include "globals.hpp"

using std::pair;
using std::vector;

void Simulation::Draw(int xOffset) { grid.Draw(xOffset); }

void Simulation::SetCellValue(int row, int column, Color color) {
    grid.SetValue(row, column, color);
}

int Simulation::CountLiveNeighbors(int row, int column) {
    int liveNeighbors = 0;
    vector<pair<int, int>> neighborOffsets = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (const auto& offset : neighborOffsets) {
        int neighborRow =
            (row + offset.first + grid.GetRows()) % grid.GetRows();
        int neighborColumn =
            (column + offset.second + grid.GetColumns()) % grid.GetColumns();
        Color neighborColor = grid.GetValue(neighborRow, neighborColumn);

        if (neighborColor.r != deadColor.r || neighborColor.g != deadColor.g ||
            neighborColor.b != deadColor.b || neighborColor.a != deadColor.a) {
            liveNeighbors++;
        }
    }
    return liveNeighbors;
}

// normal gol
void Simulation::UpdateConway() {
    if (IsRunning()) {
        for (int row = 0; row < grid.GetRows(); row++) {
            for (int column = 0; column < grid.GetColumns(); column++) {
                int liveNeighbors = CountLiveNeighbors(row, column);
                Color cellValue = grid.GetValue(row, column);

                if (cellValue.r != deadColor.r || cellValue.g != deadColor.g ||
                    cellValue.b != deadColor.b || cellValue.a != deadColor.a) {
                    if (liveNeighbors > 3 || liveNeighbors < 2) {
                        tempGrid.SetValue(row, column, deadColor);
                    } else {
                        tempGrid.SetValue(row, column, cellValue);
                    }
                } else {
                    if (liveNeighbors == 3) {
                        Color avgColor =
                            grid.GetAverageColorOfNeighbors(row, column);
                        tempGrid.SetValue(row, column, avgColor);
                    } else {
                        tempGrid.SetValue(row, column, deadColor);
                    }
                }
            }
        }
        grid = tempGrid;
    }
}

// walled cities
void Simulation::UpdateWalledCities() {
    if (IsRunning()) {
        for (int row = 0; row < grid.GetRows(); row++) {
            for (int column = 0; column < grid.GetColumns(); column++) {
                int liveNeighbors = CountLiveNeighbors(row, column);
                Color cellValue = grid.GetValue(row, column);

                if (cellValue.r != deadColor.r || cellValue.g != deadColor.g ||
                    cellValue.b != deadColor.b || cellValue.a != deadColor.a) {
                    if (liveNeighbors == 2 || liveNeighbors == 3 ||
                        liveNeighbors == 4 || liveNeighbors == 5) {
                        tempGrid.SetValue(row, column, cellValue);
                    } else {
                        tempGrid.SetValue(row, column, deadColor);
                    }
                } else {
                    if (liveNeighbors == 4 || liveNeighbors == 5 ||
                        liveNeighbors == 6 || liveNeighbors == 7 ||
                        liveNeighbors == 8) {
                        Color avgColor =
                            grid.GetAverageColorOfNeighbors(row, column);
                        tempGrid.SetValue(row, column, avgColor);
                    } else {
                        tempGrid.SetValue(row, column, deadColor);
                    }
                }
            }
        }
        grid = tempGrid;
    }
}

// Gnarl
void Simulation::UpdateGnarl() {
    if (IsRunning()) {
        for (int row = 0; row < grid.GetRows(); row++) {
            for (int column = 0; column < grid.GetColumns(); column++) {
                int liveNeighbors = CountLiveNeighbors(row, column);
                Color cellValue = grid.GetValue(row, column);

                if (cellValue.r != deadColor.r || cellValue.g != deadColor.g ||
                    cellValue.b != deadColor.b || cellValue.a != deadColor.a) {
                    if (liveNeighbors == 1) {
                        tempGrid.SetValue(row, column, cellValue);
                    } else {
                        tempGrid.SetValue(row, column, deadColor);
                    }
                } else {
                    if (liveNeighbors == 1) {
                        Color avgColor =
                            grid.GetAverageColorOfNeighbors(row, column);
                        tempGrid.SetValue(row, column, avgColor);
                    } else {
                        tempGrid.SetValue(row, column, deadColor);
                    }
                }
            }
        }
        grid = tempGrid;
    }
}

// 34 life
void Simulation::UpdateLife34() {
    if (IsRunning()) {
        for (int row = 0; row < grid.GetRows(); row++) {
            for (int column = 0; column < grid.GetColumns(); column++) {
                int liveNeighbors = CountLiveNeighbors(row, column);
                Color cellValue = grid.GetValue(row, column);

                if (cellValue.r != deadColor.r || cellValue.g != deadColor.g ||
                    cellValue.b != deadColor.b || cellValue.a != deadColor.a) {
                    if (liveNeighbors == 3 || liveNeighbors == 4) {
                        tempGrid.SetValue(row, column, cellValue);
                    } else {
                        tempGrid.SetValue(row, column, deadColor);
                    }
                } else {
                    if (liveNeighbors == 3 || liveNeighbors == 4) {
                        Color avgColor =
                            grid.GetAverageColorOfNeighbors(row, column);
                        tempGrid.SetValue(row, column, avgColor);
                    } else {
                        tempGrid.SetValue(row, column, deadColor);
                    }
                }
            }
        }
        grid = tempGrid;
    }
}

void Simulation::ClearGrid() {
    if (!IsRunning()) {
        grid.Clear();
    }
}

void Simulation::CreateRandomState() {
    if (!IsRunning()) {
        grid.FillRandom();
    }
}

void Simulation::ToggleCell(int row, int column) {
    if (!IsRunning()) {
        grid.ToggleCell(row, column);
    }
}