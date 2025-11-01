#ifndef _WIN32
    #define _DEFAULT_SOURCE
    #define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define BOARD_SIZE 10
#define NUM_SHIPS 5
#define WATER '~'
#define HIT 'X'
#define MISS 'O'
#define SHIP 'S'

// Ship types
typedef struct {
    char name[20];
    int size;
    int hits;
    int sunk;
} Ship;

// Game board
typedef struct {
    char grid[BOARD_SIZE][BOARD_SIZE];
    char display[BOARD_SIZE][BOARD_SIZE];
    int shipId[BOARD_SIZE][BOARD_SIZE];  // Track which ship is at each position
    Ship ships[NUM_SHIPS];
    int shipsRemaining;
} Board;

// Function prototypes (from battleship.c)
void initShips(Board *board);
void initializeBoard(Board *board);
int placeShip(Board *board, int shipIndex, int row, int col, int horizontal);
int shoot(Board *board, int row, int col);

// Initialize ships data
void initShips(Board *board) {
    strcpy(board->ships[0].name, "Carrier");
    board->ships[0].size = 5;
    strcpy(board->ships[1].name, "Battleship");
    board->ships[1].size = 4;
    strcpy(board->ships[2].name, "Cruiser");
    board->ships[2].size = 3;
    strcpy(board->ships[3].name, "Submarine");
    board->ships[3].size = 3;
    strcpy(board->ships[4].name, "Destroyer");
    board->ships[4].size = 2;
    
    for (int i = 0; i < NUM_SHIPS; i++) {
        board->ships[i].hits = 0;
        board->ships[i].sunk = 0;
    }
    board->shipsRemaining = NUM_SHIPS;
}

// Initialize game board
void initializeBoard(Board *board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board->grid[i][j] = WATER;
            board->display[i][j] = WATER;
            board->shipId[i][j] = -1;
        }
    }
    initShips(board);
}

// Place a ship on the board
int placeShip(Board *board, int shipIndex, int row, int col, int horizontal) {
    int size = board->ships[shipIndex].size;
    
    // Check if ship fits on board
    if (horizontal) {
        if (col + size > BOARD_SIZE) return 0;
    } else {
        if (row + size > BOARD_SIZE) return 0;
    }
    
    // Check if space is available
    for (int i = 0; i < size; i++) {
        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;
        if (board->grid[r][c] != WATER) return 0;
    }
    
    // Place the ship
    for (int i = 0; i < size; i++) {
        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;
        board->grid[r][c] = SHIP;
        board->display[r][c] = SHIP;
        board->shipId[r][c] = shipIndex;
    }
    
    return 1;
}

// Player shoots at a position
int shoot(Board *board, int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return -1; // Invalid coordinates
    }
    
    if (board->display[row][col] == HIT || board->display[row][col] == MISS) {
        return -2; // Already shot here
    }
    
    if (board->grid[row][col] == SHIP) {
        board->display[row][col] = HIT;
        
        // Get the ship that was hit
        int shipIndex = board->shipId[row][col];
        if (shipIndex >= 0 && shipIndex < NUM_SHIPS) {
            board->ships[shipIndex].hits++;
            if (board->ships[shipIndex].hits >= board->ships[shipIndex].size) {
                board->ships[shipIndex].sunk = 1;
                board->shipsRemaining--;
            }
        }
        return 1; // Hit
    } else {
        board->display[row][col] = MISS;
        return 0; // Miss
    }
}

// Test functions
void test_board_initialization() {
    Board board;
    initializeBoard(&board);
    
    // Check that all cells are water
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            assert(board.grid[i][j] == WATER);
            assert(board.display[i][j] == WATER);
        }
    }
    
    // Check ships are initialized
    assert(board.shipsRemaining == NUM_SHIPS);
    assert(board.ships[0].size == 5);
    assert(board.ships[1].size == 4);
    assert(board.ships[2].size == 3);
    assert(board.ships[3].size == 3);
    assert(board.ships[4].size == 2);
    
    printf("✓ Board initialization test passed\n");
}

void test_ship_placement() {
    Board board;
    initializeBoard(&board);
    
    // Test horizontal ship placement
    int result = placeShip(&board, 0, 0, 0, 1);
    assert(result == 1);
    
    // Verify ship is placed correctly
    for (int i = 0; i < board.ships[0].size; i++) {
        assert(board.grid[0][i] == SHIP);
    }
    
    // Test that overlapping placement fails
    result = placeShip(&board, 1, 0, 0, 1);
    assert(result == 0);
    
    // Test vertical placement
    result = placeShip(&board, 1, 1, 0, 0);
    assert(result == 1);
    
    // Test boundary checking
    result = placeShip(&board, 2, 0, 9, 1);
    assert(result == 0);
    
    printf("✓ Ship placement test passed\n");
}

void test_shooting() {
    Board board;
    initializeBoard(&board);
    
    // Place a ship
    placeShip(&board, 0, 0, 0, 1);
    
    // Test hitting a ship
    int result = shoot(&board, 0, 0);
    assert(result == 1);
    assert(board.display[0][0] == HIT);
    
    // Test missing
    result = shoot(&board, 5, 5);
    assert(result == 0);
    assert(board.display[5][5] == MISS);
    
    // Test shooting same spot twice
    result = shoot(&board, 0, 0);
    assert(result == -2);
    
    // Test invalid coordinates
    result = shoot(&board, -1, 0);
    assert(result == -1);
    
    result = shoot(&board, 10, 10);
    assert(result == -1);
    
    printf("✓ Shooting test passed\n");
}

void test_ship_sinking() {
    Board board;
    initializeBoard(&board);
    
    // Place a small ship (destroyer - size 2)
    placeShip(&board, 4, 0, 0, 1);
    
    int initialShips = board.shipsRemaining;
    
    // Hit the ship twice to sink it
    shoot(&board, 0, 0);
    assert(board.shipsRemaining == initialShips);
    
    shoot(&board, 0, 1);
    assert(board.shipsRemaining == initialShips - 1);
    assert(board.ships[4].sunk == 1);
    
    printf("✓ Ship sinking test passed\n");
}

int main() {
    printf("\n=== Running Battleship Tests ===\n\n");
    
    test_board_initialization();
    test_ship_placement();
    test_shooting();
    test_ship_sinking();
    
    printf("\n=== All tests passed! ===\n\n");
    
    return 0;
}
