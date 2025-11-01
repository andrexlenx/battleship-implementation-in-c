# Battleship Implementation in C

A classic Battleship board game implementation in C, created in 2017. The game uses console-based graphics with support for both Windows (using `windows.h` and `conio.h`) and Unix-like systems (using POSIX terminal functions).

## Features

- Classic Battleship gameplay
- Single-player mode against computer AI
- 10x10 game board
- 5 different ship types:
  - Carrier (5 spaces)
  - Battleship (4 spaces)
  - Cruiser (3 spaces)
  - Submarine (3 spaces)
  - Destroyer (2 spaces)
- Automatic ship placement
- Simple computer AI opponent
- Cross-platform support (Windows and Unix-like systems)

## Building

### Requirements
- GCC compiler (or any C99-compatible compiler)
- Make (optional, for using Makefile)

### Compilation

Using Make:
```bash
make
```

Or compile directly:
```bash
gcc -Wall -Wextra -std=c99 -o battleship battleship.c
```

## Running

After building, run the game:
```bash
./battleship
```

On Windows:
```cmd
battleship.exe
```

## Gameplay

1. The game automatically places ships on both player's and computer's boards
2. Players take turns shooting at coordinates on the opponent's board
3. Enter coordinates as two numbers (row column), e.g., `3 5`
4. The game displays:
   - `~` for water
   - `X` for hits
   - `O` for misses
   - `S` for your ships (on your board only)
5. Sink all opponent ships to win!

## Testing

Run the test suite:
```bash
make test
```

## Cleaning

Remove compiled files:
```bash
make clean
```

## License

See LICENSE file for details.
