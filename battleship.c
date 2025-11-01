#ifndef _WIN32
    #define _DEFAULT_SOURCE
    #define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
    
    // Compatibility functions for non-Windows systems
    void Sleep(int milliseconds) {
        usleep(milliseconds * 1000);
    }
    
    int _getch(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        return ch;
    }
    
    void clearConsole(void) {
        printf("\033[2J\033[1;1H");
        fflush(stdout);
    }
#endif

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

// Function prototypes
void initializeBoard(Board *board);
void displayBoard(Board *board, int hideShips);
void placeShipsRandomly(Board *board);
int placeShip(Board *board, int shipIndex, int row, int col, int horizontal);
int shoot(Board *board, int row, int col);
void playGame();
int checkGameOver(Board *playerBoard, Board *computerBoard);
void clearScreen();
void printTitle();
void computerTurn(Board *playerBoard, int *lastRow, int *lastCol, int *lastHit);

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

// Clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    clearConsole();
#endif
}

// Print game title
void printTitle() {
    printf("\n");
    printf("  ====================================\n");
    printf("  ||     BATTLESHIP GAME 2017      ||\n");
    printf("  ====================================\n");
    printf("\n");
}

// Display the game board
void displayBoard(Board *board, int hideShips) {
    printf("    ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");
    printf("   ");
    for (int i = 0; i < BOARD_SIZE * 2 + 1; i++) {
        printf("-");
    }
    printf("\n");
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d | ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            char cell = board->display[i][j];
            if (hideShips && cell == SHIP) {
                printf("%c ", WATER);
            } else {
                printf("%c ", cell);
            }
        }
        printf("|\n");
    }
    
    printf("   ");
    for (int i = 0; i < BOARD_SIZE * 2 + 1; i++) {
        printf("-");
    }
    printf("\n");
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

// Place all ships randomly
void placeShipsRandomly(Board *board) {
    for (int i = 0; i < NUM_SHIPS; i++) {
        int placed = 0;
        while (!placed) {
            int row = rand() % BOARD_SIZE;
            int col = rand() % BOARD_SIZE;
            int horizontal = rand() % 2;
            placed = placeShip(board, i, row, col, horizontal);
        }
    }
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
                printf("\n  >>> You sunk the %s! <<<\n", board->ships[shipIndex].name);
            }
        }
        return 1; // Hit
    } else {
        board->display[row][col] = MISS;
        return 0; // Miss
    }
}

// Computer's turn (simple AI)
void computerTurn(Board *playerBoard, int *lastRow, int *lastCol, int *lastHit) {
    int row, col;
    int validShot = 0;
    
    while (!validShot) {
        // Simple AI: if last shot was a hit, try adjacent cells
        if (*lastHit) {
            int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
            int dir = rand() % 4;
            row = *lastRow + directions[dir][0];
            col = *lastCol + directions[dir][1];
            
            if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE ||
                playerBoard->display[row][col] == HIT || playerBoard->display[row][col] == MISS) {
                *lastHit = 0; // Reset and pick random
                continue;
            }
        } else {
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;
        }
        
        if (playerBoard->display[row][col] != HIT && playerBoard->display[row][col] != MISS) {
            validShot = 1;
        }
    }
    
    printf("\n  Computer shoots at (%d, %d)... ", row, col);
    Sleep(1000);
    
    int result = shoot(playerBoard, row, col);
    if (result == 1) {
        printf("HIT!\n");
        *lastRow = row;
        *lastCol = col;
        *lastHit = 1;
    } else {
        printf("MISS!\n");
        *lastHit = 0;
    }
    
    Sleep(1500);
}

// Check if game is over
int checkGameOver(Board *playerBoard, Board *computerBoard) {
    if (playerBoard->shipsRemaining == 0) {
        printf("\n  *** GAME OVER - Computer Wins! ***\n\n");
        return 1;
    }
    if (computerBoard->shipsRemaining == 0) {
        printf("\n  *** CONGRATULATIONS - You Win! ***\n\n");
        return 1;
    }
    return 0;
}

// Main game loop
void playGame() {
    Board playerBoard, computerBoard;
    int gameOver = 0;
    int compLastRow = 0, compLastCol = 0, compLastHit = 0;
    
    // Initialize boards
    initializeBoard(&playerBoard);
    initializeBoard(&computerBoard);
    
    // Place ships
    printf("  Placing your ships randomly...\n");
    placeShipsRandomly(&playerBoard);
    Sleep(1000);
    
    printf("  Placing computer's ships...\n");
    placeShipsRandomly(&computerBoard);
    Sleep(1000);
    
    // Game loop
    while (!gameOver) {
        clearScreen();
        printTitle();
        
        // Display boards
        printf("  YOUR BOARD:\n");
        displayBoard(&playerBoard, 0);
        
        printf("\n  COMPUTER'S BOARD:\n");
        displayBoard(&computerBoard, 1);
        
        // Player's turn
        printf("\n  Your turn! Enter coordinates to shoot (row col): ");
        int row, col;
        if (scanf("%d %d", &row, &col) != 2) {
            // Clear input buffer
            while (getchar() != '\n');
            printf("  Invalid input! Please enter two numbers.\n");
            Sleep(2000);
            continue;
        }
        
        int result = shoot(&computerBoard, row, col);
        if (result == -1) {
            printf("  Invalid coordinates! Try again.\n");
            Sleep(2000);
            continue;
        } else if (result == -2) {
            printf("  You already shot there! Try again.\n");
            Sleep(2000);
            continue;
        } else if (result == 1) {
            printf("  HIT!\n");
        } else {
            printf("  MISS!\n");
        }
        
        Sleep(1500);
        
        // Check if player won
        if (checkGameOver(&playerBoard, &computerBoard)) {
            gameOver = 1;
            break;
        }
        
        // Computer's turn
        computerTurn(&playerBoard, &compLastRow, &compLastCol, &compLastHit);
        
        // Check if computer won
        if (checkGameOver(&playerBoard, &computerBoard)) {
            gameOver = 1;
        }
    }
    
    // Final board display
    clearScreen();
    printTitle();
    printf("  FINAL BOARDS:\n\n");
    printf("  YOUR BOARD:\n");
    displayBoard(&playerBoard, 0);
    printf("\n  COMPUTER'S BOARD:\n");
    displayBoard(&computerBoard, 0);
}

// Main function
int main() {
    srand(time(NULL));
    char playAgain;
    
    do {
        clearScreen();
        printTitle();
        printf("  Welcome to Battleship!\n");
        printf("  Press any key to start...\n");
        _getch();
        
        playGame();
        
        printf("\n  Play again? (y/n): ");
        playAgain = _getch();
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    printf("\n\n  Thanks for playing!\n\n");
    
    return 0;
}
