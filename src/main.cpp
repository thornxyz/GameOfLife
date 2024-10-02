#include <cstdio>

#include "raylib.h"
#include "simulation.hpp"

int main(void) {
    Color GREY = {29, 29, 29, 255};
    const int MENU_WIDTH = 200;
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 850;
    int CELL_SIZE = 25;
    int FPS = 12;

    InitWindow(WINDOW_WIDTH + MENU_WIDTH, WINDOW_HEIGHT, "Conway's");
    SetTargetFPS(FPS);

    Simulation simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);

    bool isPaused = true;

    Color colorOption1 = {255, 0, 0, 255};
    Color colorOption2 = {0, 255, 0, 255};
    Color colorOption3 = {0, 0, 255, 255};

    Color selectedColor = colorOption1;

    float buttonWidth = 180;
    float buttonHeight = 40;
    float buttonX = (MENU_WIDTH - buttonWidth) / 2;

    Rectangle resumePauseButton = {buttonX, 20, buttonWidth, buttonHeight};
    Rectangle clearButton = {buttonX, 70, buttonWidth, buttonHeight};
    Rectangle randomButton = {buttonX, 120, buttonWidth, buttonHeight};
    Rectangle fpsButton = {buttonX, 170, buttonWidth, buttonHeight};
    Rectangle plusButtonArea = {fpsButton.x + buttonWidth - 40, fpsButton.y, 40,
                                buttonHeight};
    Rectangle minusButtonArea = {fpsButton.x, fpsButton.y, 40, buttonHeight};
    Rectangle resetButton = {buttonX, 220, buttonWidth, buttonHeight};
    Rectangle cellSizeButton = {buttonX, 270, buttonWidth, buttonHeight};
    Rectangle cellPlus = {cellSizeButton.x + buttonWidth - 40, cellSizeButton.y,
                          40, buttonHeight};
    Rectangle cellMinus = {cellSizeButton.x, cellSizeButton.y, 40,
                           buttonHeight};
    Rectangle resetSizeButton = {buttonX, 320, buttonWidth, buttonHeight};

    Rectangle color1Button = {buttonX, 370, buttonWidth, buttonHeight};
    Rectangle color2Button = {buttonX, 420, buttonWidth, buttonHeight};
    Rectangle color3Button = {buttonX, 470, buttonWidth, buttonHeight};

    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int column = (mousePosition.x - MENU_WIDTH) / CELL_SIZE;

            if (mousePosition.x >= MENU_WIDTH && column >= 0 &&
                column < WINDOW_WIDTH / CELL_SIZE) {
                simulation.SetCellValue(row, column, selectedColor);
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();

            if (CheckCollisionPointRec(mousePosition, resumePauseButton)) {
                isPaused = !isPaused;
                if (isPaused) {
                    simulation.Stop();
                } else {
                    simulation.Start();
                }
            } else if (CheckCollisionPointRec(mousePosition, clearButton)) {
                simulation.ClearGrid();
            } else if (CheckCollisionPointRec(mousePosition, randomButton)) {
                simulation.CreateRandomState();
            } else if (CheckCollisionPointRec(mousePosition, plusButtonArea)) {
                FPS += 4;
                SetTargetFPS(FPS);
            } else if (CheckCollisionPointRec(mousePosition, minusButtonArea)) {
                if (FPS > 5) {
                    FPS -= 4;
                    SetTargetFPS(FPS);
                }
            } else if (CheckCollisionPointRec(mousePosition, resetButton)) {
                FPS = 12;
                SetTargetFPS(FPS);
            } else if (CheckCollisionPointRec(mousePosition, cellPlus)) {
                CELL_SIZE += 5;
                if (CELL_SIZE > 0) {
                    simulation =
                        Simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
                }
            } else if (CheckCollisionPointRec(mousePosition, cellMinus)) {
                if (CELL_SIZE > 5) {
                    CELL_SIZE -= 5;
                    simulation =
                        Simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
                }
            } else if (CheckCollisionPointRec(mousePosition, resetSizeButton)) {
                CELL_SIZE = 25;
                simulation = Simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
            } else if (CheckCollisionPointRec(mousePosition, color1Button)) {
                selectedColor = colorOption1;
            } else if (CheckCollisionPointRec(mousePosition, color2Button)) {
                selectedColor = colorOption2;
            } else if (CheckCollisionPointRec(mousePosition, color3Button)) {
                selectedColor = colorOption3;
            }
        }

        if (!isPaused) {
            simulation.Update();
        }

        BeginDrawing();
        ClearBackground(GREY);

        simulation.Draw(MENU_WIDTH);

        DrawRectangleRec(resumePauseButton, isPaused ? DARKGRAY : GREEN);
        int textWidth =
            (isPaused ? MeasureText("Resume", 20) : MeasureText("Pause", 20));
        DrawText(isPaused ? "Resume" : "Pause",
                 resumePauseButton.x + (buttonWidth - textWidth) / 2,
                 resumePauseButton.y + 10, 20, RAYWHITE);

        DrawRectangleRec(clearButton, DARKGRAY);
        textWidth = MeasureText("Clear", 20);
        DrawText("Clear", clearButton.x + (buttonWidth - textWidth) / 2,
                 clearButton.y + 10, 20, RAYWHITE);

        DrawRectangleRec(randomButton, DARKGRAY);
        textWidth = MeasureText("Random", 20);
        DrawText("Random", randomButton.x + (buttonWidth - textWidth) / 2,
                 randomButton.y + 10, 20, RAYWHITE);

        DrawRectangleRec(fpsButton, DARKGRAY);
        DrawText("-", minusButtonArea.x + 15, minusButtonArea.y + 10, 25,
                 RAYWHITE);
        char fpsText[20];
        sprintf(fpsText, "%d FPS", FPS);
        DrawText(fpsText,
                 fpsButton.x + (buttonWidth / 2 - MeasureText(fpsText, 20) / 2),
                 fpsButton.y + 10, 20, RAYWHITE);
        DrawText("+", plusButtonArea.x + 15, plusButtonArea.y + 10, 25,
                 RAYWHITE);

        DrawRectangleRec(resetButton, DARKGRAY);
        textWidth = MeasureText("Reset FPS", 20);
        DrawText("Reset FPS", resetButton.x + (buttonWidth - textWidth) / 2,
                 resetButton.y + 10, 20, RAYWHITE);

        DrawRectangleRec(cellSizeButton, DARKGRAY);
        DrawText("-", cellMinus.x + 15, cellMinus.y + 10, 25, RAYWHITE);
        char cellSizeText[20];
        sprintf(cellSizeText, "%d", CELL_SIZE);
        DrawText(cellSizeText,
                 cellSizeButton.x +
                     (buttonWidth / 2 - MeasureText(cellSizeText, 20) / 2),
                 cellSizeButton.y + 10, 20, RAYWHITE);
        DrawText("+", cellPlus.x + 15, cellPlus.y + 10, 25, RAYWHITE);
        DrawRectangleRec(resetSizeButton, DARKGRAY);
        textWidth = MeasureText("Reset Size", 20);
        DrawText("Reset Size",
                 resetSizeButton.x + (buttonWidth - textWidth) / 2,
                 resetSizeButton.y + 10, 20, RAYWHITE);

        DrawRectangleRec(color1Button, colorOption1);
        textWidth = MeasureText("Color 1", 20);
        DrawText("Color 1", color1Button.x + (buttonWidth - textWidth) / 2,
                 color1Button.y + 10, 20, RAYWHITE);

        DrawRectangleRec(color2Button, colorOption2);
        textWidth = MeasureText("Color 2", 20);
        DrawText("Color 2", color2Button.x + (buttonWidth - textWidth) / 2,
                 color2Button.y + 10, 20, RAYWHITE);

        DrawRectangleRec(color3Button, colorOption3);
        textWidth = MeasureText("Color 3", 20);
        DrawText("Color 3", color3Button.x + (buttonWidth - textWidth) / 2,
                 color3Button.y + 10, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
}
