#include <stdio.h>
#include <stdint.h>

#include "raylib.h"

#define SQUARE_SIZE 256

// Using standard int since calling raylib
static const int screenWidth = 1024;
static const int screenHeight = 1024;

// TODO: add details of how I'm storing this
// For now, first byte represents number of entries, except for "0" which represents a straight pipe
// Second byte is orientation, indexed by the counterclockwise most open pipe.
// 0 is up, 1 is right, 2 is down and 3 is left.
// For straight pipes, 0 is up/down, 1 is right/left
static uint8_t tiles[4][4] = {
    {0x11, 0x31, 0x12, 0x12},
    {0x21, 0x23, 0x00, 0x00},
    {0x00, 0x21, 0x23, 0x00},
    {0x11, 0x33, 0x01, 0x23}
};

int main(int argc, char** argv){
    InitWindow(screenWidth, screenHeight, "Piper");

    BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                char buf[1];
                sprintf(buf,"%d", tiles[i][j]);
                DrawText(buf, i * SQUARE_SIZE, j * SQUARE_SIZE, 5, ORANGE);
            }
        }
    EndDrawing();

    while(!WindowShouldClose()){
        PollInputEvents();
    }
    CloseWindow();
    
    return 0;
}