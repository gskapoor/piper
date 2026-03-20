#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

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
// static uint8_t tiles[4][4] = {
//     {0b0010, 0b1110, 0b1100, 0b0100},
//     {0b0110, 0b1001, 0b0101, 0b0101},
//     {0b0001, 0b0110, 0b1001, 0b0101},
//     {0b0010, 0b1011, 0b1010, 0b1001}
// };

// Tile Related Functions

bool tile_has_single_entry(uint8_t tile){
    return tile == NORTH || tile == EAST || tile == SOUTH || tile == WEST;
}

bool tile_has_bent_pipe(uint8_t tile){
    return (
        tile == (NORTH | EAST) ||
        tile == (SOUTH | EAST) ||
        tile == (NORTH | WEST) ||
        tile == (WEST | SOUTH)
    );
}

bool tile_has_straight_pipe(uint8_t tile){
    return (
        tile == (NORTH | SOUTH) || tile == (WEST | EAST)
    );
}

bool tile_has_triple_entry(uint8_t tile){
    return (
        tile == (NORTH | EAST | WEST) ||
        tile == (SOUTH | EAST | WEST) ||
        tile == (NORTH | WEST | SOUTH) ||
        tile == (NORTH | EAST | SOUTH)
    );
}

// Tilemap creation
// Assume an "empty" tilemap is calloced to 0
void generate_tilemap(uint8_t** tilemap, uint8_t m, uint8_t n){
    for (int row = 0; row < m; row++){
        for (int col = 0; col < n; col++){
            tilemap[row][col] = NORTH | SOUTH;
        }
    }
}

uint8_t rotate_tile_once(uint8_t tile){
    // Counter Clockwise
    // return ((tile & 1) << 3) + (tile >> 1);
    // Clockwise for now
    return ((tile << 1) & 0xF) + (tile >> 3);
}

void redraw_pipes(uint8_t** tiles){
    BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                // char buf[1];
                // sprintf(buf,"%d", tiles[i][j]);
                // DrawText(buf, j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, ORANGE);

                DrawRectangle(j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, GRAY);
                DrawRectangle(j * SQUARE_SIZE + 16, i * SQUARE_SIZE + 16, SQUARE_SIZE - 32, SQUARE_SIZE - 32, GREEN);

                int center_x = j * SQUARE_SIZE + SQUARE_SIZE / 2;
                int center_y = i * SQUARE_SIZE + SQUARE_SIZE / 2;

                if (tiles[i][j] & NORTH){
                    DrawRectangle(center_x - pipeOffset, i * SQUARE_SIZE, pipeWidth, SQUARE_SIZE / 2 + pipeOffset, ORANGE);
                } 
                if (tiles[i][j] & SOUTH){
                    DrawRectangle(center_x - pipeOffset, center_y - pipeOffset, pipeWidth, SQUARE_SIZE / 2 + pipeOffset, ORANGE);
                }
                if (tiles[i][j] & EAST){
                    DrawRectangle(center_x - pipeOffset, center_y - pipeOffset, SQUARE_SIZE / 2 + pipeOffset, pipeWidth, ORANGE);
                }
                if (tiles[i][j] & WEST){
                    DrawRectangle(j * SQUARE_SIZE, center_y - pipeOffset, SQUARE_SIZE / 2 + pipeOffset, pipeWidth, ORANGE);
                }
            }
        }
    EndDrawing();


}

int main(int argc, char** argv){

    // I sure love pseudo random numbers
    srand(time(NULL));

    InitWindow(screenWidth, screenHeight, "Piper");

    uint8_t m = 4, n = 4;

    uint8_t **tiles = malloc(m * sizeof(uint8_t *));
    for (int i = 0; i < m; i++)
        tiles[i] = malloc(n * sizeof(uint8_t));


    generate_tilemap(tiles, 4, 4);

    redraw_pipes(tiles);

    while(!WindowShouldClose()){
        PollInputEvents();
        
        // Check for mouse input
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            int mouse_x = GetMouseX();
            int mouse_y = GetMouseY();

            int col = mouse_x / SQUARE_SIZE;
            int row = mouse_y / SQUARE_SIZE;

            tiles[row][col] = rotate_tile_once(tiles[row][col]);

            redraw_pipes(tiles);
        }
    }
    CloseWindow();
    
    return 0;
}