#include <stdio.h>
#include "raylib.h"

int main(int argc, char** argv){
    InitWindow(200, 200, "Piper");

    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("I'm a piper : )", 0, 0, 5, ORANGE);
    EndDrawing();

    while(!WindowShouldClose()){
        PollInputEvents();
    }
    CloseWindow();
    
    return 0;
}