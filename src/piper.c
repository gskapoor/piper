#include <stdio.h>
#include <stdint.h>

#include "raylib.h"

#define SQUARE_SIZE 256

#define NORTH 0b0001
#define EAST  0b0010
#define SOUTH 0b0100
#define WEST  0b1000

// Using standard int since calling raylib
static const int screenWidth = 1024;
static const int screenHeight = 1024;

static const int pipeWidth = SQUARE_SIZE / 4;
static const int pipeOffset = pipeWidth / 2;

// TODO: add details of how I'm storing this
static uint8_t tiles[4][4] = {
    {0b0100, 0b1110, 0b0100, 0b0100},
    {0b0110, 0b1001, 0b0101, 0b0101},
    {0b0101, 0b0110, 0b1001, 0b0101},
    {0b0010, 0b1011, 0b1010, 0b1001}
};

int main(int argc, char** argv){
    InitWindow(screenWidth, screenHeight, "Piper");

    BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                // char buf[1];
                // sprintf(buf,"%d", tiles[i][j]);
                // DrawText(buf, i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, ORANGE);
                DrawRectangle(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, GRAY);
                DrawRectangle(i * SQUARE_SIZE + 16, j * SQUARE_SIZE + 16, SQUARE_SIZE - 32, SQUARE_SIZE - 32, GREEN);

                int center_x = i * SQUARE_SIZE + SQUARE_SIZE / 2;
                int center_y = j * SQUARE_SIZE + SQUARE_SIZE / 2;

                if (tiles[i][j] & NORTH){
                    DrawRectangle(center_x - pipeOffset, j * SQUARE_SIZE, pipeWidth, SQUARE_SIZE / 2, ORANGE);
                }
            }
        }
    EndDrawing();

    while(!WindowShouldClose()){
        PollInputEvents();
    }
    CloseWindow();
    
    return 0;
}