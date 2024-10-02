#include "grid.hpp"

#include "globals.hpp"
#include "raylib.h"

void Grid::Draw(int xOffset) {
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            Color color = cells[row][column];
            DrawRectangle(xOffset + column * cellSize, row * cellSize,
                          cellSize - 0.125, cellSize - 0.125, color);
        }
    }
}

void Grid::SetValue(int row, int column, Color value) {
    if (IsWithinBounds(row, column)) {
        cells[row][column] = value;
    }
}

Color Grid::GetValue(int row, int column) {
    if (IsWithinBounds(row, column)) {
        return cells[row][column];
    }
    return deadColor;
}

bool Grid::IsWithinBounds(int row, int column) {
    return row >= 0 && row < rows && column >= 0 && column < columns;
}

void Grid::FillRandom() {
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            int randomValue = GetRandomValue(0, 8);
            switch (randomValue) {
                case 1:
                    cells[row][column] = Color{255, 0, 0, 255};
                    break;
                case 2:
                    cells[row][column] = Color{0, 255, 0, 255};
                    break;
                case 3:
                    cells[row][column] = Color{0, 0, 255, 255};
                    break;
                default:
                    cells[row][column] = deadColor;
                    break;
            }
        }
    }
}

void Grid::Clear() {
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            cells[row][column] = deadColor;
        }
    }
}

void Grid::ToggleCell(int row, int column) {
    if (IsWithinBounds(row, column)) {
        if (cells[row][column].r != deadColor.r ||
            cells[row][column].g != deadColor.g ||
            cells[row][column].b != deadColor.b) {
            cells[row][column] = deadColor;
        } else {
            int randomValue = GetRandomValue(1, 3);
            switch (randomValue) {
                case 1:
                    cells[row][column] = Color{255, 0, 0, 255};
                    break;
                case 2:
                    cells[row][column] = Color{0, 255, 0, 255};
                    break;
                case 3:
                    cells[row][column] = Color{0, 0, 255, 255};
                    break;
            }
        }
    }
}

Color Grid::GetAverageColorOfNeighbors(int row, int column) {
    int rSum = 0, gSum = 0, bSum = 0, liveCount = 0;
    vector<std::pair<int, int>> neighborOffsets = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (const auto& offset : neighborOffsets) {
        int neighborRow = (row + offset.first + rows) % rows;
        int neighborColumn = (column + offset.second + columns) % columns;

        Color neighborColor = GetValue(neighborRow, neighborColumn);
        if (neighborColor.r != deadColor.r || neighborColor.g != deadColor.g ||
            neighborColor.b != deadColor.b) {
            rSum += neighborColor.r;
            gSum += neighborColor.g;
            bSum += neighborColor.b;
            liveCount++;
        }
    }

    if (liveCount > 0) {
        return Color{static_cast<unsigned char>(rSum / liveCount),
                     static_cast<unsigned char>(gSum / liveCount),
                     static_cast<unsigned char>(bSum / liveCount), 255};
    } else {
        return deadColor;
    }
}
